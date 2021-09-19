#include "distributionmodel.h"

using namespace model;

DistributionModel::DistributionModel(QObject *parent) : ModelBase(parent)
{
	setTable("distributions");
	setId("id_distribution");
}
