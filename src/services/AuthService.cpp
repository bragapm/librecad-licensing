#include "AuthService.h"
#include "ApiClient.h"
#include "SessionManager.h"

#include <QJsonObject>

AuthService::AuthService(ApiClient *api, SessionManager *session, QObject *parent)
    : QObject(parent)
    , m_api(api)
    , m_session(session)
{
}

void AuthService::setBusy(bool busy)
{
    if (m_busy == busy)
        return;
    m_busy = busy;
    emit busyChanged();
}

void AuthService::login(const QString &email, const QString &password)
{
    if (m_busy)
        return;

    const QJsonObject body{
        {QStringLiteral("email"), email},
        {QStringLiteral("password"), password},
        {QStringLiteral("mode"), QStringLiteral("json")},
    };

    setBusy(true);
    m_api->post(QStringLiteral("/auth/login"), body, [this](const ApiResponse &res) {
        if (!res.ok) {
            setBusy(false);
            emit loginFailed(res.errorMessage);
            return;
        }

        const QJsonObject data = res.json.value(QStringLiteral("data")).toObject();
        const QString access = data.value(QStringLiteral("access_token")).toString();
        const QString refresh = data.value(QStringLiteral("refresh_token")).toString();

        if (access.isEmpty()) {
            setBusy(false);
            emit loginFailed(tr("Respon server tidak valid."));
            return;
        }

        m_session->setTokens(access, refresh);
        fetchCurrentUser();
    }, /*authorized=*/false);
}

void AuthService::fetchCurrentUser()
{
    // Dipanggil setelah token tersimpan. Jika gagal, login tetap dianggap berhasil
    // dengan role kosong (diperlakukan sebagai user biasa).
    m_api->get(QStringLiteral("/users/me?fields=email,role.name"), [this](const ApiResponse &res) {
        if (res.ok) {
            const QJsonObject data = res.json.value(QStringLiteral("data")).toObject();
            m_session->setUser(
                data.value(QStringLiteral("email")).toString(),
                data.value(QStringLiteral("role")).toObject()
                    .value(QStringLiteral("name")).toString());
        }
        setBusy(false);
        emit loginSucceeded();
    });
}

void AuthService::logout()
{
    const QString refresh = m_session->refreshToken();
    if (!refresh.isEmpty()) {
        // Best-effort: beri tahu server, hasilnya tidak ditunggu.
        m_api->post(QStringLiteral("/auth/logout"),
                    QJsonObject{{QStringLiteral("refresh_token"), refresh},
                                {QStringLiteral("mode"), QStringLiteral("json")}},
                    nullptr, /*authorized=*/false);
    }
    m_session->clear();
}
