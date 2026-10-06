#include "UserDashboardViewModel.h"
#include "LicenseService.h"
#include "LicenseListModel.h"
#include <QDebug>

UserDashboardViewModel::UserDashboardViewModel(LicenseService *service, QObject *parent)
    : QObject(parent)
    , m_service(service)
    , m_model(new LicenseListModel(this))
{
    connect(m_service, &LicenseService::busyChanged, this, [this](){
        emit isLoadingChanged();
    });

    connect(m_service, &LicenseService::licenseFetched, this, [this](const QList<License> &licenses) {
        m_model->setLicenses(licenses);
        setErrorMessage(QString());
    });

    connect(m_service, &LicenseService::fetchFailed, this, [this](const QString &error) {
        setErrorMessage(error);
        qWarning() << "Gagal mengambil lisensi:" << error;
    });
}

bool UserDashboardViewModel::isLoading() const {
    return m_service->busy();
}

void UserDashboardViewModel::setErrorMessage(const QString &message){
    if (m_errorMessage == message)
        return;
    m_errorMessage = message;
    emit errorMessageChanged();
}

void UserDashboardViewModel::refresh()
{
    setErrorMessage(QString());
    m_service->fetchMyLicense();
}

void UserDashboardViewModel::buyLicense()
{
    qDebug() << "INI UNTUK BUY LICENSE DARI VIEWMODEL";
}
