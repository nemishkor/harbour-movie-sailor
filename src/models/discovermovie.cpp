#include "discovermovie.h"

DiscoverMovie::DiscoverMovie(GenresListModel *genres, QObject *parent) :
    QObject(parent),
    page(1),
    voteCountGte(0),
    region(new Country(this)),
    sortBy("popularity"),
    order("desc"),
    voteAverageGte(0.0),
    voteAverageLte(10.0),
    includeVideo(true),
    includeAdult(false),
    originCountry(new Country(this)),
    originLanguage(new Language(this)),
    genres(genres),
    providers(new MovieProvidersListModel(this)),
    anyRoleList(new SearchPeopleListModel(this)),
    castRoleList(new SearchPeopleListModel(this)),
    crewRoleList(new SearchPeopleListModel(this)),
    companies(new FilterByCompaniesListModel(this)),
    keywords(new KeywordsListModel(this))
{
}

void DiscoverMovie::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("page", QString::number(page));
    urlQuery.addQueryItem("sort_by", sortBy + "." + order);

    QString ids = genres->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_genres", ids);
    }

    ids = anyRoleList->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_people", ids);
    }

    ids = castRoleList->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_cast", ids);
    }

    ids = crewRoleList->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_crew", ids);
    }

    ids = companies->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_companies", ids);
    }

    ids = keywords->toQueryString();

    if (!ids.isEmpty()) {
        urlQuery.addQueryItem("with_keywords", ids);
    }

    if (!watchRegion.isEmpty()) {
        ids = providers->toQueryString();
        if (!ids.isEmpty()) {
            urlQuery.addQueryItem("with_watch_providers", ids);
            urlQuery.addQueryItem("watch_region", watchRegion);
        }
    }

    if (region->getId().isEmpty()) {
        if (primaryReleaseYear.isEmpty()) {
            if (!primaryReleaseDateGte.isEmpty()) {
                urlQuery.addQueryItem("primary_release_date.gte", primaryReleaseDateGte);
            }
            if (!primaryReleaseDateLte.isEmpty()) {
                urlQuery.addQueryItem("primary_release_date.lte", primaryReleaseDateLte);
            }
        } else {
            urlQuery.addQueryItem("primary_release_year", primaryReleaseYear);
        }
    } else {
        if (!primaryReleaseDateGte.isEmpty()) {
            urlQuery.addQueryItem("release_date.gte", primaryReleaseDateGte);
        }
        if (!primaryReleaseDateLte.isEmpty()) {
            urlQuery.addQueryItem("release_date.lte", primaryReleaseDateLte);
        }
    }

    if (voteAverageGte > 0.0) {
        urlQuery.addQueryItem("vote_average.gte", QString::number(voteAverageGte));
    }

    if (voteAverageLte < 10.0) {
        urlQuery.addQueryItem("vote_average.lte", QString::number(voteAverageLte));
    }

    if (voteCountGte > 0) {
        urlQuery.addQueryItem("vote_count.gte", QString::number(voteCountGte));
    }

    if (!originCountry->getId().isEmpty()) {
        urlQuery.addQueryItem("with_origin_country", originCountry->getId());
    }

    if (!originLanguage->getId().isEmpty()) {
        urlQuery.addQueryItem("with_original_language", originLanguage->getId());
    }

    urlQuery.addQueryItem("include_video", includeVideo ? "true" : "false");
    urlQuery.addQueryItem("include_adult", includeAdult ? "true" : "false");
}

QString DiscoverMovie::toString() const
{
    return QString();
}

Country *DiscoverMovie::getOriginCountry() const
{
    return originCountry;
}

Language *DiscoverMovie::getOriginLanguage() const
{
    return originLanguage;
}

const QString &DiscoverMovie::getSortBy() const
{
    return sortBy;
}

void DiscoverMovie::setSortBy(const QString &newSortBy)
{
    if (sortBy == newSortBy)
        return;
    sortBy = newSortBy;
    emit sortByChanged();
}

const QString &DiscoverMovie::getOrder() const
{
    return order;
}

void DiscoverMovie::setOrder(const QString &newOrder)
{
    if (order == newOrder)
        return;
    order = newOrder;
    emit orderChanged();
}

const QString &DiscoverMovie::getWatchRegion() const
{
    return watchRegion;
}

void DiscoverMovie::setWatchRegion(const QString &newWatchRegion)
{
    if (watchRegion == newWatchRegion)
        return;
    watchRegion = newWatchRegion;
    emit watchRegionChanged();
}

const QString &DiscoverMovie::getPrimaryReleaseYear() const
{
    return primaryReleaseYear;
}

void DiscoverMovie::setPrimaryReleaseYear(const QString &newPrimaryReleaseYear)
{
    if (primaryReleaseYear == newPrimaryReleaseYear)
        return;
    primaryReleaseYear = newPrimaryReleaseYear;
    emit primaryReleaseYearChanged();
}

const QString &DiscoverMovie::getPrimaryReleaseDateGte() const
{
    return primaryReleaseDateGte;
}

void DiscoverMovie::setPrimaryReleaseDateGte(const QString &newPrimaryReleaseDateGte)
{
    if (primaryReleaseDateGte == newPrimaryReleaseDateGte)
        return;
    primaryReleaseDateGte = newPrimaryReleaseDateGte;
    emit primaryReleaseDateGteChanged();
}

const QString &DiscoverMovie::getPrimaryReleaseDateLte() const
{
    return primaryReleaseDateLte;
}

void DiscoverMovie::setPrimaryReleaseDateLte(const QString &newPrimaryReleaseDateLte)
{
    if (primaryReleaseDateLte == newPrimaryReleaseDateLte)
        return;
    primaryReleaseDateLte = newPrimaryReleaseDateLte;
    emit primaryReleaseDateLteChanged();
}

double DiscoverMovie::getVoteAverageGte() const
{
    return voteAverageGte;
}

void DiscoverMovie::setVoteAverageGte(double newVoteAverageGte)
{
    if (qFuzzyCompare(voteAverageGte, newVoteAverageGte))
        return;
    voteAverageGte = newVoteAverageGte;
    emit voteAverageGteChanged();
}

double DiscoverMovie::getVoteAverageLte() const
{
    return voteAverageLte;
}

void DiscoverMovie::setVoteAverageLte(double newVoteAverageLte)
{
    if (qFuzzyCompare(voteAverageLte, newVoteAverageLte))
        return;
    voteAverageLte = newVoteAverageLte;
    emit voteAverageLteChanged();
}

uint DiscoverMovie::getVoteCountGte() const
{
    return voteCountGte;
}

void DiscoverMovie::setVoteCountGte(uint newVoteCountGte)
{
    if (voteCountGte == newVoteCountGte)
        return;
    voteCountGte = newVoteCountGte;
    emit voteCountGteChanged();
}

bool DiscoverMovie::getIncludeVideo() const
{
    return includeVideo;
}

void DiscoverMovie::setIncludeVideo(bool newIncludeVideo)
{
    if (includeVideo == newIncludeVideo)
        return;
    includeVideo = newIncludeVideo;
    emit includeVideoChanged();
}

bool DiscoverMovie::getIncludeAdult() const
{
    return includeAdult;
}

void DiscoverMovie::setIncludeAdult(bool newIncludeAdult)
{
    if (includeAdult == newIncludeAdult)
        return;
    includeAdult = newIncludeAdult;
    emit includeAdultChanged();
}

SearchPeopleListModel *DiscoverMovie::getAnyRoleList() const
{
    return anyRoleList;
}

SearchPeopleListModel *DiscoverMovie::getCastRoleList() const
{
    return castRoleList;
}

SearchPeopleListModel *DiscoverMovie::getCrewRoleList() const
{
    return crewRoleList;
}

FilterByCompaniesListModel *DiscoverMovie::getCompanies() const
{
    return companies;
}

KeywordsListModel *DiscoverMovie::getKeywords() const
{
    return keywords;
}

Country *DiscoverMovie::getRegion() const
{
    return region;
}

GenresListModel *DiscoverMovie::getGenres() const
{
    return genres;
}

MovieProvidersListModel *DiscoverMovie::getProviders() const
{
    return providers;
}

uint DiscoverMovie::getPage() const
{
    return page;
}

void DiscoverMovie::setPage(uint newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}
