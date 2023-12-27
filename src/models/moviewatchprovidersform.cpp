#include "moviewatchprovidersform.h"

MovieWatchProvidersForm::MovieWatchProvidersForm(const QString &region) :
    region(region)
{

}

void MovieWatchProvidersForm::populateQuery(QUrlQuery &urlQuery) const
{
    if (!region.isEmpty()) {
        urlQuery.addQueryItem("watch_region", region);
    }
}

QString MovieWatchProvidersForm::toString() const
{
    return region;
}
