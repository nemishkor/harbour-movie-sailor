#ifndef LANGUAGESLISTMODEL_H
#define LANGUAGESLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/languagelistitem.h"

class LanguagesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum LanguageRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    LanguagesListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const LanguageListItem &language);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<LanguageListItem> items;
};

#endif // LANGUAGESLISTMODEL_H
