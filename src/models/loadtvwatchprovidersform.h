#ifndef LOADTVWATCHPROVIDERSFORM_H
#define LOADTVWATCHPROVIDERSFORM_H

#include <QString>

#include "src/models/form.h"

class LoadTVWatchProvidersForm : public Form
{
public:
    LoadTVWatchProvidersForm(const QString &watchRegion);

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;

private:
    QString watchRegion;
};

#endif // LOADTVWATCHPROVIDERSFORM_H
