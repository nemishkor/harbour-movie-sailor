#ifndef KEYWORDSSERVICE_H
#define KEYWORDSSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/keywordslistmodel.h"
#include "src/viewmodels/keywordssearchlistmodel.h"

class KeywordsService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    explicit KeywordsService(Api &api, FileCache &cache, QObject *parent);
    Q_INVOKABLE void search(const QString &query, int page = 1);
    Q_INVOKABLE void select(int id);
    Q_INVOKABLE void unselect(int id);
    KeywordsListModel *getModel();
    KeywordsSearchListModel *getSearchModel();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    KeywordsListModel model;
    KeywordsSearchListModel searchModel;
    bool initialized;
    void setInitialized(bool newInitialized);

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();

};

#endif // KEYWORDSSERVICE_H
