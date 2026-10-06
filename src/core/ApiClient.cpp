#include "ApiClient.h"
#include "Config.h"
#include "SessionManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

ApiClient::ApiClient(SessionManager *session, QObject *parent)
    : QObject(parent)
    , m_session(session)
    , m_baseUrl(QString::fromLatin1(Config::kDefaultBaseUrl))
{
}

QNetworkRequest ApiClient::makeRequest(const QString &path, bool authorized) const
{
    QString base = m_baseUrl;
    while (base.endsWith('/'))
        base.chop(1);

    QNetworkRequest req{QUrl(base + path)};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    if (authorized && m_session && !m_session->accessToken().isEmpty()) {
        req.setRawHeader("Authorization",
                         "Bearer " + m_session->accessToken().toUtf8());
    }
    return req;
}

void ApiClient::get(const QString &path, ApiCallback callback, bool authorized)
{
    handleReply(m_nam.get(makeRequest(path, authorized)), std::move(callback));
}

void ApiClient::post(const QString &path, const QJsonObject &body, ApiCallback callback,
                     bool authorized)
{
    const QByteArray payload = QJsonDocument(body).toJson(QJsonDocument::Compact);
    handleReply(m_nam.post(makeRequest(path, authorized), payload), std::move(callback));
}

void ApiClient::handleReply(QNetworkReply *reply, ApiCallback callback)
{
    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        reply->deleteLater();

        ApiResponse res;
        res.status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        res.json = QJsonDocument::fromJson(reply->readAll()).object();
        res.ok = (reply->error() == QNetworkReply::NoError);

        if (!res.ok) {
            // Format error Directus: {"errors":[{"message":"..."}]}
            res.errorMessage = res.json.value(QStringLiteral("errors")).toArray()
                                   .first().toObject()
                                   .value(QStringLiteral("message")).toString();
            if (res.errorMessage.isEmpty())
                res.errorMessage = reply->errorString();
        }

        if (callback)
            callback(res);
    });
}
