#pragma once

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <functional>

class QNetworkReply;
class SessionManager;

// Hasil satu permintaan HTTP, sudah diurai.
struct ApiResponse
{
    bool ok = false;          // true jika status HTTP sukses
    int status = 0;           // kode HTTP, mis. 200 / 401
    QJsonObject json;         // isi balasan (objek JSON)
    QString errorMessage;     // pesan error siap tampil jika !ok
};

using ApiCallback = std::function<void(const ApiResponse &)>;

// Satu-satunya class yang bicara HTTP ke Directus.
// Mengurus base URL, header Authorization, dan pengambilan pesan error.
class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(SessionManager *session, QObject *parent = nullptr);

    QString baseUrl() const { return m_baseUrl; }
    void setBaseUrl(const QString &url) { m_baseUrl = url; }

    // path diawali "/", mis. "/items/licenses".
    // authorized=false untuk endpoint publik seperti /auth/login.
    void get(const QString &path, ApiCallback callback, bool authorized = true);
    void post(const QString &path, const QJsonObject &body, ApiCallback callback,
              bool authorized = true);

private:
    QNetworkRequest makeRequest(const QString &path, bool authorized) const;
    void handleReply(QNetworkReply *reply, ApiCallback callback);

    QNetworkAccessManager m_nam;
    SessionManager *m_session;
    QString m_baseUrl;
};
