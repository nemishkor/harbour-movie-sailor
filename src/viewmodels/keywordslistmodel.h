#ifndef KEYWORDSLISTMODEL_H
#define KEYWORDSLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QMutableListIterator>
#include "src/models/keyword.h"

class KeywordsListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool andMode READ getAndMode WRITE setAndMode NOTIFY andModeChanged)
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)
public:
    enum KeywordRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    explicit KeywordsListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Keyword &item);
    void remove(const Keyword &item);
    const QList<Keyword> &getItems() const;

    const QString &getSummary() const;

    bool getAndMode() const;
    void setAndMode(bool newAndMode);

    const QString toQueryString();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Keyword> items;
    QString summary;
    bool andMode;
    void setSummary(const QString &newSummary);
    void updateSummary();

signals:
    void countChanged();
    void summaryChanged();
    void andModeChanged();
};

#endif // KEYWORDSLISTMODEL_H
