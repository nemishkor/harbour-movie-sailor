#include "loadtvwatchprovidersform.h"

LoadTVWatchProvidersForm::LoadTVWatchProvidersForm(const QString &watchRegion) :
    watchRegion(watchRegion)
{

}

void LoadTVWatchProvidersForm::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("watch_region", watchRegion);
}

QString LoadTVWatchProvidersForm::toString() const
{
    return watchRegion;
}
