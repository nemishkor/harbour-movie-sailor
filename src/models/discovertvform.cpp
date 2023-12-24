#include "discovertvform.h"

DiscoverTvForm::DiscoverTvForm(QObject *parent) :
    QObject(parent),
    firstAirDateYear(0),
    includeAdult(false),
    includeNullFirstAirDates(true),
    page(1),
    screenedTheatrically(false),
    sorting(Sorting::Popularity),
    order(Order::DESC),
    voteAverageGte(0.0),
    voteAverageLte(10.0),
    voteCountGte(0),
    voteCountLte(-1),
    watchRegion(new Country(this)),
    providersList(new ProvidersList(this)),
    withWatchProvidersCombinationMode(ListCombinationMode::AND),
    withoutWatchProvidersCombinationMode(ListCombinationMode::AND),
    withOriginCountry(this),
    withOriginLanguage(this)
{
    connect(providersList, &QAbstractListModel::dataChanged, this, &DiscoverTvForm::providersChanged);
    connect(providersList, &QAbstractListModel::rowsRemoved, this, &DiscoverTvForm::providersChanged);
}

void DiscoverTvForm::populateQuery(QUrlQuery &urlQuery) const
{
    QString dateFormat = "yyyy-MM-dd";

    if (!airDateGte.isNull()) {
        urlQuery.addQueryItem("air_date.gte", airDateGte.toString(dateFormat));
    }

    if (!airDateLte.isNull()) {
        urlQuery.addQueryItem("air_date.lte", airDateLte.toString(dateFormat));
    }

    if (firstAirDateYear > 0) {
        urlQuery.addQueryItem("first_air_date_year", QString::number(firstAirDateYear));
    }

    if (!firstAirDateGte.isNull()) {
        urlQuery.addQueryItem("first_air_date.gte", firstAirDateGte.toString(dateFormat));
    }

    if (!firstAirDateLte.isNull()) {
        urlQuery.addQueryItem("first_air_date.lte", firstAirDateLte.toString(dateFormat));
    }

    urlQuery.addQueryItem("include_adult", includeAdult ? "true" : "false");
    urlQuery.addQueryItem("include_null_first_air_dates", includeNullFirstAirDates ? "true" : "false");
    urlQuery.addQueryItem("page", QString::number(page));
    urlQuery.addQueryItem("screened_theatrically", screenedTheatrically ? "true" : "false");

    QString sortBy = "";
    switch (sorting) {
    case DiscoverTvForm::Popularity:
        sortBy.append("popularity");
        break;
    case DiscoverTvForm::Revenue:
        sortBy.append("revenue");
        break;
    case DiscoverTvForm::PrimaryReleaseDate:
        sortBy.append("primary_release_date");
        break;
    case DiscoverTvForm::VoteAverage:
        sortBy.append("vote_average");
        break;
    case DiscoverTvForm::VoteCount:
        sortBy.append("vote_count");
        break;
    }
    sortBy.append(".");
    switch (order) {
    case DiscoverTvForm::ASC:
        sortBy.append("asc");
        break;
    case DiscoverTvForm::DESC:
        sortBy.append("desc");
        break;
    }
    urlQuery.addQueryItem("sort_by", sortBy);

    if (voteAverageGte > 0.0) {
        urlQuery.addQueryItem("vote_average.gte", QString::number(voteAverageGte));
    }

    if (voteAverageLte < 10.0) {
        urlQuery.addQueryItem("vote_average.lte", QString::number(voteAverageLte));
    }

    if (voteCountGte > 0) {
        urlQuery.addQueryItem("vote_count.gte", QString::number(voteCountGte));
    }

    if (!watchRegion->getId().isEmpty()) {
        urlQuery.addQueryItem("watch_region", watchRegion->getId());
        QStringList withProviders;
        QStringList withoutProviders;
        QList<ProviderListItem>::const_iterator providersIt = providersList->getItems().constBegin();
        for (; providersIt != providersList->getItems().constEnd(); providersIt++) {
            if (providersIt->getState() == 1) {
                withProviders.append(QString::number(providersIt->getId()));
            } else if (providersIt->getState() == 2) {
                withoutProviders.append(QString::number(providersIt->getId()));
            }
        }
        if (!withProviders.isEmpty()) {
            urlQuery.addQueryItem(
                "with_watch_providers",
                withProviders.join(QString::number(static_cast<int>(withWatchProvidersCombinationMode)))
            );
        }
        if (!withoutProviders.isEmpty()) {
            urlQuery.addQueryItem(
                "without_watch_providers",
                withoutProviders.join(QString::number(static_cast<int>(withoutWatchProvidersCombinationMode)))
            );
        }
    }
}

QString DiscoverTvForm::toString() const
{
    QUrlQuery query;
    populateQuery(query);

    return query.toString();
}

const QDateTime &DiscoverTvForm::getAirDateGte() const
{
    return airDateGte;
}

void DiscoverTvForm::setAirDateGte(const QDateTime &newAirDateGte)
{
    if (airDateGte == newAirDateGte)
        return;
    airDateGte = newAirDateGte;
    emit airDateGteChanged();
}

const QDateTime &DiscoverTvForm::getAirDateLte() const
{
    return airDateLte;
}

void DiscoverTvForm::setAirDateLte(const QDateTime &newAirDateLte)
{
    if (airDateLte == newAirDateLte)
        return;
    airDateLte = newAirDateLte;
    emit airDateLteChanged();
}

int DiscoverTvForm::getFirstAirDateYear() const
{
    return firstAirDateYear;
}

void DiscoverTvForm::setFirstAirDateYear(int newFirstAirDateYear)
{
    if (firstAirDateYear == newFirstAirDateYear)
        return;
    firstAirDateYear = newFirstAirDateYear;
    emit firstAirDateYearChanged();
}

const QDateTime &DiscoverTvForm::getFirstAirDateGte() const
{
    return firstAirDateGte;
}

void DiscoverTvForm::setFirstAirDateGte(const QDateTime &newFirstAirDateGte)
{
    if (firstAirDateGte == newFirstAirDateGte)
        return;
    firstAirDateGte = newFirstAirDateGte;
    emit firstAirDateGteChanged();
}

const QDateTime &DiscoverTvForm::getFirstAirDateLte() const
{
    return firstAirDateLte;
}

void DiscoverTvForm::setFirstAirDateLte(const QDateTime &newFirstAirDateLte)
{
    if (firstAirDateLte == newFirstAirDateLte)
        return;
    firstAirDateLte = newFirstAirDateLte;
    emit firstAirDateLteChanged();
}

bool DiscoverTvForm::getIncludeAdult() const
{
    return includeAdult;
}

void DiscoverTvForm::setIncludeAdult(bool newIncludeAdult)
{
    if (includeAdult == newIncludeAdult)
        return;
    includeAdult = newIncludeAdult;
    emit includeAdultChanged();
}

bool DiscoverTvForm::getIncludeNullFirstAirDates() const
{
    return includeNullFirstAirDates;
}

void DiscoverTvForm::setIncludeNullFirstAirDates(bool newIncludeNullFirstAirDates)
{
    if (includeNullFirstAirDates == newIncludeNullFirstAirDates)
        return;
    includeNullFirstAirDates = newIncludeNullFirstAirDates;
    emit includeNullFirstAirDatesChanged();
}

bool DiscoverTvForm::getScreenedTheatrically() const
{
    return screenedTheatrically;
}

void DiscoverTvForm::setScreenedTheatrically(bool newScreenedTheatrically)
{
    if (screenedTheatrically == newScreenedTheatrically)
        return;
    screenedTheatrically = newScreenedTheatrically;
    emit screenedTheatricallyChanged();
}

DiscoverTvForm::Sorting DiscoverTvForm::getSorting() const
{
    return sorting;
}

void DiscoverTvForm::setSorting(Sorting newSorting)
{
    if (sorting == newSorting)
        return;
    sorting = newSorting;
    emit sortingChanged();
}

DiscoverTvForm::Order DiscoverTvForm::getOrder() const
{
    return order;
}

void DiscoverTvForm::setOrder(Order newOrder)
{
    if (order == newOrder)
        return;
    order = newOrder;
    emit orderChanged();
}

double DiscoverTvForm::getVoteAverageGte() const
{
    return voteAverageGte;
}

void DiscoverTvForm::setVoteAverageGte(double newVoteAverageGte)
{
    if (qFuzzyCompare(voteAverageGte, newVoteAverageGte))
        return;
    voteAverageGte = newVoteAverageGte;
    emit voteAverageGteChanged();
}

double DiscoverTvForm::getVoteAverageLte() const
{
    return voteAverageLte;
}

void DiscoverTvForm::setVoteAverageLte(double newVoteAverageLte)
{
    if (qFuzzyCompare(voteAverageLte, newVoteAverageLte))
        return;
    voteAverageLte = newVoteAverageLte;
    emit voteAverageLteChanged();
}

int DiscoverTvForm::getVoteCountGte() const
{
    return voteCountGte;
}

void DiscoverTvForm::setVoteCountGte(int newVoteCountGte)
{
    if (voteCountGte == newVoteCountGte)
        return;
    voteCountGte = newVoteCountGte;
    emit voteCountGteChanged();
}

int DiscoverTvForm::getVoteCountLte() const
{
    return voteCountLte;
}

void DiscoverTvForm::setVoteCountLte(int newVoteCountLte)
{
    if (voteCountLte == newVoteCountLte)
        return;
    voteCountLte = newVoteCountLte;
    emit voteCountLteChanged();
}

Country *DiscoverTvForm::getWatchRegion() const
{
    return watchRegion;
}

const DiscoverTvForm::ListCombinationMode &DiscoverTvForm::getWithWatchProvidersCombinationMode() const
{
    return withWatchProvidersCombinationMode;
}

void DiscoverTvForm::setWithWatchProvidersCombinationMode(const ListCombinationMode &newWithWatchProvidersCombinationMode)
{
    if (withWatchProvidersCombinationMode == newWithWatchProvidersCombinationMode)
        return;
    withWatchProvidersCombinationMode = newWithWatchProvidersCombinationMode;
    emit withWatchProvidersCombinationModeChanged();
}

const DiscoverTvForm::ListCombinationMode &DiscoverTvForm::getWithoutWatchProvidersCombinationMode() const
{
    return withoutWatchProvidersCombinationMode;
}

void DiscoverTvForm::setWithoutWatchProvidersCombinationMode(const ListCombinationMode &newWithoutWatchProvidersCombinationMode)
{
    if (withoutWatchProvidersCombinationMode == newWithoutWatchProvidersCombinationMode)
        return;
    withoutWatchProvidersCombinationMode = newWithoutWatchProvidersCombinationMode;
    emit withoutWatchProvidersCombinationModeChanged();
}

void DiscoverTvForm::providersChanged()
{
    withWatchProviders.clear();
    withoutWatchProviders.clear();
    QList<ProviderListItem>::const_iterator it;
    for (it = providersList->getItems().constBegin(); it != providersList->getItems().constEnd(); it++) {
        if (it->getState() == 1) {
            withWatchProviders.append(it->getName());
        } else if (it->getState() == 2) {
            withoutWatchProviders.append(it->getName());
        }
    }
    emit withWatchProvidersChanged();
    emit withoutWatchProvidersChanged();
}

int DiscoverTvForm::getPage() const
{
    return page;
}

void DiscoverTvForm::setPage(int newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}

const QStringList &DiscoverTvForm::getWithoutWatchProviders() const
{
    return withoutWatchProviders;
}

void DiscoverTvForm::setWithoutWatchProviders(const QStringList &newWithoutWatchProviders)
{
    if (withoutWatchProviders == newWithoutWatchProviders)
        return;
    withoutWatchProviders = newWithoutWatchProviders;
    emit withoutWatchProvidersChanged();
}

const QStringList &DiscoverTvForm::getWithWatchProviders() const
{
    return withWatchProviders;
}

void DiscoverTvForm::setWithWatchProviders(const QStringList &newWithWatchProviders)
{
    if (withWatchProviders == newWithWatchProviders)
        return;
    withWatchProviders = newWithWatchProviders;
    emit withWatchProvidersChanged();
}

ProvidersList *DiscoverTvForm::getProvidersList() const
{
    return providersList;
}
