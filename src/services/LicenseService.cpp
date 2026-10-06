#include "LicenseService.h"
#include "ApiClient.h"
#include "SessionManager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>

LicenseService::LicenseService(ApiClient *api, SessionManager *session, QObject *parent)
    : QObject(parent)
    , m_api(api)
    , m_session(session)
{
}

void LicenseService::setBusy(bool busy)
{
    if (m_busy == busy)
        return;
    m_busy = busy;
    emit busyChanged();
}

void LicenseService::fetchMyLicense()
{
    if (m_busy)
        return;

    setBusy(true);

    // Ambil lisensi dengan filter email user (atau ambil semua jika filter belum diaktifkan)
    QString path = QStringLiteral("/items/licenses");
    if (!m_session->userEmail().isEmpty()) {
        // Directus filter query syntax: ?filter[user_email][_eq]=email
        path += QStringLiteral("?filter[user_email][_eq]=") + QUrl::toPercentEncoding(m_session->userEmail());
    }

    m_api->get(path, [this]( const ApiResponse &res) {
        setBusy(false);

        if (!res.ok) {
            emit fetchFailed(res.errorMessage);
            return;
        }

        QList<License> list;
        QJsonArray data = res.json.value(QStringLiteral("data")).toArray();
        for (const QJsonValue &val : data) {
            QJsonObject obj = val.toObject();
            License item;
            item.id = obj.value(QStringLiteral("id")).toVariant().toString();
            item.appName = obj.value(QStringLiteral("app_name")).toString();
            item.licenseKey = obj.value(QStringLiteral("license_key")).toString();
            item.status = obj.value(QStringLiteral("status")).toString();
            item.expiresAt = obj.value(QStringLiteral("expires_at")).toString();
            item.userEmail = obj.value(QStringLiteral("user_email")).toString();
            list.append(item);
        }

        emit licenseFetched(list);
    });
}