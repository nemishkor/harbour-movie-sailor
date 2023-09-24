#ifndef LANGUAGESLISTMODEL_H
#define LANGUAGESLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/system.h"
#include "src/models/language.h"

class LanguagesListModel : public QAbstractListModel
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

    explicit LanguagesListModel(System &system, QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Language &language);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    System &system;
    QList<Language> items;

signals:
    void countChanged();
};

#endif // LANGUAGESLISTMODEL_H
