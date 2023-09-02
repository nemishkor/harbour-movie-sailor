#ifndef ACCOUNTSERVICE_H
#define ACCOUNTSERVICE_H

#include <QDebug>
#include <QObject>
#include <QDateTime>

#include "src/api.h"
#include "src/models/account.h"
#include "src/models/accountmoviesform.h"
#include "src/models/settings.h"
#include "src/models/requesttoken.h"
#include "src/services/accountmedialistservice.h"
#include "src/services/movieservice.h"
#include "src/viewmodels/movieslistmodel.h"
#include "src/viewmodels/genreslistmodel.h"

class AccountService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RequestToken* requestToken READ getRequestToken CONSTANT)
    Q_PROPERTY(AccountMediaListService* favoriteMovies READ getFavoriteMovies CONSTANT)
    Q_PROPERTY(AccountMediaListService* favoriteTv READ getFavoriteTv CONSTANT)
    Q_PROPERTY(AccountMediaListService* ratedMovies READ getRatedMovies CONSTANT)
    Q_PROPERTY(AccountMediaListService* ratedTv READ getRatedTv CONSTANT)
    Q_PROPERTY(AccountMediaListService* watchlistMovies READ getWatchlistMovies CONSTANT)
    Q_PROPERTY(AccountMediaListService* watchlistTv READ getWatchlistTv CONSTANT)

public:
    AccountService(Account *account,
                   Api &api,
                   Settings &settings,
                   GenresListModel *genresListModel,
                   MovieService &movieService,
                   QObject *parent);

    Q_INVOKABLE void createRequestToken();
    Q_INVOKABLE void createSessionId();
    Q_INVOKABLE void logout();

    RequestToken *getRequestToken() const;

    AccountMediaListService *getFavoriteMovies() const;
    AccountMediaListService *getFavoriteTv() const;
    AccountMediaListService *getRatedMovies() const;
    AccountMediaListService *getRatedTv() const;
    AccountMediaListService *getWatchlistMovies() const;
    AccountMediaListService *getWatchlistTv() const;

private:
    Api &api;
    Settings &settings;
    GenresListModel *genresListModel;
    MovieService &movieService;
    RequestToken *requestToken;
    Account *account;

    AccountMediaListService *favoriteMovies;
    AccountMediaListService *favoriteTv;
    AccountMediaListService *ratedMovies;
    AccountMediaListService *ratedTv;
    AccountMediaListService *watchlistMovies;
    AccountMediaListService *watchlistTv;

public slots:
    void saveRefreshToken(QByteArray &data);
    void saveSession(QByteArray &data);
    void saveAccount(QByteArray &data);
    void movieFavoriteChanged();
    void movieRatingChanged();
    void movieWatchlistChanged();

};

#endif // ACCOUNTSERVICE_H
