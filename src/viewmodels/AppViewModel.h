#pragma once

#include <QObject>
#include <QString>

class AuthService;
class SessionManager;

// State level aplikasi: halaman mana yang sedang tampil, dan siapa yang login.
// Dipakai di QML sebagai singleton: AppViewModel.currentPage, AppViewModel.logout().
class AppViewModel : public QObject
{
    Q_OBJECT
    // "login" | "userDashboard" | "adminDashboard"
    Q_PROPERTY(QString currentPage READ currentPage NOTIFY currentPageChanged FINAL)
    Q_PROPERTY(QString userEmail READ userEmail NOTIFY userEmailChanged FINAL)

public:
    AppViewModel(SessionManager *session, AuthService *auth, QObject *parent = nullptr);

    QString currentPage() const { return m_currentPage; }
    QString userEmail() const;

    Q_INVOKABLE void logout();

signals:
    void currentPageChanged();
    void userEmailChanged();

private:
    void refresh();

    SessionManager *m_session;
    AuthService *m_auth;
    QString m_currentPage;
};
