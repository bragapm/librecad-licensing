#pragma once

#include <QObject>
#include <QList>
#include "License.h"

class ApiClient;
class SessionManager;

class LicenseService : public QObject
{
    Q_OBJECT
public :
    LicenseService(ApiClient *api, SessionManager *session, QObject *parent = nullptr);
    bool busy() const { return m_busy; }
    void fetchMyLicense();

signals :
    void busyChanged();
    void licenseFetched(const QList<License> &license);
    void fetchFailed(const QString &errorMessage);
private :
    void setBusy(bool busy);

    ApiClient *m_api;
    SessionManager *m_session;
    bool m_busy = false;

};
