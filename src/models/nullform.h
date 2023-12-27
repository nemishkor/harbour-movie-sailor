#ifndef NULLFORM_H
#define NULLFORM_H

#include "src/models/form.h"

class NullForm : public Form
{
public:
    NullForm();

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;
};

#endif // NULLFORM_H
