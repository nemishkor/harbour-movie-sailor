#ifndef DISCOVERTVSERVICE_H
#define DISCOVERTVSERVICE_H

#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/models/discovertvform.h"
#include "src/models/loadtvwatchprovidersform.h"
#include "src/viewmodels/medialistmodel.h"

class DiscoverTvService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DiscoverTvForm* form READ getForm CONSTANT)
    Q_PROPERTY(bool watchProvidersInitialized READ getWatchProvidersInitialized WRITE setWatchProvidersInitialized NOTIFY watchProvidersInitializedChanged)
    Q_PROPERTY(RequestInfo* watchProvidersRequestInfo READ getWatchProvidersRequestInfo CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)
    Q_PROPERTY(MediaListModel* model READ getModel CONSTANT)
    Q_PROPERTY(bool initialized READ getInitialized WRITE setInitialized NOTIFY initializedChanged)

public:
    DiscoverTvService(Api &api,
                      GenresListModel *genres,
                      QObject *parent);

    Q_INVOKABLE void loadWatchProviders(DiscoverTvForm *tvDiscovery);
    Q_INVOKABLE void search(DiscoverTvForm *tvDiscovery = nullptr);
    Q_INVOKABLE void loadMore(); // search method have to be called first

    DiscoverTvForm *getForm() const;

    bool getWatchProvidersInitialized() const;
    void setWatchProvidersInitialized(bool newWatchProvidersInitialized);

    RequestInfo *getWatchProvidersRequestInfo() const;
    RequestInfo *getRequest() const;
    MediaListModel *getModel() const;

    bool getInitialized() const;
    void setInitialized(bool newInitialized);

signals:
    void watchProvidersInitializedChanged();
    void initializedChanged();

public slots:
    void searchDone(const QByteArray &data);
    void loadWatchProvidersDone(const QByteArray &data);

private:
    Api &api;
    GenresListModel &genres;
    DiscoverTvForm *form;
    bool watchProvidersInitialized;
    RequestInfo *watchProvidersRequestInfo;
    RequestInfo *request;
    MediaListModel *model;
    bool initialized;
};

#endif // DISCOVERTVSERVICE_H
