#include "companiessearchlistmodel.h"

CompaniesSearchListModel::CompaniesSearchListModel(FilterByCompaniesListModel &model, QObject *parent) :
    FilterByCompaniesListModel(parent),
    model(model)
{

}

Company CompaniesSearchListModel::findById(int id)
{
    for (QList<Company>::const_iterator it = items.constBegin(); it != items.constEnd(); it++){
        if(it->getId() == id) {
            return *it;
        }
    }

    return Company(-1, "", "", "");
}

void CompaniesSearchListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray items = json.array();

    for (QJsonArray::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        qDebug() << "add company to the view list model from cache";
        QJsonObject obj = (*it).toObject();
        Company item(obj);
        if (!model.getIds().contains(item.getId())) {
            add(item);
        }
    }
    qDebug() << "all companies are loaded to list model";
}

const QJsonDocument CompaniesSearchListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QJsonArray newJsonItems;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject obj = (*it).toObject();
        QJsonObject newObj;
        newObj.insert("id", obj["id"].toInt());
        newObj.insert("logo", obj["logo_path"].toString());
        newObj.insert("name", obj["name"].toString());
        newObj.insert("country", obj["origin_country"].toString());
        Company item(newObj);
        if (!model.getIds().contains(item.getId())) {
            add(item);
        }
        newJsonItems.append(newObj);
    }

    return QJsonDocument(newJsonItems);
}
