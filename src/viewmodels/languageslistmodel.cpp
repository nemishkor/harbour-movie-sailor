#include "languageslistmodel.h"

LanguagesListModel::LanguagesListModel(System &system, QObject *parent) :
    QAbstractListModel(parent),
    system(system)
{

}

int LanguagesListModel::rowCount(const QModelIndex &) const{
    return items.size();
}

QVariant LanguagesListModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const LanguageListItem &language = items[index.row()];
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

void LanguagesListModel::add(const LanguageListItem &language)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(language);
    endInsertRows();
    emit countChanged();
}

void LanguagesListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray languages = json.array();
    for(QJsonArray::const_iterator it = languages.constBegin(); it != languages.constEnd(); it++){
        add(LanguageListItem((*it).toObject()));
    }
}

const QJsonDocument LanguagesListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonLanguages = json.array();
    QVector<LanguageListItem> items(jsonLanguages.count() + 1);
    QVector<LanguageListItem>::iterator itemsIt = items.begin();
    bool foundSystemLanguage = false;

    for (QJsonArray::const_iterator it = jsonLanguages.constBegin(); it != jsonLanguages.constEnd(); it++) {
        QJsonObject jsonItem = (*it).toObject();
        itemsIt->setId(jsonItem["iso_639_1"].toString());
        itemsIt->setName(jsonItem["name"].toString());
        itemsIt->setEnglishName(jsonItem["english_name"].toString());

        if (!foundSystemLanguage && (*itemsIt).getId() == system.getLanguage()) {
            foundSystemLanguage = true;
            LanguageListItem& lastLanguage = *itemsIt;
            itemsIt++;
            itemsIt->setId(lastLanguage.getId());
            itemsIt->setName(lastLanguage.getName());
            itemsIt->setEnglishName(lastLanguage.getEnglishName());
            itemsIt->setIsPrimary(true);
        }

        itemsIt++;
    }

    std::sort(items.begin(), items.end(), [](const LanguageListItem &a, const LanguageListItem &b)
    {
        return ((a.getIsPrimary() || a.getId() == "xx") ? "" : a.getEnglishName()) < ((b.getIsPrimary() || b.getId() == "xx") ? "" : b.getEnglishName());
    });

    for (int i = 0; i < items.count(); i++) {
        const LanguageListItem &language = items.at(i);
        qDebug() << "add language" << language.getId() << " " << language.getEnglishName() << " " << language.getName();
        add(language);
        jsonLanguages.replace(i, language.toJson());
    }

    return QJsonDocument(jsonLanguages);
}

QHash<int, QByteArray> LanguagesListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[EnglishNameRole] = "englishName";
    roles[NameRole] = "name";
    roles[SectionRole] = "section";
    roles[PrimaryRole] = "isPrimary";
    return roles;
}
