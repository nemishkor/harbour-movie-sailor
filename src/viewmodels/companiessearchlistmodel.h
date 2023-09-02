#ifndef COMPANIESSEARCHLISTMODEL_H
#define COMPANIESSEARCHLISTMODEL_H

#include "filterbycompanieslistmodel.h"

class CompaniesSearchListModel : public FilterByCompaniesListModel
{
public:
    explicit CompaniesSearchListModel(FilterByCompaniesListModel &model, QObject *parent);
    Company findById(int id);
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

private:
    FilterByCompaniesListModel &model;
};

#endif // COMPANIESSEARCHLISTMODEL_H
