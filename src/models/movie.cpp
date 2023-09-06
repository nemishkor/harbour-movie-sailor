#include "movie.h"

Movie::Movie(QObject *parent) :
    QObject(parent),
    belongsToCollection(new MovieCollection(this)),
    productionCompanies(new CompaniesListModel(this)),
    productionCountries(new CountriesListModel(this)),
    spokenLanguages(new LanguagesListModel(this)),
    favorite(false),
    watchlist(false),
    credits(new Credits(this))
{

}

int Movie::getId() const
{
    return id;
}

void Movie::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Movie::getBackdropPath() const
{
    return backdropPath;
}

void Movie::setBackdropPath(const QString &newBackdropPath)
{
    if (backdropPath == newBackdropPath)
        return;
    backdropPath = newBackdropPath;
    emit backdropPathChanged();
}

const QStringList &Movie::getGenres() const
{
    return genres;
}

void Movie::setGenres(const QStringList &newGenres)
{
    if (genres == newGenres)
        return;
    genres = newGenres;
    emit genresChanged();
}

const QString &Movie::getHomepage() const
{
    return homepage;
}

void Movie::setHomepage(const QString &newHomepage)
{
    if (homepage == newHomepage)
        return;
    homepage = newHomepage;
    emit homepageChanged();
}

const QString &Movie::getImdbId() const
{
    return imdbId;
}

void Movie::setImdbId(const QString &newImdbId)
{
    if (imdbId == newImdbId)
        return;
    imdbId = newImdbId;
    emit imdbIdChanged();
}

const QString &Movie::getOriginalLanguage() const
{
    return originalLanguage;
}

void Movie::setOriginalLanguage(const QString &newOriginalLanguage)
{
    if (originalLanguage == newOriginalLanguage)
        return;
    originalLanguage = newOriginalLanguage;
    emit originalLanguageChanged();
}

const QString &Movie::getOriginalTitle() const
{
    return originalTitle;
}

void Movie::setOriginalTitle(const QString &newOriginalTitle)
{
    if (originalTitle == newOriginalTitle)
        return;
    originalTitle = newOriginalTitle;
    emit originalTitleChanged();
}

const QString &Movie::getOverview() const
{
    return overview;
}

void Movie::setOverview(const QString &newOverview)
{
    if (overview == newOverview)
        return;
    overview = newOverview;
    emit overviewChanged();
}

const QString &Movie::getPosterPath() const
{
    return posterPath;
}

void Movie::setPosterPath(const QString &newPosterPath)
{
    if (posterPath == newPosterPath)
        return;
    posterPath = newPosterPath;
    emit posterPathChanged();
}

const QString &Movie::getReleaseDate() const
{
    return releaseDate;
}

void Movie::setReleaseDate(const QString &newReleaseDate)
{
    if (releaseDate == newReleaseDate)
        return;
    releaseDate = newReleaseDate;
    emit releaseDateChanged();
}

const QString &Movie::getRevenue() const
{
    return revenue;
}

void Movie::setRevenue(const QString &newRevenue)
{
    if (revenue == newRevenue)
        return;
    revenue = newRevenue;
    emit revenueChanged();
}

int Movie::getRuntimeHours() const
{
    return runtimeHours;
}

void Movie::setRuntimeHours(int newRuntimeHours)
{
    if (runtimeHours == newRuntimeHours)
        return;
    runtimeHours = newRuntimeHours;
    emit runtimeHoursChanged();
}

int Movie::getRuntimeMinutes() const
{
    return runtimeMinutes;
}

void Movie::setRuntimeMinutes(int newRuntimeMinutes)
{
    if (runtimeMinutes == newRuntimeMinutes)
        return;
    runtimeMinutes = newRuntimeMinutes;
    emit runtimeMinutesChanged();
}

const QString &Movie::getStatus() const
{
    return status;
}

void Movie::setStatus(const QString &newStatus)
{
    if (status == newStatus)
        return;
    status = newStatus;
    emit statusChanged();
}

const QString &Movie::getTagline() const
{
    return tagline;
}

void Movie::setTagline(const QString &newTagline)
{
    if (tagline == newTagline)
        return;
    tagline = newTagline;
    emit taglineChanged();
}

const QString &Movie::getTitle() const
{
    return title;
}

void Movie::setTitle(const QString &newTitle)
{
    if (title == newTitle)
        return;
    title = newTitle;
    emit titleChanged();
}

double Movie::getVoteAvarage() const
{
    return voteAvarage;
}

void Movie::setVoteAvarage(double newVoteAvarage)
{
    if (qFuzzyCompare(voteAvarage, newVoteAvarage))
        return;
    voteAvarage = newVoteAvarage;
    emit voteAvarageChanged();
}

uint Movie::getVoteCount() const
{
    return voteCount;
}

void Movie::setVoteCount(uint newVoteCount)
{
    if (voteCount == newVoteCount)
        return;
    voteCount = newVoteCount;
    emit voteCountChanged();
}

const QString &Movie::getBudget() const
{
    return budget;
}

void Movie::setBudget(const QString &newBudget)
{
    if (budget == newBudget)
        return;
    budget = newBudget;
    emit budgetChanged();
}

MovieCollection *Movie::getBelongsToCollection() const
{
    return belongsToCollection;
}

CompaniesListModel *Movie::getProductionCompanies() const
{
    return productionCompanies;
}

CountriesListModel *Movie::getProductionCountries() const
{
    return productionCountries;
}

LanguagesListModel *Movie::getSpokenLanguages() const
{
    return spokenLanguages;
}

bool Movie::getFavorite() const
{
    return favorite;
}

void Movie::setFavorite(bool newFavorite)
{
    if (favorite == newFavorite)
        return;
    favorite = newFavorite;
    emit favoriteChanged();
}

bool Movie::getWatchlist() const
{
    return watchlist;
}

void Movie::setWatchlist(bool newWatchlist)
{
    if (watchlist == newWatchlist)
        return;
    watchlist = newWatchlist;
    emit watchlistChanged();
}

int Movie::getRating() const
{
    return rating;
}

void Movie::setRating(int newRating)
{
    if (rating == newRating)
        return;
    rating = newRating;
    emit ratingChanged();
}

Credits *Movie::getCredits() const
{
    return credits;
}
