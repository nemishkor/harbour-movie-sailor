#include "searchservice.h"

SearchService::SearchService(Api &api,
                             MovieService &movieService,
                             TvService &tvService,
                             PersonService &personService,
                             GenresListModel *genresListModel,
                             QObject *parent) :
    QObject(parent),
    apiWorkerName(Api::SearchMedia),
    api(api),
    movieService(movieService),
    tvService(tvService),
    personService(personService),
    genresListModel(genresListModel),
    form(new SearchForm(this)),
    request(api.getRequestInfo(apiWorkerName)),
    list(new MediaListModel(this))
{
    connect(&api, &Api::searchMediaDone, this, &SearchService::fillFromApi);
}

void SearchService::search()
{
    qDebug() << "SearchService: search";
    if (list->getDirty() || form->isDirty()) {
        list->clear();
        form->setPage(1);
    }

    list->setDirty(false);
    form->setDirty(false);

    qDebug() << "type" << form->getType();
    api.searchMedia(apiWorkerName, *form);
}

void SearchService::select(int id)
{
    qDebug() << "SearchService: select" << id;
    QList<MediaListItem>::const_iterator it;
    for (it = list->getItems().constBegin(); it != list->getItems().constEnd(); it++) {
        if (it->getId() == id) {
            qDebug() << "SearchService: media is found";
            switch (it->getMediaType()) {
            case MediaListItem::Unknown:
                qWarning() << "Unknown media type of the media entity" << it->getId();
                break;
            case MediaListItem::MovieType:
                movieService.fillWithListItemAndLoad(*it);
                break;
            case MediaListItem::TvType:
                tvService.fillWithListItemAndLoad(*it);
                break;
            case MediaListItem::PersonType:
                break;
            }
            return;
        }
    }
}

SearchForm *SearchService::getForm() const
{
    return form;
}

RequestInfo *SearchService::getRequest() const
{
    return request;
}

MediaListModel *SearchService::getList() const
{
    return list;
}

void SearchService::fillFromApi(QByteArray &data)
{
    qDebug() << "SearchService: search - got data";
    MediaListItem::MediaType mediaType = MediaListItem::MediaType::MovieType;
    switch (form->getType()) {
    case SearchForm::Any:
        break;
    case SearchForm::Movie:
        mediaType = MediaListItem::MediaType::MovieType;
        break;
    case SearchForm::Tv:
        mediaType = MediaListItem::MediaType::TvType;
        break;
    case SearchForm::Person:
        mediaType = MediaListItem::MediaType::PersonType;
        break;
    }
    list->fillFromAPI(QJsonDocument::fromJson(data), genresListModel->getItems(), mediaType);
    qDebug() << "SearchService: search - done";
}

