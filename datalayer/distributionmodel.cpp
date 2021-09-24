#include "distributionmodel.h"

using namespace model;

/**
 * @brief DistributionModel::DistributionModel							[public]
 *
 * Default constructor, construct object.
 *
 * @param parent waits parent QObject default nullptr.
 * @param connectionName waits a connectionName, default connection name sql_distrib_connection
 */
DistributionModel::DistributionModel(QObject *parent, const QString &connectionName) : ModelBase(parent, connectionName)
{
	setTable("distributions");
	setId("id_distribution");
}
