#include "filterbylanguageslistmodel.h"

FilterByLanguagesListModel::FilterByLanguagesListModel(System &system, QObject *parent) :
    QAbstractListModel(parent),
    system(system)
{

}

int FilterByLanguagesListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant FilterByLanguagesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const FilterByLanguageListItem &language = items[index.row()];
    if(role == IdRole)
        return language.getId();
    if(role == EnglishNameRole)
        return language.getEnglishName();
    if(role == NameRole)
        return language.getName();
    if(role == SectionRole)
        return language.getSection();
    if(role == PrimaryRole)
        return language.getIsPrimary();
    return QVariant();
}

void FilterByLanguagesListModel::add(const FilterByLanguageListItem &language)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(language);
    endInsertRows();
    emit countChanged();
}

void FilterByLanguagesListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray languages = json.array();
    for(QJsonArray::const_iterator it = languages.constBegin(); it != languages.constEnd(); it++){
        add(FilterByLanguageListItem((*it).toObject()));
    }
}

const QJsonDocument FilterByLanguagesListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonLanguages = json.array();
    QVector<FilterByLanguageListItem> items(jsonLanguages.count() + 1);
    QVector<FilterByLanguageListItem>::iterator itemsIt = items.begin();
    bool foundSystemLanguage = false;

    for (QJsonArray::const_iterator it = jsonLanguages.constBegin(); it != jsonLanguages.constEnd(); it++) {
        QJsonObject jsonItem = (*it).toObject();
        itemsIt->setId(jsonItem["iso_639_1"].toString());
        itemsIt->setName(jsonItem["name"].toString());
        itemsIt->setEnglishName(jsonItem["english_name"].toString());

        if (!foundSystemLanguage && (*itemsIt).getId() == system.getLanguage()) {
            foundSystemLanguage = true;
            FilterByLanguageListItem& lastLanguage = *itemsIt;
            itemsIt++;
            itemsIt->setId(lastLanguage.getId());
            itemsIt->setName(lastLanguage.getName());
            itemsIt->setEnglishName(lastLanguage.getEnglishName());
            itemsIt->setIsPrimary(true);
        }

        itemsIt++;
    }

    std::sort(items.begin(), items.end(), [](const FilterByLanguageListItem &a, const FilterByLanguageListItem &b)
    {
        return ((a.getIsPrimary() || a.getId() == "xx") ? "" : a.getEnglishName()) < ((b.getIsPrimary() || b.getId() == "xx") ? "" : b.getEnglishName());
    });

    qDebug() << "FilterByLanguagesListModel: sorted";

    for (int i = 0; i < items.count(); i++) {
        const FilterByLanguageListItem &language = items.at(i);
        qDebug() << "add language" << language.getId() << " " << language.getEnglishName() << " " << language.getName();
        add(language);
        jsonLanguages.replace(i, language.toJson());
    }

    return QJsonDocument(jsonLanguages);
}

QHash<int, QByteArray> FilterByLanguagesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[EnglishNameRole] = "englishName";
    roles[NameRole] = "name";
    roles[SectionRole] = "section";
    roles[PrimaryRole] = "isPrimary";
    return roles;
}

const QList<FilterByLanguageListItem> &FilterByLanguagesListModel::getItems() const
{
    return items;
}
