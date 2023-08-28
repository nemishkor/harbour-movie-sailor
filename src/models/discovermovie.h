#ifndef DISCOVERMOVIE_H
#define DISCOVERMOVIE_H

#include <QObject>

#include "src/models/country.h"
#include "src/models/language.h"
#include "src/viewmodels/companieslistmodel.h"
#include "src/viewmodels/genreslistmodel.h"
#include "src/viewmodels/keywordslistmodel.h"
#include "src/viewmodels/peoplelistmodel.h"
#include "src/viewmodels/movieproviderslistmodel.h"

class DiscoverMovie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(Country* originCountry READ getOriginCountry CONSTANT)
    Q_PROPERTY(Language* language READ getLanguage CONSTANT)
    Q_PROPERTY(Language* originLanguage READ getOriginLanguage CONSTANT)
    Q_PROPERTY(GenresListModel* genres READ getGenres CONSTANT)
    Q_PROPERTY(MovieProvidersListModel* providers READ getProviders CONSTANT)
    Q_PROPERTY(QString sortBy READ getSortBy WRITE setSortBy NOTIFY sortByChanged)
    Q_PROPERTY(QString order READ getOrder WRITE setOrder NOTIFY orderChanged)
    Q_PROPERTY(QString watchRegion READ getWatchRegion WRITE setWatchRegion NOTIFY watchRegionChanged)
    Q_PROPERTY(Country* region READ getRegion CONSTANT)
    Q_PROPERTY(QString primaryReleaseYear READ getPrimaryReleaseYear WRITE setPrimaryReleaseYear NOTIFY primaryReleaseYearChanged)
    Q_PROPERTY(QString primaryReleaseDateGte READ getPrimaryReleaseDateGte WRITE setPrimaryReleaseDateGte NOTIFY primaryReleaseDateGteChanged)
    Q_PROPERTY(QString primaryReleaseDateLte READ getPrimaryReleaseDateLte WRITE setPrimaryReleaseDateLte NOTIFY primaryReleaseDateLteChanged)
    Q_PROPERTY(double voteAverageGte READ getVoteAverageGte WRITE setVoteAverageGte NOTIFY voteAverageGteChanged)
    Q_PROPERTY(double voteAverageLte READ getVoteAverageLte WRITE setVoteAverageLte NOTIFY voteAverageLteChanged)
    Q_PROPERTY(uint voteCountGte READ getVoteCountGte WRITE setVoteCountGte NOTIFY voteCountGteChanged)
    Q_PROPERTY(bool includeVideo READ getIncludeVideo WRITE setIncludeVideo NOTIFY includeVideoChanged)
    Q_PROPERTY(bool includeAdult READ getIncludeAdult WRITE setIncludeAdult NOTIFY includeAdultChanged)
    Q_PROPERTY(PeopleListModel* anyRoleList READ getAnyRoleList CONSTANT)
    Q_PROPERTY(PeopleListModel* castRoleList READ getCastRoleList CONSTANT)
    Q_PROPERTY(PeopleListModel* crewRoleList READ getCrewRoleList CONSTANT)
    Q_PROPERTY(CompaniesListModel* companies READ getCompanies CONSTANT)
    Q_PROPERTY(KeywordsListModel* keywords READ getKeywords CONSTANT)

public:
    explicit DiscoverMovie(QObject *parent);

    uint getPage() const;
    void setPage(uint newPage);

    const QString &getSortBy() const;
    void setSortBy(const QString &newSortBy);

    const QString &getOrder() const;
    void setOrder(const QString &newOrder);

    const QString &getWatchRegion() const;
    void setWatchRegion(const QString &newWatchRegion);

    const QString &getPrimaryReleaseYear() const;
    void setPrimaryReleaseYear(const QString &newPrimaryReleaseYear);

    const QString &getPrimaryReleaseDateGte() const;
    void setPrimaryReleaseDateGte(const QString &newPrimaryReleaseDateGte);

    const QString &getPrimaryReleaseDateLte() const;
    void setPrimaryReleaseDateLte(const QString &newPrimaryReleaseDateLte);

    double getVoteAverageGte() const;
    void setVoteAverageGte(double newVoteAverageGte);

    double getVoteAverageLte() const;
    void setVoteAverageLte(double newVoteAverageLte);

    uint getVoteCountGte() const;
    void setVoteCountGte(uint newVoteCountGte);

    bool getIncludeVideo() const;
    void setIncludeVideo(bool newIncludeVideo);

    bool getIncludeAdult() const;
    void setIncludeAdult(bool newIncludeAdult);

    Country *getOriginCountry() const;
    Language *getLanguage() const;
    Language *getOriginLanguage() const;
    GenresListModel *getGenres() const;
    MovieProvidersListModel *getProviders() const;
    Country *getRegion() const;
    PeopleListModel *getAnyRoleList() const;
    PeopleListModel *getCastRoleList() const;
    PeopleListModel *getCrewRoleList() const;
    CompaniesListModel *getCompanies() const;
    KeywordsListModel *getKeywords() const;

signals:
    void pageChanged();
    void sortByChanged();
    void orderChanged();
    void watchRegionChanged();
    void primaryReleaseYearChanged();
    void primaryReleaseDateGteChanged();
    void primaryReleaseDateLteChanged();
    void voteAverageGteChanged();
    void voteAverageLteChanged();
    void voteCountGteChanged();
    void includeVideoChanged();
    void includeAdultChanged();

private:
    uint page;
    uint voteCountGte;
    Country *region;
    QString sortBy;
    QString order;
    QString watchRegion;
    QString primaryReleaseYear;
    QString primaryReleaseDateGte;
    QString primaryReleaseDateLte;
    double voteAverageGte;
    double voteAverageLte;
    bool includeVideo;
    bool includeAdult;
    Country *originCountry;
    Language *language;
    Language *originLanguage;
    GenresListModel *genres;
    MovieProvidersListModel *providers;
    PeopleListModel *anyRoleList;
    PeopleListModel *castRoleList;
    PeopleListModel *crewRoleList;
    CompaniesListModel *companies;
    KeywordsListModel *keywords;
};

#endif // DISCOVERMOVIE_H
