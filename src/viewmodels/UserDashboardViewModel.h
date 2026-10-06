#pragma once

#include <QObject>

class LicenseService;
class LicenseListModel;

class UserDashboardViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LicenseListModel* licenseModel READ licenseModel CONSTANT)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoading FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessage FINAL)

public :
    explicit UserDashboardViewModel(LicenseService *service, QObject *parent = nullptr);

    LicenseListModel* licenseModel() const {return m_model;}
    bool isLoading() const ;
    QString errorMessage() const {return m_errorMessage;}

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void buyLicense();

signals :
    void isLoadingChanged();
    void errorMessageChanged();


private :
    void setErrorMessage(const QString &message);

    LicenseService *m_service;
    LicenseListModel *m_model;
    QString m_errorMessage;
};
