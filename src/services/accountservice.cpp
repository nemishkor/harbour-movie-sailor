#include "accountservice.h"

AccountService::AccountService(Account *account,
                               Api &api,
                               Settings &settings,
                               GenresListModel *genresListModel,
                               MovieService &movieService,
                               TvService &tvService,
                               QObject *parent) :
    QObject(parent),
    apiWorkerName(Api::Account),
    request(api.getRequestInfo(apiWorkerName)),
    api(api),
    settings(settings),
    genresListModel(genresListModel),
    movieService(movieService),
    tvService(tvService),
    requestToken(new RequestToken(false, "", QDateTime(), this)),
    account(account),
    favoriteMovies(new AccountMediaListService(Api::FavoriteMovies, MediaListItem::MovieType, api, genresListModel, movieService, tvService, this)),
    favoriteTv(new AccountMediaListService(Api::FavoriteTv, MediaListItem::TvType, api, genresListModel, movieService, tvService, this)),
    ratedMovies(new AccountMediaListService(Api::RatedMovies, MediaListItem::MovieType, api, genresListModel, movieService, tvService, this)),
    ratedTv(new AccountMediaListService(Api::RatedTv, MediaListItem::TvType, api, genresListModel, movieService, tvService, this)),
    watchlistMovies(new AccountMediaListService(Api::WatchlistMovies, MediaListItem::MovieType, api, genresListModel, movieService, tvService, this)),
    watchlistTv(new AccountMediaListService(Api::WatchlistTv, MediaListItem::TvType, api, genresListModel, movieService, tvService, this))
{
    connect(&api, &Api::requestRefreshTokenDone, this, &AccountService::saveRefreshToken);
    connect(&api, &Api::createSessionDone, this, &AccountService::saveSession);
    connect(&api, &Api::loadAccountDone, this, &AccountService::saveAccount);

    connect(&api, &Api::favoriteMoviesDone, favoriteMovies, &AccountMediaListService::fillModelFromApi);
    connect(&api, &Api::favoriteTvDone, favoriteTv, &AccountMediaListService::fillModelFromApi);
    connect(&api, &Api::ratedMoviesDone, ratedMovies, &AccountMediaListService::fillModelFromApi);
    connect(&api, &Api::ratedTvDone, ratedTv, &AccountMediaListService::fillModelFromApi);
    connect(&api, &Api::watchlistMoviesDone, watchlistMovies, &AccountMediaListService::fillModelFromApi);
    connect(&api, &Api::watchlistTvDone, watchlistTv, &AccountMediaListService::fillModelFromApi);

    connect(movieService.getModel(), &Movie::favoriteChanged, this, &AccountService::movieFavoriteChanged);
    connect(movieService.getModel(), &Movie::ratingChanged, this, &AccountService::movieRatingChanged);
    connect(movieService.getModel(), &Movie::watchlistChanged, this, &AccountService::movieWatchlistChanged);

    connect(movieService.getModel(), &Movie::favoriteChanged, this, &AccountService::movieFavoriteChanged);
    connect(movieService.getModel(), &Movie::ratingChanged, this, &AccountService::movieRatingChanged);
    connect(movieService.getModel(), &Movie::watchlistChanged, this, &AccountService::movieWatchlistChanged);

    connect(tvService.getModel(), &Tv::favoriteChanged, this, &AccountService::tvFavoriteChanged);
    connect(tvService.getModel(), &Tv::ratingChanged, this, &AccountService::tvRatingChanged);
    connect(tvService.getModel(), &Tv::watchlistChanged, this, &AccountService::tvWatchlistChanged);

    if (!settings.getSessionId().isEmpty()) {
        qDebug() << "AccountService: sessionId exists. Load account's data";
        api.getResource(apiWorkerName);
    }
}

void AccountService::createRequestToken()
{
    qDebug() << "AccountService: createRequestToken";
    if (requestToken->isValid()) {
        qDebug() << "AccountService: request token is valid";
        return;
    }
    qDebug() << "AccountService: request token is not valid. Request for refresh token";
    api.requestRefreshToken();
}

void AccountService::createSessionId()
{
    api.createSessionId(requestToken->getRawBody());
}

void AccountService::logout()
{
    requestToken->setRawBody(QByteArray());
    requestToken->setSuccess(false);
    requestToken->setRequestToken(QString());
    requestToken->setExpireAt(QDateTime());

    settings.setSessionId("");

    account->setId(0);
    account->setLanguage(QString());
    account->setCountry(QString());
    account->setName(QString());
    account->setIncludeAdult(true);
    account->setUsername(QString());
}

RequestToken *AccountService::getRequestToken() const
{
    return requestToken;
}

AccountMediaListService *AccountService::getFavoriteMovies() const
{
    return favoriteMovies;
}

AccountMediaListService *AccountService::getFavoriteTv() const
{
    return favoriteTv;
}

AccountMediaListService *AccountService::getRatedMovies() const
{
    return ratedMovies;
}

AccountMediaListService *AccountService::getRatedTv() const
{
    return ratedTv;
}

AccountMediaListService *AccountService::getWatchlistMovies() const
{
    return watchlistMovies;
}

AccountMediaListService *AccountService::getWatchlistTv() const
{
    return watchlistTv;
}

RequestInfo *AccountService::getRequest() const
{
    return request;
}

void AccountService::saveRefreshToken(QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    QDateTime expiresAt = QDateTime::fromString(obj["expires_at"].toString(), Qt::ISODate);
    qDebug() << "AccountService: expiresAt is valid:" << (expiresAt.isValid() ? "true" : "false");

    requestToken->setRawBody(data);
    requestToken->setSuccess(obj["success"].toBool());
    requestToken->setRequestToken(obj["request_token"].toString());
    requestToken->setExpireAt(expiresAt);
    qDebug() << "AccountService: refresh token is saved";
}

void AccountService::saveSession(QByteArray &data)
{
    qInfo() << "AccountService: session is saved";
    requestToken->setRawBody(QByteArray());
    requestToken->setSuccess(false);
    requestToken->setRequestToken(QString());
    requestToken->setExpireAt(QDateTime());
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    settings.setSessionId(obj["session_id"].toString());
    api.getResource(apiWorkerName);
}

void AccountService::saveAccount(QByteArray &data)
{
    qDebug() << "AccountService: save account";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    account->setId(obj["id"].toInt());
    account->setLanguage(obj["iso_639_1"].toString());
    account->setCountry(obj["iso_3166_1"].toString());
    account->setName(obj["name"].toString());
    account->setIncludeAdult(obj["include_adult"].toBool());
    account->setUsername(obj["username"].toString());
}

void AccountService::movieFavoriteChanged()
{
    favoriteMovies->getList()->setDirty(true);
}

void AccountService::movieRatingChanged()
{
    ratedMovies->getList()->setDirty(true);
}

void AccountService::movieWatchlistChanged()
{
    watchlistMovies->getList()->setDirty(true);
}

void AccountService::tvFavoriteChanged()
{
    favoriteTv->getList()->setDirty(true);
}

void AccountService::tvRatingChanged()
{
    ratedTv->getList()->setDirty(true);
}

void AccountService::tvWatchlistChanged()
{
    watchlistTv->getList()->setDirty(true);
}
