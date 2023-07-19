#ifndef LANGUAGESLISTMODEL_H
#define LANGUAGESLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

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

    explicit LanguagesListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Language &language);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Language> items;

signals:
    void countChanged();
};

#endif // LANGUAGESLISTMODEL_H
