#ifndef FORM_H
#define FORM_H

#include <QUrlQuery>

class Form
{
public:
    Form();

    virtual void populateQuery(QUrlQuery &urlQuery) const =0;
    virtual QString toString() const =0; // is used for cache key
    virtual bool isValid() const;

    bool isDirty() const;
    void setDirty(bool newDirty);

private:
    bool dirty; // is used for cache

};

#endif // FORM_H
