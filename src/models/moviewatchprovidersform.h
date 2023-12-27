#ifndef MOVIEWATCHPROVIDERSFORM_H
#define MOVIEWATCHPROVIDERSFORM_H

#include "src/models/form.h"

class MovieWatchProvidersForm : public Form
{
public:
    MovieWatchProvidersForm(const QString &region);

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;

private:
    QString region;
};

#endif // MOVIEWATCHPROVIDERSFORM_H
