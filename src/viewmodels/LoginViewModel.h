#pragma once

#include <QObject>
#include <QString>

class AuthService;

// State halaman login: isi form, pesan error, status loading, dan aksi submit.
// Dipakai di QML sebagai singleton: LoginViewModel.email, LoginViewModel.submit(), dst.
class LoginViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged FINAL)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged FINAL)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged FINAL)
    Q_PROPERTY(bool canSubmit READ canSubmit NOTIFY canSubmitChanged FINAL)

public:
    explicit LoginViewModel(AuthService *auth, QObject *parent = nullptr);

    QString email() const { return m_email; }
    QString password() const { return m_password; }
    QString errorMessage() const { return m_errorMessage; }
    bool isLoading() const;
    bool canSubmit() const;

    void setEmail(const QString &email);
    void setPassword(const QString &password);

    Q_INVOKABLE void submit();

signals:
    void emailChanged();
    void passwordChanged();
    void errorMessageChanged();
    void isLoadingChanged();
    void canSubmitChanged();

private:
    void setErrorMessage(const QString &message);

    AuthService *m_auth;
    QString m_email;
    QString m_password;
    QString m_errorMessage;
};
