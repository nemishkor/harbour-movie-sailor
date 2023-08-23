#ifndef COMPANIESSEARCHLISTMODEL_H
#define COMPANIESSEARCHLISTMODEL_H

#include "companieslistmodel.h"

class CompaniesSearchListModel : public CompaniesListModel
{
public:
    explicit CompaniesSearchListModel(CompaniesListModel &model, QObject *parent);
    Company findById(int id);
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

private:
    CompaniesListModel &model;
};

#endif // COMPANIESSEARCHLISTMODEL_H
