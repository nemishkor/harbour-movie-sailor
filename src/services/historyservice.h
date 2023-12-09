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
    Q_PROPERTY(QStringList searchList READ getSearchList WRITE setSearchList NOTIFY searchListChanged)
public:
    HistoryService(QList<Genre> &allGenres, const Settings &settings, QObject *parent);

    void add(MediaListItem::MediaType mediaType, int id, const QByteArray &apiResponse);
    void addSearch(SearchForm::MediaType mediaType, QString term);
    Q_INVOKABLE void load();
    Q_INVOKABLE void loadMore();
    Q_INVOKABLE void loadSearchHistory(SearchForm &form);
    Q_INVOKABLE void clear();

    MediaListModel *getList() const;

    bool getHasMore() const;
    void setHasMore(bool newHasMore);

    const QStringList &getSearchList() const;
    void setSearchList(const QStringList &newSearchHistory);

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
    QStringList searchList;

    void loadPage();
    void add(int mediaType, int id, const QByteArray &apiResponse);
    void addSearch(int mediaType, const QString &term);
    void insert(int mediaType, int id, const QByteArray &apiResponse);
    void insertSearch(int mediaType, const QString &term);
    void deleteRecords(int mediaType, int id);
    void deleteSearchRecords(int mediaType, const QString &term);
    void deleteOld();
    void deleteOldSearch();

signals:
    void hasMoreChanged();
    void searchListChanged();
};

#endif // HISTORYSERVICE_H
