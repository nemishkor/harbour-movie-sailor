#ifndef GENRESMOVIESERVICE_H
#define GENRESMOVIESERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/settings.h"
#include "src/system.h"
#include "src/viewmodels/genreslistmodel.h"

class GenresMovieService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    GenresMovieService(Api &api, FileCache &cache, Settings &settings, QObject *parent);
    Q_INVOKABLE void initialize();
    GenresListModel *getModel();
    void setInitialized(bool newInitialized);
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    Settings &settings;
    CacheKey key;
    GenresListModel *model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();

};

#endif // GENRESMOVIESERVICE_H
