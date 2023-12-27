#include "nullform.h"

NullForm::NullForm()
{

}

void NullForm::populateQuery(QUrlQuery &urlQuery) const
{
    Q_UNUSED(urlQuery);
}

QString NullForm::toString() const
{
    return QString();
}
