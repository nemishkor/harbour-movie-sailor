#ifndef COMPANIESLISTMODEL_H
#define COMPANIESLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMutableMapIterator>

#include "src/models/company.h"

class CompaniesListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool andMode READ getAndMode WRITE setAndMode NOTIFY andModeChanged)
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)
public:
    explicit CompaniesListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Company &item);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void removeOneById(int id);
    const QList<int> &getIds() const;

    bool getAndMode() const;
    void setAndMode(bool newAndMode);

    const QString &getSummary() const;
    void setSummary(const QString &newSummary);

    const QString toQueryString();

protected:
    enum CompanyRoles {
        IdRole = Qt::UserRole + 1,
        LogoRole,
        NameRole,
        CountryRole
    };
    QList<Company> items;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<int> ids;
    bool andMode;
    QString summary;
    void updateSummary();

signals:
    void countChanged();
    void summaryChanged();
    void andModeChanged();
};

#endif // COMPANIESLISTMODEL_H
