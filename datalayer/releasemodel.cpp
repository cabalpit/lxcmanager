#include "releasemodel.h"

using namespace model;
/*!
 * \brief ReleaseModel::ReleaseModel						[public]
 *
 * Default constructor construct class.
 *
 * \param parent waits parent QObject default nullptr
 * \param connectionName waits a connectionName, default connection name sql_release_connection
 */
ReleaseModel::ReleaseModel(QObject *parent, const QString &connectionName) : ModelBase(parent, connectionName)
{
	setTable("releases");
	setId("id_release");
}
