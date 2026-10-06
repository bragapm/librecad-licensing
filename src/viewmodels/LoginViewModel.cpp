#include "LoginViewModel.h"
#include "AuthService.h"

LoginViewModel::LoginViewModel(AuthService *auth, QObject *parent)
    : QObject(parent)
    , m_auth(auth)
{
    connect(m_auth, &AuthService::busyChanged, this, [this]() {
        emit isLoadingChanged();
        emit canSubmitChanged();
    });
    connect(m_auth, &AuthService::loginFailed, this, [this](const QString &message) {
        setErrorMessage(message);
    });
    connect(m_auth, &AuthService::loginSucceeded, this, [this]() {
        setErrorMessage(QString());
        setPassword(QString());
    });
}

bool LoginViewModel::isLoading() const
{
    return m_auth->busy();
}

bool LoginViewModel::canSubmit() const
{
    return !m_email.trimmed().isEmpty() && !m_password.isEmpty() && !isLoading();
}

void LoginViewModel::setEmail(const QString &email)
{
    if (m_email == email)
        return;
    m_email = email;
    emit emailChanged();
    emit canSubmitChanged();
}

void LoginViewModel::setPassword(const QString &password)
{
    if (m_password == password)
        return;
    m_password = password;
    emit passwordChanged();
    emit canSubmitChanged();
}

void LoginViewModel::setErrorMessage(const QString &message)
{
    if (m_errorMessage == message)
        return;
    m_errorMessage = message;
    emit errorMessageChanged();
}

void LoginViewModel::submit()
{
    setErrorMessage(QString());

    if (m_email.trimmed().isEmpty() || m_password.isEmpty()) {
        setErrorMessage(tr("Email dan password wajib diisi."));
        return;
    }

    m_auth->login(m_email.trimmed(), m_password);
}
