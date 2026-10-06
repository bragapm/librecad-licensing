#pragma once

#include <QObject>
#include <QString>

class ApiClient;
class SessionManager;

// Alur autentikasi ke Directus: login, logout, ambil data user.
// Tidak tahu apa pun soal UI; hanya memancarkan sinyal hasil.
class AuthService : public QObject
{
    Q_OBJECT

public:
    AuthService(ApiClient *api, SessionManager *session, QObject *parent = nullptr);

    bool busy() const { return m_busy; }

    // Directus memakai email sebagai identitas login.
    void login(const QString &email, const QString &password);
    void logout();

signals:
    void busyChanged();
    void loginSucceeded();
    void loginFailed(const QString &message);

private:
    void setBusy(bool busy);
    void fetchCurrentUser();

    ApiClient *m_api;
    SessionManager *m_session;
    bool m_busy = false;
};
