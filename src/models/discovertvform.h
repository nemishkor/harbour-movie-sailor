#ifndef TVDISCOVERY_H
#define TVDISCOVERY_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "src/listmodels/providerslist.h"
#include "src/models/country.h"
#include "src/models/company.h"
#include "src/models/form.h"
#include "src/models/language.h"
#include "src/models/provider.h"
#include "src/models/tvnetwork.h"
#include "src/models/tvstatus.h"
#include "src/models/tvtype.h"
#include "src/models/watchmonetizationtype.h"
#include "src/viewmodels/filterbycompanieslistmodel.h"
#include "src/viewmodels/genreslistmodel.h"
#include "src/viewmodels/keywordslistmodel.h"

class DiscoverTvForm : public QObject, public Form
{
    Q_OBJECT
    Q_PROPERTY(QDateTime airDateGte READ getAirDateGte WRITE setAirDateGte NOTIFY airDateGteChanged)
    Q_PROPERTY(QDateTime airDateLte READ getAirDateLte WRITE setAirDateLte NOTIFY airDateLteChanged)
    Q_PROPERTY(int firstAirDateYear READ getFirstAirDateYear WRITE setFirstAirDateYear NOTIFY firstAirDateYearChanged)
    Q_PROPERTY(QDateTime firstAirDateGte READ getFirstAirDateGte WRITE setFirstAirDateGte NOTIFY firstAirDateGteChanged)
    Q_PROPERTY(QDateTime firstAirDateLte READ getFirstAirDateLte WRITE setFirstAirDateLte NOTIFY firstAirDateLteChanged)
    Q_PROPERTY(bool includeAdult READ getIncludeAdult WRITE setIncludeAdult NOTIFY includeAdultChanged)
    Q_PROPERTY(bool includeNullFirstAirDates READ getIncludeNullFirstAirDates WRITE setIncludeNullFirstAirDates NOTIFY includeNullFirstAirDatesChanged)
    Q_PROPERTY(bool screenedTheatrically READ getScreenedTheatrically WRITE setScreenedTheatrically NOTIFY screenedTheatricallyChanged)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(Sorting sorting READ getSorting WRITE setSorting NOTIFY sortingChanged)
    Q_PROPERTY(Order order READ getOrder WRITE setOrder NOTIFY orderChanged)
    Q_PROPERTY(double voteAverageGte READ getVoteAverageGte WRITE setVoteAverageGte NOTIFY voteAverageGteChanged)
    Q_PROPERTY(double voteAverageLte READ getVoteAverageLte WRITE setVoteAverageLte NOTIFY voteAverageLteChanged)
    Q_PROPERTY(int voteCountGte READ getVoteCountGte WRITE setVoteCountGte NOTIFY voteCountGteChanged)
    Q_PROPERTY(int voteCountLte READ getVoteCountLte WRITE setVoteCountLte NOTIFY voteCountLteChanged)
    Q_PROPERTY(Country* watchRegion READ getWatchRegion CONSTANT)
    Q_PROPERTY(ProvidersList* providersList READ getProvidersList CONSTANT)
    Q_PROPERTY(QStringList withWatchProviders READ getWithWatchProviders WRITE setWithWatchProviders NOTIFY withWatchProvidersChanged)
    Q_PROPERTY(QStringList withoutWatchProviders READ getWithoutWatchProviders WRITE setWithoutWatchProviders NOTIFY withoutWatchProvidersChanged)
    Q_PROPERTY(ListCombinationMode withWatchProvidersCombinationMode READ getWithWatchProvidersCombinationMode WRITE setWithWatchProvidersCombinationMode NOTIFY withWatchProvidersCombinationModeChanged)
    Q_PROPERTY(ListCombinationMode withoutWatchProvidersCombinationMode READ getWithoutWatchProvidersCombinationMode WRITE setWithoutWatchProvidersCombinationMode NOTIFY withoutWatchProvidersCombinationModeChanged)
    Q_PROPERTY(TvNetwork* withNetworks READ getWithNetworks CONSTANT)
    Q_PROPERTY(Country* withOriginCountry READ getWithOriginCountry CONSTANT)
    Q_PROPERTY(Language* withOriginLanguage READ getWithOriginLanguage CONSTANT)
    Q_PROPERTY(int withRuntimeGte READ getWithRuntimeGte WRITE setWithRuntimeGte NOTIFY withRuntimeGteChanged)
    Q_PROPERTY(int withRuntimeLte READ getWithRuntimeLte WRITE setWithRuntimeLte NOTIFY withRuntimeLteChanged)

public:
    enum Sorting {
        Popularity = 0,
        Revenue = 1,
        PrimaryReleaseDate = 2,
        VoteAverage = 3,
        VoteCount = 4,
    };
    enum Order {
        ASC = 0,
        DESC = 1
    };
    enum ListCombinationMode {
        AND = 0,
        OR = 1,
    };

    Q_ENUMS(Sorting)
    Q_ENUMS(Order)
    Q_ENUMS(ListCombinationMode)

    DiscoverTvForm(QObject *parent = nullptr);

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;

    const QDateTime &getAirDateGte() const;
    void setAirDateGte(const QDateTime &newAirDateGte);

    const QDateTime &getAirDateLte() const;
    void setAirDateLte(const QDateTime &newAirDateLte);

    int getFirstAirDateYear() const;
    void setFirstAirDateYear(int newFirstAirDateYear);

    const QDateTime &getFirstAirDateGte() const;
    void setFirstAirDateGte(const QDateTime &newFirstAirDateGte);

    const QDateTime &getFirstAirDateLte() const;
    void setFirstAirDateLte(const QDateTime &newFirstAirDateLte);

    bool getIncludeAdult() const;
    void setIncludeAdult(bool newIncludeAdult);

    bool getIncludeNullFirstAirDates() const;
    void setIncludeNullFirstAirDates(bool newIncludeNullFirstAirDates);

    bool getScreenedTheatrically() const;
    void setScreenedTheatrically(bool newScreenedTheatrically);

    Sorting getSorting() const;
    void setSorting(Sorting newSorting);

    Order getOrder() const;
    void setOrder(Order newOrder);

    double getVoteAverageGte() const;
    void setVoteAverageGte(double newVoteAverageGte);

    double getVoteAverageLte() const;
    void setVoteAverageLte(double newVoteAverageLte);

    int getVoteCountGte() const;
    void setVoteCountGte(int newVoteCountGte);

    int getVoteCountLte() const;
    void setVoteCountLte(int newVoteCountLte);

    Country *getWatchRegion() const;
    ProvidersList *getProvidersList() const;
    const ListCombinationMode &getWithWatchProvidersCombinationMode() const;
    void setWithWatchProvidersCombinationMode(const ListCombinationMode &newWithWatchProvidersCombinationMode);
    const ListCombinationMode &getWithoutWatchProvidersCombinationMode() const;
    void setWithoutWatchProvidersCombinationMode(const ListCombinationMode &newWithoutWatchProvidersCombinationMode);

    const QStringList &getWithWatchProviders() const;
    void setWithWatchProviders(const QStringList &newWithWatchProviders);

    const QStringList &getWithoutWatchProviders() const;
    void setWithoutWatchProviders(const QStringList &newWithoutWatchProviders);

    int getPage() const;
    void setPage(int newPage);

    TvNetwork *getWithNetworks() const;

    Country *getWithOriginCountry() const;

    Language *getWithOriginLanguage() const;

    int getWithRuntimeGte() const;
    void setWithRuntimeGte(int newWithRuntimeGte);

    int getWithRuntimeLte() const;
    void setWithRuntimeLte(int newWithRuntimeLte);

signals:
    void airDateGteChanged();
    void airDateLteChanged();
    void firstAirDateYearChanged();
    void firstAirDateGteChanged();
    void firstAirDateLteChanged();
    void includeAdultChanged();
    void includeNullFirstAirDatesChanged();
    void screenedTheatricallyChanged();
    void sortingChanged();
    void orderChanged();
    void voteAverageGteChanged();
    void voteAverageLteChanged();
    void voteCountGteChanged();
    void voteCountLteChanged();
    void withWatchProvidersCombinationModeChanged();
    void withoutWatchProvidersCombinationModeChanged();
    void withWatchProvidersChanged();
    void withoutWatchProvidersChanged();
    void pageChanged();
    void withRuntimeGteChanged();
    void withRuntimeLteChanged();

public slots:
    void providersChanged();

private:
    QDateTime airDateGte;
    QDateTime airDateLte;
    int firstAirDateYear;
    QDateTime firstAirDateGte;
    QDateTime firstAirDateLte;
    bool includeAdult;
    bool includeNullFirstAirDates;
    int page;
    bool screenedTheatrically;
    Sorting sorting;
    Order order;
    double voteAverageGte;
    double voteAverageLte;
    int voteCountGte;
    int voteCountLte;

    Country *watchRegion;
    ProvidersList *providersList;
    QStringList withWatchProviders;
    ListCombinationMode withWatchProvidersCombinationMode;
    QStringList withoutWatchProviders;
    ListCombinationMode withoutWatchProvidersCombinationMode;

    TvNetwork *withNetworks;
    Country *withOriginCountry;
    Language *withOriginLanguage;
    int withRuntimeGte;
    int withRuntimeLte;

    QList<Company> withCompanies;
    ListCombinationMode withCompaniesCombinationMode;
    QList<Company> withoutCompanies;

    QList<Genre> withGenres;
    ListCombinationMode withGenresCombinationMode;
    QList<Genre> withoutGenres;

    QList<Keyword> withKeywords;
    QList<Keyword> withoutKeywords;

    QList<TVStatus> withStatus;
    ListCombinationMode withStatusCombinationMode;

    QList<WatchMonetizationType> withWatchMonetizationTypes;

    QList<TVType> withtype;
    ListCombinationMode withTypeCombinationMode;
};

#endif // TVDISCOVERY_H
