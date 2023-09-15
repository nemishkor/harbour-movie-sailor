#include "personservice.h"

PersonService::PersonService(Api &api, QObject *parent) :
    QObject(parent),
    apiWorkerName(Api::LoadPerson),
    api(api),
    model(new Person(this)),
    request(api.getRequestInfo(apiWorkerName))
{

}

void PersonService::fillAndLoad(const PersonListItem &result)
{
    qDebug() << "PersonService: fill" << result.getId();
    model->setAlsoKnownAs(QStringList());
    model->setBiography("");
    model->setBirthday("");
    model->setDeathday("");
    model->setHomepage("");
    model->setId(result.getId());
    model->setImdbId("");
    model->setKnownForDepartment("");
    model->setName(result.getName());
    model->setPlaceOfBirth("");
    model->setProfilePath(result.getProfilePath());
    model->setFreebaseId("");
    model->setFreebaseMid("");
    model->setTvrageId(0);
    model->setWikidataId("");
    model->setFacebookId("");
    model->setInstagramId("");
    model->setTiktokId("");
    model->setTwitterId("");
    model->setYoutubeId("");
    model->setImages(QStringList());
    qDebug() << "PersonService: load from API";
    api.getResource(apiWorkerName, form);
}

void PersonService::fillAndLoad(const MediaListItem &result)
{
    qDebug() << "PersonService: fill" << result.getId();
    model->setAlsoKnownAs(QStringList());
    model->setBiography("");
    model->setBirthday("");
    model->setDeathday("");
    model->setHomepage("");
    model->setId(result.getId());
    model->setImdbId("");
    model->setKnownForDepartment(result.getKnownForDepartment());
    model->setName(result.getTitle());
    model->setPlaceOfBirth("");
    model->setProfilePath(result.getPosterPath());
    model->setFreebaseId("");
    model->setFreebaseMid("");
    model->setTvrageId(0);
    model->setWikidataId("");
    model->setFacebookId("");
    model->setInstagramId("");
    model->setTiktokId("");
    model->setTwitterId("");
    model->setYoutubeId("");
    model->setImages(QStringList());
    qDebug() << "PersonService: load from API";
    api.getResource(apiWorkerName, form);
}

Person *PersonService::getModel() const
{
    return model;
}

RequestInfo *PersonService::getRequest() const
{
    return request;
}

void PersonService::apiRequestDone(QByteArray &data)
{
    qDebug() << "PersonService: load from API - got data";
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    QJsonArray::const_iterator it;
    QJsonArray items = obj["also_known_as"].toArray();

    QStringList alsoKnownAs;
    for (it = items.constBegin(); it != items.constEnd(); it++) {
        alsoKnownAs.append(it->toString());
    }

    model->setAlsoKnownAs(alsoKnownAs);
    model->setBiography(obj["biography"].toString());
    model->setBirthday(obj["birthday"].toString());
    model->setDeathday(obj["deathday"].toString());
    model->setHomepage(obj["homepage"].toString());
    model->setImdbId(obj["imdb_id"].toString());
    model->setKnownForDepartment(obj["known_for_department"].toString());
    model->setPlaceOfBirth(obj["place_of_birth"].toString());

    if (obj.contains("external_ids") && obj["external_ids"].isObject()) {
        QJsonObject externalIds = obj["external_ids"].toObject();
        model->setFreebaseId(externalIds["freebase_id"].toString());
        model->setFreebaseMid(externalIds["freebase_mid"].toString());
        model->setTvrageId(externalIds["tvrage_id"].toInt());
        model->setWikidataId(externalIds["wikidata_id"].toString());
        model->setFacebookId(externalIds["facebook_id"].toString());
        model->setInstagramId(externalIds["instagram_id"].toString());
        model->setTiktokId(externalIds["tiktok_id"].toString());
        model->setTwitterId(externalIds["twitter_id"].toString());
        model->setYoutubeId(externalIds["youtube_id"].toString());
    }

    items = obj["images"].toObject()["profiles"].toArray();
    QStringList images;
    for (it = items.constBegin(); it != items.constEnd(); it++) {
        images.append(it->toObject()["file_path"].toString());
    }
    model->setImages(images);
    qDebug() << "PersonService: load from API - done";
}
