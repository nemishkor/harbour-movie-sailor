#ifndef PEOPLELISTMODEL_H
#define PEOPLELISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/searchpersonlistitem.h"

class PeopleListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool andMode READ getAndMode WRITE setAndMode NOTIFY andModeChanged)
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)
public:
    enum CastRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        KnownForDepartment,
        ProfilePath
    };
    explicit PeopleListModel(QObject *parent);

    Q_INVOKABLE void remove(int id);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const SearchPersonListItem &item);
    void clear();

    const QString &getSummary() const;
    void setSummary(const QString &newSummary);

    bool getAndMode() const;
    void setAndMode(bool newAndMode);

    const QList<int> &getIds() const;

    const QString toQueryString();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<SearchPersonListItem> items;
    QList<int> ids;
    QString summary;
    bool andMode;
    void updateSummary();

signals:
    void countChanged();
    void summaryChanged();
    void andModeChanged();
};

#endif // PEOPLELISTMODEL_H
