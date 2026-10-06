#pragma once

#include <QObject>
#include <QString>

// Menyimpan status sesi: token, email, dan role user yang sedang login.
// Satu-satunya tempat token disimpan; lapisan lain hanya membacanya.
class SessionManager : public QObject
{
    Q_OBJECT

public:
    explicit SessionManager(QObject *parent = nullptr);

    QString accessToken() const { return m_accessToken; }
    QString refreshToken() const { return m_refreshToken; }
    QString userEmail() const { return m_userEmail; }
    QString role() const { return m_role; }

    bool loggedIn() const { return !m_accessToken.isEmpty(); }
    bool isAdmin() const;

    void setTokens(const QString &accessToken, const QString &refreshToken);
    void setUser(const QString &email, const QString &role);
    void clear();

signals:
    // Dipancarkan setiap kali token, user, atau role berubah.
    void sessionChanged();

private:
    QString m_accessToken;
    QString m_refreshToken;
    QString m_userEmail;
    QString m_role;
};
