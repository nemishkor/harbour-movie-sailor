#ifndef LOADPERSONFORM_H
#define LOADPERSONFORM_H

#include "form.h"

class LoadPersonForm : public Form
{
public:
    LoadPersonForm();

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;
};

#endif // LOADPERSONFORM_H
