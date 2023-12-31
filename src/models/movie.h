#ifndef MOVIE_H
#define MOVIE_H

#include <QDebug>
#include <QObject>
#include <QString>

#include "src/listmodels/videoslist.h"
#include "src/models/credits.h"
#include "src/models/moviecollection.h"
#include "src/viewmodels/companieslistmodel.h"
#include "src/viewmodels/countrieslistmodel.h"
#include "src/viewmodels/languageslistmodel.h"

class Movie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString backdropPath READ getBackdropPath WRITE setBackdropPath NOTIFY backdropPathChanged)
    Q_PROPERTY(QString budget READ getBudget WRITE setBudget NOTIFY budgetChanged)
    Q_PROPERTY(QStringList genres READ getGenres WRITE setGenres NOTIFY genresChanged)
    Q_PROPERTY(QString homepage READ getHomepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(QString imdbId READ getImdbId WRITE setImdbId NOTIFY imdbIdChanged)
    Q_PROPERTY(QString originalLanguage READ getOriginalLanguage WRITE setOriginalLanguage NOTIFY originalLanguageChanged)
    Q_PROPERTY(QString originalTitle READ getOriginalTitle WRITE setOriginalTitle NOTIFY originalTitleChanged)
    Q_PROPERTY(QString overview READ getOverview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(QString posterPath READ getPosterPath WRITE setPosterPath NOTIFY posterPathChanged)
    Q_PROPERTY(QString releaseDate READ getReleaseDate WRITE setReleaseDate NOTIFY releaseDateChanged)
    Q_PROPERTY(QString revenue READ getRevenue WRITE setRevenue NOTIFY revenueChanged)
    Q_PROPERTY(int runtimeHours READ getRuntimeHours WRITE setRuntimeHours NOTIFY runtimeHoursChanged)
    Q_PROPERTY(int runtimeMinutes READ getRuntimeMinutes WRITE setRuntimeMinutes NOTIFY runtimeMinutesChanged)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString tagline READ getTagline WRITE setTagline NOTIFY taglineChanged)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(double voteAvarage READ getVoteAvarage WRITE setVoteAvarage NOTIFY voteAvarageChanged)
    Q_PROPERTY(uint voteCount READ getVoteCount WRITE setVoteCount NOTIFY voteCountChanged)
    Q_PROPERTY(MovieCollection* belongsToCollection READ getBelongsToCollection CONSTANT)
    Q_PROPERTY(CompaniesListModel* productionCompanies READ getProductionCompanies CONSTANT)
    Q_PROPERTY(CountriesListModel* productionCountries READ getProductionCountries CONSTANT)
    Q_PROPERTY(LanguagesListModel* spokenLanguages READ getSpokenLanguages CONSTANT)
    Q_PROPERTY(bool favorite READ getFavorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(bool watchlist READ getWatchlist WRITE setWatchlist NOTIFY watchlistChanged)
    Q_PROPERTY(int rating READ getRating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(Credits* credits READ getCredits CONSTANT)
    Q_PROPERTY(VideosList* videos READ getVideos CONSTANT)

public:
    Movie(QObject *parent = nullptr);

    int getId() const;
    void setId(int newId);

    const QString &getBackdropPath() const;
    void setBackdropPath(const QString &newBackdropPath);

    const QStringList &getGenres() const;
    void setGenres(const QStringList &newGenres);

    const QString &getHomepage() const;
    void setHomepage(const QString &newHomepage);

    const QString &getImdbId() const;
    void setImdbId(const QString &newImdbId);

    const QString &getOriginalLanguage() const;
    void setOriginalLanguage(const QString &newOriginalLanguage);

    const QString &getOriginalTitle() const;
    void setOriginalTitle(const QString &newOriginalTitle);

    const QString &getOverview() const;
    void setOverview(const QString &newOverview);

    const QString &getPosterPath() const;
    void setPosterPath(const QString &newPosterPath);

    const QString &getReleaseDate() const;
    void setReleaseDate(const QString &newReleaseDate);

    const QString &getRevenue() const;
    void setRevenue(const QString &newRevenue);

    int getRuntimeHours() const;
    void setRuntimeHours(int newRuntimeHours);

    int getRuntimeMinutes() const;
    void setRuntimeMinutes(int newRuntimeMinutes);

    const QString &getStatus() const;
    void setStatus(const QString &newStatus);

    const QString &getTagline() const;
    void setTagline(const QString &newTagline);

    const QString &getTitle() const;
    void setTitle(const QString &newTitle);

    double getVoteAvarage() const;
    void setVoteAvarage(double newVoteAvarage);

    uint getVoteCount() const;
    void setVoteCount(uint newVoteCount);

    const QString &getBudget() const;
    void setBudget(const QString &newBudget);

    MovieCollection *getBelongsToCollection() const;

    CompaniesListModel *getProductionCompanies() const;

    CountriesListModel *getProductionCountries() const;

    LanguagesListModel *getSpokenLanguages() const;

    bool getFavorite() const;
    void setFavorite(bool newFavorite);

    bool getWatchlist() const;
    void setWatchlist(bool newWatchlist);

    int getRating() const;
    void setRating(int newRating);

    Credits *getCredits() const;

    VideosList *getVideos() const;

private:
    int id;
    QString backdropPath;
    QString budget;
    QStringList genres;
    QString homepage;
    QString imdbId;
    QString originalLanguage;
    QString originalTitle;
    QString overview;
    QString posterPath;
    QString releaseDate;
    QString revenue;
    int runtimeHours;
    int runtimeMinutes;
    QString status;
    QString tagline;
    QString title;
    double voteAvarage;
    uint voteCount;
    MovieCollection *belongsToCollection;
    CompaniesListModel *productionCompanies;
    CountriesListModel *productionCountries;
    LanguagesListModel *spokenLanguages;
    bool favorite;
    bool watchlist;
    int rating;
    Credits *credits;
    VideosList *videos;

signals:
    void idChanged();
    void backdropPathChanged();
    void genresChanged();
    void homepageChanged();
    void imdbIdChanged();
    void originalLanguageChanged();
    void originalTitleChanged();
    void overviewChanged();
    void posterPathChanged();
    void releaseDateChanged();
    void revenueChanged();
    void runtimeHoursChanged();
    void runtimeMinutesChanged();
    void statusChanged();
    void taglineChanged();
    void titleChanged();
    void voteAvarageChanged();
    void voteCountChanged();
    void budgetChanged();
    void favoriteChanged();
    void watchlistChanged();
    void ratingChanged();
};

#endif // MOVIE_H
