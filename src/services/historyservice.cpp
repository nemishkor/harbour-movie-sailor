#include "historyservice.h"

HistoryService::HistoryService(QList<Genre> &allGenres, const Settings &settings, QObject *parent) :
    QObject(parent),
    list(new MediaListModel(this)),
    daysLimit(-100),
    allGenres(allGenres),
    settings(settings),
    page(1),
    limitPerPage(30),
    hasMore(false),
    lastHistoryItem(new Media(this))
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
            qDebug() << "HistoryService: could not create table history" << createHistoryTable.lastError();
        }
        QSqlQuery createSearchHistoryTable = db.exec(
                    "CREATE TABLE IF NOT EXISTS search_history ("
                    "media_type INTEGER NOT NULL, "
                    "datetime INTEGER NOT NULL, "
                    "term TEXT NOT NULL)");
        if (createSearchHistoryTable.lastError().isValid()) {
            qDebug() << "HistoryService: could not create table search_history" << createSearchHistoryTable.lastError();
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

void HistoryService::addSearch(SearchForm::MediaType mediaType, QString term)
{
    if (!settings.getMediaSearchHistoryEnabled())
        return;

    switch (mediaType) {
    case SearchForm::MediaType::Any:
        addSearch(0, term);
        break;
    case SearchForm::MediaType::Movie:
        addSearch(1, term);
        break;
    case SearchForm::MediaType::Tv:
        addSearch(2, term);
        break;
    case SearchForm::MediaType::Person:
        addSearch(3, term);
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

void HistoryService::loadSearchHistory(SearchForm &form)
{
    searchList.clear();
    QSqlQuery query(db);
    query.prepare("SELECT term FROM search_history WHERE media_type = ? ORDER BY datetime DESC LIMIT ?");
    switch (form.getType()) {
    case SearchForm::MediaType::Any:
        query.addBindValue(0);
        break;
    case SearchForm::MediaType::Movie:
        query.addBindValue(1);
        break;
    case SearchForm::MediaType::Tv:
        query.addBindValue(2);
        break;
    case SearchForm::MediaType::Person:
        query.addBindValue(3);
        break;
    }
    query.addBindValue(10);
    bool result = query.exec();
    if (!result) {
        qWarning() << "HistoryService: search load failed";
        return;
    }
    while (query.next()) {
        searchList.append(query.value(0).toString());
    }
    qInfo() << "HistoryService: search history count" << searchList.count();
    emit searchListChanged();
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

void HistoryService::loadLastHistoryItem()
{
    lastHistoryItem->setId(0);
    QSqlQuery query(db);
    query.prepare("SELECT media_type, id, datetime, apiResponse FROM history ORDER BY datetime DESC LIMIT 1");
    bool result = query.exec();
    if (!result) {
        qWarning() << "HistoryService: loading of last history item has failed";
        return;
    }
    while (query.next()) {


        lastHistoryItem->setMediaType(static_cast<Media::MediaType>(query.value(0).toInt()));
        lastHistoryItem->setId(query.value(1).toInt());
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch((qint64)query.value(2).toInt() * 1000, Qt::UTC).toLocalTime();
        QJsonObject json = QJsonDocument::fromJson(query.value(3).toString().toUtf8()).object();
        QDateTime createdDate = dateTime.toLocalTime();
        lastHistoryItem->setHistoryDateTime(createdDate.toLocalTime().toString(QLocale::system().dateTimeFormat(QLocale::ShortFormat)));

        if (lastHistoryItem->getMediaType() == Media::TvType) {
            lastHistoryItem->setName(json["name"].toString());
            lastHistoryItem->setImagePath(json["poster_path"].toString());
        } else if (lastHistoryItem->getMediaType() == Media::PersonType) {
            lastHistoryItem->setName(json["name"].toString());
            lastHistoryItem->setImagePath(json["profile_path"].toString());
        } else {
            lastHistoryItem->setName(json["title"].toString());
            lastHistoryItem->setImagePath(json["poster_path"].toString());
        }

        qInfo() << "HistoryService: last history item was loaded" << lastHistoryItem->getId();
        break;
    }
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

const QStringList &HistoryService::getSearchList() const
{
    return searchList;
}

void HistoryService::setSearchList(const QStringList &newSearchHistory)
{
    if (searchList == newSearchHistory)
        return;
    searchList = newSearchHistory;
    emit searchListChanged();
}

Media *HistoryService::getLastHistoryItem() const
{
    return lastHistoryItem;
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

void HistoryService::addSearch(int mediaType, const QString &term)
{
    deleteSearchRecords(mediaType, term);
    insertSearch(mediaType, term);
    deleteOldSearch();
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

void HistoryService::insertSearch(int mediaType, const QString &term)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO search_history (media_type, datetime, term) VALUES (?, ?, ?)");
    query.addBindValue(mediaType);
    query.addBindValue((int) (QDateTime::currentMSecsSinceEpoch() / 1000));
    query.addBindValue(term);
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: insertSearch failed:" << query.lastError().text();
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

void HistoryService::deleteSearchRecords(int mediaType, const QString &term)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM search_history WHERE media_type = ? AND term = ?");
    query.addBindValue(mediaType);
    query.addBindValue(term);
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: deleteSearchRecords failed:" << query.lastError().text();
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

void HistoryService::deleteOldSearch()
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM search_history WHERE datetime < ?");
    query.addBindValue((int) (QDateTime::currentDateTimeUtc().addDays(-90).toMSecsSinceEpoch() / 1000));
    bool result = query.exec();
    if (!result)
        qWarning() << "HistoryService: deleteOldSearch failed:" << query.lastError().text();
}
