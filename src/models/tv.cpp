#include "tv.h"

Tv::Tv(QObject *parent) :
    QObject(parent),
    createdBy(new PersonListModel(this)),
    episodeRunTimeHours(0),
    episodeRunTimeMinutes(0),
    id(0),
    lastEpisodeOnAir(new Episode(this)),
    nextEpisodeOnAir(new Episode(this)),
    networks(new NetworksListModel(this)),
    numberOfEpisodes(0),
    numberOfSeasons(0),
    productionCompanies(new CompaniesListModel(this)),
    productionCountries(new CountriesListModel(this)),
    seasons(new SeasonsListModel(this)),
    spokenLanguages(new LanguagesListModel(this)),
    voteAvarage(0.0),
    voteCount(0),
    rating(0),
    credits(new Credits(this))
{

}

bool Tv::getAdult() const
{
    return adult;
}

void Tv::setAdult(bool newAdult)
{
    if (adult == newAdult)
        return;
    adult = newAdult;
    emit adultChanged();
}

const QString &Tv::getBackdropPath() const
{
    return backdropPath;
}

void Tv::setBackdropPath(const QString &newBackdropPath)
{
    if (backdropPath == newBackdropPath)
        return;
    backdropPath = newBackdropPath;
    emit backdropPathChanged();
}

PersonListModel *Tv::getCreatedBy() const
{
    return createdBy;
}

int Tv::getEpisodeRunTimeHours() const
{
    return episodeRunTimeHours;
}

void Tv::setEpisodeRunTimeHours(int newEpisodeRunTimeHours)
{
    if (episodeRunTimeHours == newEpisodeRunTimeHours)
        return;
    episodeRunTimeHours = newEpisodeRunTimeHours;
    emit episodeRunTimeHoursChanged();
}

int Tv::getEpisodeRunTimeMinutes() const
{
    return episodeRunTimeMinutes;
}

void Tv::setEpisodeRunTimeMinutes(int newEpisodeRunTimeMinutes)
{
    if (episodeRunTimeMinutes == newEpisodeRunTimeMinutes)
        return;
    episodeRunTimeMinutes = newEpisodeRunTimeMinutes;
    emit episodeRunTimeMinutesChanged();
}

const QString &Tv::getFirstAirDate() const
{
    return firstAirDate;
}

void Tv::setFirstAirDate(const QString &newFirstAirDate)
{
    if (firstAirDate == newFirstAirDate)
        return;
    firstAirDate = newFirstAirDate;
    emit firstAirDateChanged();
}

const QStringList &Tv::getGenres() const
{
    return genres;
}

void Tv::setGenres(const QStringList &newGenres)
{
    if (genres == newGenres)
        return;
    genres = newGenres;
    emit genresChanged();
}

const QString &Tv::getHomepage() const
{
    return homepage;
}

void Tv::setHomepage(const QString &newHomepage)
{
    if (homepage == newHomepage)
        return;
    homepage = newHomepage;
    emit homepageChanged();
}

int Tv::getId() const
{
    return id;
}

void Tv::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

bool Tv::getInProduction() const
{
    return inProduction;
}

void Tv::setInProduction(bool newInProduction)
{
    if (inProduction == newInProduction)
        return;
    inProduction = newInProduction;
    emit inProductionChanged();
}

const QList<QString> &Tv::getLanguages() const
{
    return languages;
}

void Tv::setLanguages(const QList<QString> &newLanguages)
{
    if (languages == newLanguages)
        return;
    languages = newLanguages;
    emit languagesChanged();
}

const QString &Tv::getLastAirDate() const
{
    return lastAirDate;
}

void Tv::setLastAirDate(const QString &newLastAirDate)
{
    if (lastAirDate == newLastAirDate)
        return;
    lastAirDate = newLastAirDate;
    emit lastAirDateChanged();
}

Episode *Tv::getLastEpisodeOnAir() const
{
    return lastEpisodeOnAir;
}

const QString &Tv::getName() const
{
    return name;
}

void Tv::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

Episode *Tv::getNextEpisodeOnAir() const
{
    return nextEpisodeOnAir;
}

NetworksListModel *Tv::getNetworks() const
{
    return networks;
}

int Tv::getNumberOfEpisodes() const
{
    return numberOfEpisodes;
}

void Tv::setNumberOfEpisodes(int newNumberOfEpisodes)
{
    if (numberOfEpisodes == newNumberOfEpisodes)
        return;
    numberOfEpisodes = newNumberOfEpisodes;
    emit numberOfEpisodesChanged();
}

int Tv::getNumberOfSeasons() const
{
    return numberOfSeasons;
}

void Tv::setNumberOfSeasons(int newNumberOfSeasons)
{
    if (numberOfSeasons == newNumberOfSeasons)
        return;
    numberOfSeasons = newNumberOfSeasons;
    emit numberOfSeasonsChanged();
}

const QList<QString> &Tv::getOriginCountry() const
{
    return originCountry;
}

void Tv::setOriginCountry(const QList<QString> &newOriginCountry)
{
    if (originCountry == newOriginCountry)
        return;
    originCountry = newOriginCountry;
    emit originCountryChanged();
}

const QString &Tv::getOriginLanguage() const
{
    return originLanguage;
}

void Tv::setOriginLanguage(const QString &newOriginLanguage)
{
    if (originLanguage == newOriginLanguage)
        return;
    originLanguage = newOriginLanguage;
    emit originLanguageChanged();
}

const QString &Tv::getOriginName() const
{
    return originName;
}

void Tv::setOriginName(const QString &newOriginName)
{
    if (originName == newOriginName)
        return;
    originName = newOriginName;
    emit originNameChanged();
}

const QString &Tv::getOverview() const
{
    return overview;
}

void Tv::setOverview(const QString &newOverview)
{
    if (overview == newOverview)
        return;
    overview = newOverview;
    emit overviewChanged();
}

double Tv::getPopularity() const
{
    return popularity;
}

void Tv::setPopularity(double newPopularity)
{
    if (qFuzzyCompare(popularity, newPopularity))
        return;
    popularity = newPopularity;
    emit popularityChanged();
}

const QString &Tv::getPosterPath() const
{
    return posterPath;
}

void Tv::setPosterPath(const QString &newPosterPath)
{
    if (posterPath == newPosterPath)
        return;
    posterPath = newPosterPath;
    emit posterPathChanged();
}

CompaniesListModel *Tv::getProductionCompanies() const
{
    return productionCompanies;
}

CountriesListModel *Tv::getProductionCountries() const
{
    return productionCountries;
}

SeasonsListModel *Tv::getSeasons() const
{
    return seasons;
}

LanguagesListModel *Tv::getSpokenLanguages() const
{
    return spokenLanguages;
}

const QString &Tv::getStatus() const
{
    return status;
}

void Tv::setStatus(const QString &newStatus)
{
    if (status == newStatus)
        return;
    status = newStatus;
    emit statusChanged();
}

const QString &Tv::getTagline() const
{
    return tagline;
}

void Tv::setTagline(const QString &newTagline)
{
    if (tagline == newTagline)
        return;
    qDebug() << "new TV tagline" << newTagline;
    tagline = newTagline;
    emit taglineChanged();
}

const QString &Tv::getType() const
{
    return type;
}

void Tv::setType(const QString &newType)
{
    if (type == newType)
        return;
    type = newType;
    emit typeChanged();
}

float Tv::getVoteAvarage() const
{
    return voteAvarage;
}

void Tv::setVoteAvarage(float newVoteAvarage)
{
    voteAvarage = newVoteAvarage;
    emit voteAvarageChanged();
}

int Tv::getVoteCount() const
{
    return voteCount;
}

void Tv::setVoteCount(int newVoteCount)
{
    if (voteCount == newVoteCount)
        return;
    voteCount = newVoteCount;
    emit voteCountChanged();
}

bool Tv::getFavorite() const
{
    return favorite;
}

void Tv::setFavorite(bool newFavorite)
{
    if (favorite == newFavorite)
        return;
    favorite = newFavorite;
    emit favoriteChanged();
}

bool Tv::getWatchlist() const
{
    return watchlist;
}

void Tv::setWatchlist(bool newWatchlist)
{
    if (watchlist == newWatchlist)
        return;
    watchlist = newWatchlist;
    emit watchlistChanged();
}

int Tv::getRating() const
{
    return rating;
}

void Tv::setRating(int newRating)
{
    if (rating == newRating)
        return;
    rating = newRating;
    emit ratingChanged();
}

Credits *Tv::getCredits() const
{
    return credits;
}
