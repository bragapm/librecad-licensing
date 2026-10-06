#include "AppViewModel.h"
#include "AuthService.h"
#include "SessionManager.h"

AppViewModel::AppViewModel(SessionManager *session, AuthService *auth, QObject *parent)
    : QObject(parent)
    , m_session(session)
    , m_auth(auth)
    , m_currentPage(QStringLiteral("login"))
{
    connect(m_session, &SessionManager::sessionChanged, this, &AppViewModel::refresh);
    refresh();
}

QString AppViewModel::userEmail() const
{
    return m_session->userEmail();
}

void AppViewModel::refresh()
{
    QString page = QStringLiteral("login");
    if (m_session->loggedIn()) {
        page = m_session->isAdmin() ? QStringLiteral("adminDashboard")
                                    : QStringLiteral("userDashboard");
    }

    if (page != m_currentPage) {
        m_currentPage = page;
        emit currentPageChanged();
    }
    emit userEmailChanged();
}

void AppViewModel::logout()
{
    m_auth->logout();
}
