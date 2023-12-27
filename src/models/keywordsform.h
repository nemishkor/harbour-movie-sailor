#ifndef KEYWORDSFORM_H
#define KEYWORDSFORM_H

#include <QString>

#include "src/models/form.h"

class KeywordsForm : public Form
{
public:
    KeywordsForm(const QString &query, int page);

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;

private:
    QString query;
    int page;
};

#endif // KEYWORDSFORM_H
