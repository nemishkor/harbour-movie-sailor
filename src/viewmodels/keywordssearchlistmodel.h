#ifndef KEYWORDSSEARCHLISTMODEL_H
#define KEYWORDSSEARCHLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/keyword.h"

class KeywordsSearchListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum KeywordSearchRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        SelectedRole
    };
    explicit KeywordsSearchListModel(const QList<Keyword> &selection, QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void selectChanged(const Keyword &item);
    void add(const Keyword &item);
    Q_INVOKABLE void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);
    const QList<Keyword> &getItems() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Keyword> items;
    const QList<Keyword> &selection;
};

#endif // KEYWORDSSEARCHLISTMODEL_H
