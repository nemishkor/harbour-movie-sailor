#include "keywordsservice.h"

KeywordsService::KeywordsService(Api &api, FileCache &cache, KeywordsListModel *model, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("search", "keyword", "1"),
    model(model),
    searchModel(this->model->getItems(), this),
    initialized(false)
{
    connect(&api, &Api::keywordsDone, this, &KeywordsService::apiRequestDone);
}

void KeywordsService::search(const QString &query, int page)
{
    QString newKey = query + "|" + QString::number(page);
    qDebug() << "search keywords" << newKey;

    if (key.key != newKey) {
        key.key = newKey;
        searchModel.clear();
        setInitialized(false);
    }

    if (query.isEmpty() || initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "load search keywords from cache";
        searchModel.fillFromCache(cache.load(key));
        setInitialized(true);
        return;
    }

    api.loadKeywords(query, page);
}

void KeywordsService::select(int id)
{
    const Keyword &keyword = searchModel.getItems()[searchModel.getItems().indexOf(Keyword(id, ""))];
    if (model->getItems().indexOf(keyword) == -1) {
        model->add(keyword);
        searchModel.selectChanged(keyword);
    }
}

void KeywordsService::unselect(int id)
{
    model->remove(Keyword(id, ""));
    searchModel.selectChanged(Keyword(id, ""));
}

KeywordsSearchListModel *KeywordsService::getSearchModel()
{
    return &searchModel;
}

bool KeywordsService::isInitialized()
{
    return initialized;
}

void KeywordsService::setInitialized(bool newInitialized)
{
    if (initialized == newInitialized)
        return;
    initialized = newInitialized;
    emit initializedChanged();
}

void KeywordsService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "keywords api request is done";
    QJsonDocument newJson = searchModel.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
