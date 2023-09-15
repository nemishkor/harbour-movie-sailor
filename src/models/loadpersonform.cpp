#include "loadpersonform.h"

LoadPersonForm::LoadPersonForm()
{

}

void LoadPersonForm::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("append_to_response", "external_ids,images");
}

QString LoadPersonForm::toString() const
{
    return "";
}
