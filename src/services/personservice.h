#ifndef PERSONSERVICE_H
#define PERSONSERVICE_H

#include <QObject>

#include "src/api.h"
#include "src/models/crewlistitem.h"
#include "src/models/crewlistitem.h"
#include "src/models/loadpersonform.h"
#include "src/models/person.h"
#include "src/models/personlistitem.h"
#include "src/models/requestinfo.h"
#include "src/models/medialistitem.h"
#include "src/services/historyservice.h"

class PersonService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)

public:
    PersonService(Api &api,
                  GenresListModel *genresListModel,
                  HistoryService &historyService,
                  QObject *parent);

    Q_INVOKABLE void load(Person *person, int id);

    RequestInfo *getRequest() const;

signals:
    void personIsLoaded(Person *model);
    void personIsDestroyed();

private:
    const Api::WorkerName apiWorkerName;
    Api &api;
    HistoryService &historyService;
    GenresListModel *genresListModel;
    Person *model;
    RequestInfo *request;
    LoadPersonForm form;

private slots:
    void apiRequestDone(QByteArray &data);
};

#endif // PERSONSERVICE_H
