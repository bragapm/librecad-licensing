#include "LicenseListModel.h"

LicenseListModel::LicenseListModel(QObject *parent)
    : QAbstractListModel(parent)
{ }

// ngasih baris
int LicenseListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return m_licenses.count();
}

QVariant LicenseListModel::data(const QModelIndex &index, int role) const
{
    // membuat QVariant data jika index row < 0 || indexrow > banyaknya lisense
    if (!index.isValid() || index.row() < 0 || index.row() >= m_licenses.count())
        return QVariant();
    const License &item = m_licenses[index.row()];
    switch (role)
    {
    case appNameRoles:
        return item.appName;
    case LicenseKeyRole :
        return item.licenseKey;
    case StatusRole :
        return item.status;
    case ExpiresAtRole :
        return item.expiresAt;
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> LicenseListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[appNameRoles] = "appName";
    roles[LicenseKeyRole] = "licenseKey";
    roles[StatusRole] = "status";
    roles[ExpiresAtRole] = "expiresAt";
    return roles;
}

void LicenseListModel::setLicenses(const QList<License> &licenses)
{
    beginResetModel();
    m_licenses = licenses;
    endResetModel();
}

void LicenseListModel::clear()
{
    beginResetModel();
    m_licenses.clear();
    endResetModel();
}