#ifndef GENRESLISTMODEL_H
#define GENRESLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include "src/models/genre.h"

class GenresListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool andMode READ getAndMode WRITE setAndMode NOTIFY andModeChanged)
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)
public:
    enum GenreRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CheckedRole
    };
    explicit GenresListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void add(const Genre &item);
    void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);
    QList<Genre> &getItems();

    const QString &getSummary() const;
    void setSummary(const QString &newSummary);

    bool getAndMode() const;
    void setAndMode(bool newAndMode);

    QString toQueryString();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Genre> items;
    QString summary;
    bool andMode;
    void updateSummary();

signals:
    void countChanged();
    void summaryChanged();
    void andModeChanged();
};

#endif // GENRESLISTMODEL_H
