#include "distributionmodel.h"

using namespace model;

DistributionModel::DistributionModel(QObject *parent) : ModelBase(parent, "sql_distrib_connection")
{
	setTable("distributions");
	setId("id_distribution");
}
