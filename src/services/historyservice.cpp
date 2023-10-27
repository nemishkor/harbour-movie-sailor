#include "historyservice.h"

HistoryService::HistoryService(QList<Genre> &allGenres, const Settings &settings, QObject *parent) :
    QObject(parent),
    list(new MediaListModel(this)),
    daysLimit(-100),
    allGenres(allGenres),
    settings(settings),
    page(1),
    limitPerPage(30),
    hasMore(false)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/database.db";
    qDebug() << "HistoryService: connect to the database" << path;
    db.setDatabaseName(path);
    if (!db.open()) {
        qWarning() << "HistoryService: connection with database failed" << path;
    } else {
        QSqlQuery createHistoryTable = db.exec(
                    "CREATE TABLE IF NOT EXISTS history ("
                    "media_type INTEGER NOT NULL, "
                    "id INTEGER NOT NULL, "
                    "datetime INTEGER NOT NULL, "
                    "apiResponse TEXT NOT NULL)");
        if (createHistoryTable.lastError().isValid()) {
            qDebug() << "HistoryService: could not create table" << createHistoryTable.lastError();
        }
    }
}

void HistoryService::add(MediaListItem::MediaType mediaType, int id, const QByteArray &apiResponse)
{
    if (!settings.getViewedMediaHistoryEnabled())
        return;

    switch (mediaType) {
    case MediaListItem::Unknown:
        return;
    case MediaListItem::MovieType:
        add(1, id, apiResponse);
        break;
    case MediaListItem::TvType:
        add(2, id, apiResponse);
        break;
    case MediaListItem::PersonType:
        add(3, id, apiResponse);
        break;
    }
}

void HistoryService::load()
{
    qDebug() << "HistoryService: load - start";

    if (!list->getDirty())
        return;

    page = 1;
    list->clear();

    QSqlQuery totalQuery(db);
    totalQuery.prepare("SELECT COUNT() AS ctn FROM history");
    totalQuery.exec();
    totalQuery.first();
    int total = totalQuery.value(0).toInt();
    maxPage = ceil((float)total / limitPerPage);
    setHasMore(page < maxPage);

    loadPage();

    list->setDirty(false);
    qDebug() << "HistoryService: load - done";
}

void HistoryService::loadMore()
{
    qDebug() << "HistoryService: loadMore - start";
    page++;
    setHasMore(page < maxPage);
    loadPage();
    qDebug() << "HistoryService: loadMore - done";
}

void HistoryService::clear()
{
    list->clear();
    QSqlQuery query(db);
    query.prepare("DELETE FROM history");
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: clear failed:" << query.lastError().text();
}

MediaListModel *HistoryService::getList() const
{
    return list;
}

bool HistoryService::getHasMore() const
{
    return hasMore;
}

void HistoryService::setHasMore(bool newHasMore)
{
    if (hasMore == newHasMore)
        return;
    hasMore = newHasMore;
    emit hasMoreChanged();
}

void HistoryService::loadPage()
{
    QSqlQuery query(db);
    query.prepare("SELECT media_type, id, datetime, apiResponse FROM history ORDER BY datetime DESC LIMIT ? OFFSET ?");
    query.addBindValue(limitPerPage);
    query.addBindValue((page - 1) * limitPerPage);
    bool result = query.exec();
    if (!result) {
        qWarning() << "HistoryService: load failed";
        return;
    }
    while (query.next()) {
        int mediaType = query.value(0).toInt();
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch((qint64)query.value(2).toInt() * 1000, Qt::UTC).toLocalTime();
        QJsonObject json = QJsonDocument::fromJson(query.value(3).toString().toUtf8()).object();
        list->add(allGenres, json, static_cast<MediaListItem::MediaType>(mediaType), dateTime);
    }
}

void HistoryService::add(int mediaType, int id, const QByteArray &apiResponse)
{
    deleteRecords(mediaType, id);
    insert(mediaType, id, apiResponse);
    deleteOld();
    list->setDirty(true);
}

void HistoryService::insert(int mediaType, int id, const QByteArray &apiResponse)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO history (media_type, id, datetime, apiResponse) VALUES (?, ?, ?, ?)");
    query.addBindValue(mediaType);
    query.addBindValue(id);
    query.addBindValue((int) (QDateTime::currentMSecsSinceEpoch() / 1000));
    query.addBindValue(apiResponse);
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: insert failed:" << query.lastError().text();
}

void HistoryService::deleteRecords(int mediaType, int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM history WHERE media_type = ? AND id = ?");
    query.addBindValue(mediaType);
    query.addBindValue(id);
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: deleteRecords failed:" << query.lastError().text();
}

void HistoryService::deleteOld()
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM history WHERE datetime < ?");
    query.addBindValue((int) (QDateTime::currentDateTimeUtc().addDays(-1 * settings.getViewedMediaHistoryDaysLimit()).toMSecsSinceEpoch() / 1000));
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: deleteOld failed:" << query.lastError().text();
}
