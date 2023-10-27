#ifndef HISTORYSERVICE_H
#define HISTORYSERVICE_H

#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QJsonDocument>

#include "src/models/medialistitem.h"
#include "src/viewmodels/medialistmodel.h"
#include "src/settings.h"

class HistoryService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MediaListModel* list READ getList CONSTANT)
    Q_PROPERTY(bool hasMore READ getHasMore WRITE setHasMore NOTIFY hasMoreChanged)
public:
    HistoryService(QList<Genre> &allGenres, const Settings &settings, QObject *parent);

    void add(MediaListItem::MediaType mediaType, int id, const QByteArray &apiResponse);
    Q_INVOKABLE void load();
    Q_INVOKABLE void loadMore();
    Q_INVOKABLE void clear();

    MediaListModel *getList() const;

    bool getHasMore() const;
    void setHasMore(bool newHasMore);

private:
    QSqlDatabase db;
    MediaListModel *list;
    const int daysLimit;
    QList<Genre> &allGenres;
    const Settings &settings;
    uint page;
    uint maxPage;
    const uint limitPerPage;
    bool hasMore;

    void loadPage();
    void add(int mediaType, int id, const QByteArray &apiResponse);
    void insert(int mediaType, int id, const QByteArray &apiResponse);
    void deleteRecords(int mediaType, int id);
    void deleteOld();

signals:
    void hasMoreChanged();
};

#endif // HISTORYSERVICE_H
