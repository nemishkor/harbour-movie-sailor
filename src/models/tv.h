#ifndef TV_H
#define TV_H

#include <QDebug>
#include <QObject>
#include <QList>
#include <QString>

#include "src/listmodels/videoslist.h"
#include "src/models/credits.h"
#include "src/models/personlistitem.h"
#include "src/models/episode.h"
#include "src/models/networklistitem.h"
#include "src/models/seasonlistitem.h"
#include "src/viewmodels/companieslistmodel.h"
#include "src/viewmodels/countrieslistmodel.h"
#include "src/viewmodels/languageslistmodel.h"
#include "src/viewmodels/personlistmodel.h"
#include "src/viewmodels/networkslistmodel.h"
#include "src/viewmodels/seasonslistmodel.h"
#include "src/viewmodels/medialistmodel.h"

class Tv : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool adult READ getAdult WRITE setAdult NOTIFY adultChanged)
    Q_PROPERTY(QString backdropPath READ getBackdropPath WRITE setBackdropPath NOTIFY backdropPathChanged)
    Q_PROPERTY(PersonListModel* createdBy READ getCreatedBy CONSTANT)
    Q_PROPERTY(int episodeRunTimeHours READ getEpisodeRunTimeHours WRITE setEpisodeRunTimeHours NOTIFY episodeRunTimeHoursChanged)
    Q_PROPERTY(int episodeRunTimeMinutes READ getEpisodeRunTimeMinutes WRITE setEpisodeRunTimeMinutes NOTIFY episodeRunTimeMinutesChanged)
    Q_PROPERTY(QString firstAirDate READ getFirstAirDate WRITE setFirstAirDate NOTIFY firstAirDateChanged)
    Q_PROPERTY(QStringList genres READ getGenres WRITE setGenres NOTIFY genresChanged)
    Q_PROPERTY(QString homepage READ getHomepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool inProduction READ getInProduction WRITE setInProduction NOTIFY inProductionChanged)
    Q_PROPERTY(QList<QString> languages READ getLanguages WRITE setLanguages NOTIFY languagesChanged)
    Q_PROPERTY(QString lastAirDate READ getLastAirDate WRITE setLastAirDate NOTIFY lastAirDateChanged)
    Q_PROPERTY(Episode* lastEpisodeOnAir READ getLastEpisodeOnAir CONSTANT)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Episode* nextEpisodeOnAir READ getNextEpisodeOnAir CONSTANT)
    Q_PROPERTY(NetworksListModel* networks READ getNetworks CONSTANT)
    Q_PROPERTY(int numberOfEpisodes READ getNumberOfEpisodes WRITE setNumberOfEpisodes NOTIFY numberOfEpisodesChanged)
    Q_PROPERTY(int numberOfSeasons READ getNumberOfSeasons WRITE setNumberOfSeasons NOTIFY numberOfSeasonsChanged)
    Q_PROPERTY(QList<QString> originCountry READ getOriginCountry WRITE setOriginCountry NOTIFY originCountryChanged)
    Q_PROPERTY(QString originLanguage READ getOriginLanguage WRITE setOriginLanguage NOTIFY originLanguageChanged)
    Q_PROPERTY(QString originName READ getOriginName WRITE setOriginName NOTIFY originNameChanged)
    Q_PROPERTY(QString overview READ getOverview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(double popularity READ getPopularity WRITE setPopularity NOTIFY popularityChanged)
    Q_PROPERTY(QString posterPath READ getPosterPath WRITE setPosterPath NOTIFY posterPathChanged)
    Q_PROPERTY(CompaniesListModel* productionCompanies READ getProductionCompanies CONSTANT)
    Q_PROPERTY(CountriesListModel* productionCountries READ getProductionCountries CONSTANT)
    Q_PROPERTY(SeasonsListModel* seasons READ getSeasons CONSTANT)
    Q_PROPERTY(LanguagesListModel* spokenLanguages READ getSpokenLanguages CONSTANT)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString tagline READ getTagline WRITE setTagline NOTIFY taglineChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(float voteAvarage READ getVoteAvarage WRITE setVoteAvarage NOTIFY voteAvarageChanged)
    Q_PROPERTY(int voteCount READ getVoteCount WRITE setVoteCount NOTIFY voteCountChanged)
    Q_PROPERTY(bool favorite READ getFavorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(bool watchlist READ getWatchlist WRITE setWatchlist NOTIFY watchlistChanged)
    Q_PROPERTY(int rating READ getRating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(Credits* credits READ getCredits CONSTANT)
    Q_PROPERTY(VideosList* videos READ getVideos CONSTANT)
    Q_PROPERTY(MediaListModel* recommendations READ getRecommendations CONSTANT)
    Q_PROPERTY(MediaListModel* similar READ getSimilar CONSTANT)

public:
    Tv(QObject *parent = nullptr);

    bool getAdult() const;
    void setAdult(bool newAdult);

    const QString &getBackdropPath() const;
    void setBackdropPath(const QString &newBackdropPath);

    PersonListModel *getCreatedBy() const;

    int getEpisodeRunTimeHours() const;
    void setEpisodeRunTimeHours(int newEpisodeRunTimeHours);

    int getEpisodeRunTimeMinutes() const;
    void setEpisodeRunTimeMinutes(int newEpisodeRunTimeMinutes);

    const QString &getFirstAirDate() const;
    void setFirstAirDate(const QString &newFirstAirDate);

    const QStringList &getGenres() const;
    void setGenres(const QStringList &newGenres);

    const QString &getHomepage() const;
    void setHomepage(const QString &newHomepage);

    int getId() const;
    void setId(int newId);

    bool getInProduction() const;
    void setInProduction(bool newInProduction);

    const QList<QString> &getLanguages() const;
    void setLanguages(const QList<QString> &newLanguages);

    const QString &getLastAirDate() const;
    void setLastAirDate(const QString &newLastAirDate);

    Episode *getLastEpisodeOnAir() const;

    const QString &getName() const;
    void setName(const QString &newName);

    Episode *getNextEpisodeOnAir() const;

    NetworksListModel *getNetworks() const;

    int getNumberOfEpisodes() const;
    void setNumberOfEpisodes(int newNumberOfEpisodes);

    int getNumberOfSeasons() const;
    void setNumberOfSeasons(int newNumberOfSeasons);

    const QList<QString> &getOriginCountry() const;
    void setOriginCountry(const QList<QString> &newOriginCountry);

    const QString &getOriginLanguage() const;
    void setOriginLanguage(const QString &newOriginLanguage);

    const QString &getOriginName() const;
    void setOriginName(const QString &newOriginName);

    const QString &getOverview() const;
    void setOverview(const QString &newOverview);

    double getPopularity() const;
    void setPopularity(double newPopularity);

    const QString &getPosterPath() const;
    void setPosterPath(const QString &newPosterPath);

    CompaniesListModel *getProductionCompanies() const;

    CountriesListModel *getProductionCountries() const;

    SeasonsListModel *getSeasons() const;

    LanguagesListModel *getSpokenLanguages() const;

    const QString &getStatus() const;
    void setStatus(const QString &newStatus);

    const QString &getTagline() const;
    void setTagline(const QString &newTagline);

    const QString &getType() const;
    void setType(const QString &newType);

    float getVoteAvarage() const;
    void setVoteAvarage(float newVoteAvarage);

    int getVoteCount() const;
    void setVoteCount(int newVoteCount);

    bool getFavorite() const;
    void setFavorite(bool newFavorite);

    bool getWatchlist() const;
    void setWatchlist(bool newWatchlist);

    int getRating() const;
    void setRating(int newRating);

    Credits *getCredits() const;

    VideosList *getVideos() const;

    MediaListModel *getRecommendations() const;

    MediaListModel *getSimilar() const;

signals:
    void adultChanged();
    void backdropPathChanged();
    void episodeRunTimeHoursChanged();
    void episodeRunTimeMinutesChanged();
    void firstAirDateChanged();
    void genresChanged();
    void homepageChanged();
    void idChanged();
    void inProductionChanged();
    void languagesChanged();
    void lastAirDateChanged();
    void nameChanged();
    void numberOfEpisodesChanged();
    void numberOfSeasonsChanged();
    void originCountryChanged();
    void originLanguageChanged();
    void originNameChanged();
    void overviewChanged();
    void popularityChanged();
    void posterPathChanged();
    void statusChanged();
    void taglineChanged();
    void typeChanged();
    void voteAvarageChanged();
    void voteCountChanged();
    void favoriteChanged();
    void watchlistChanged();
    void ratingChanged();

private:
    bool adult;
    QString backdropPath;
    PersonListModel *createdBy;
    int episodeRunTimeHours;
    int episodeRunTimeMinutes;
    QString firstAirDate;
    QStringList genres;
    QString homepage;
    int id;
    bool inProduction;
    QList<QString> languages;
    QString lastAirDate;
    Episode *lastEpisodeOnAir;
    QString name;
    Episode *nextEpisodeOnAir;
    NetworksListModel *networks;
    int numberOfEpisodes;
    int numberOfSeasons;
    QList<QString> originCountry;
    QString originLanguage;
    QString originName;
    QString overview;
    double popularity;
    QString posterPath;
    CompaniesListModel *productionCompanies;
    CountriesListModel *productionCountries;
    SeasonsListModel *seasons;
    LanguagesListModel *spokenLanguages;
    QString status;
    QString tagline;
    QString type;
    float voteAvarage;
    int voteCount;
    bool favorite;
    bool watchlist;
    int rating;
    Credits *credits;
    VideosList *videos;
    MediaListModel *recommendations;
    MediaListModel *similar;

};

#endif // TV_H
