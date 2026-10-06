#pragma once

#include <QAbstractListModel>
#include <QList>
#include "License.h"

class LicenseListModel : public QAbstractListModel
{
    Q_OBJECT


public :
    enum LicenseRoles{
        appNameRoles = Qt::UserRole + 1,
        LicenseKeyRole,
        StatusRole,
        ExpiresAtRole
    };

    explicit LicenseListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // fungsi helper untuk update data lisensi dari c++
    void setLicenses(const QList<License> &licenses);
    void clear();

private:
    QList<License> m_licenses;
};
