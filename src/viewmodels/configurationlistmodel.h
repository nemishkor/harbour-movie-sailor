#ifndef CONFIGURATIONLISTMODEL_H
#define CONFIGURATIONLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/configuration.h"

class ConfigurationListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum ConfigurationRoles {
        IdRole = Qt::UserRole + 1,
        LabelRole,
        SectionRole,
        PrimaryRole
    };
    explicit ConfigurationListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Configuration &item);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Configuration> items;

signals:
    void countChanged();
};

#endif // CONFIGURATIONLISTMODEL_H
