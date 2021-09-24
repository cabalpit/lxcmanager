#include "architecturemodel.h"

using namespace model;

/**
 * @brief ArchitectureModel::ArchitectureModel						[public]
 *
 * Default constructor construct class.
 *
 * @param parent waits parent QObject default nullptr.
 * @param connectionName waits a connectionName, default connection name sql_arch_connection
 */
ArchitectureModel::ArchitectureModel(QObject *parent, const QString &connectionName) : ModelBase(parent, connectionName)
{
	setTable("architectures");
	setId("id_arch");
}
