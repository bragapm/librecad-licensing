#include "SessionManager.h"
#include "Config.h"

SessionManager::SessionManager(QObject *parent)
    : QObject(parent)
{
}

bool SessionManager::isAdmin() const
{
    return m_role.compare(QString::fromLatin1(Config::kAdminRoleName), Qt::CaseInsensitive) == 0;
}

void SessionManager::setTokens(const QString &accessToken, const QString &refreshToken)
{
    m_accessToken = accessToken;
    m_refreshToken = refreshToken;
    emit sessionChanged();
}

void SessionManager::setUser(const QString &email, const QString &role)
{
    m_userEmail = email;
    m_role = role;
    emit sessionChanged();
}

void SessionManager::clear()
{
    m_accessToken.clear();
    m_refreshToken.clear();
    m_userEmail.clear();
    m_role.clear();
    emit sessionChanged();
}
