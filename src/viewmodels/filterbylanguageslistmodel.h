#ifndef FILTERBYLANGUAGESLISTMODEL_H
#define FILTERBYLANGUAGESLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/system.h"
#include "src/models/filterbylanguagelistitem.h"

class FilterByLanguagesListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum LanguageRoles {
        IdRole = Qt::UserRole + 1,
        EnglishNameRole,
        NameRole,
        SectionRole,
        PrimaryRole
    };

    FilterByLanguagesListModel(System &system, QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const FilterByLanguageListItem &language);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QList<FilterByLanguageListItem> &getItems() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    System &system;
    QList<FilterByLanguageListItem> items;

signals:
    void countChanged();
};

#endif // FILTERBYLANGUAGESLISTMODEL_H
