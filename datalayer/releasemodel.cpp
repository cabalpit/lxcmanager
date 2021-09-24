#include "releasemodel.h"

using namespace model;
/**
 * @brief ReleaseModel::ReleaseModel						[public]
 *
 * Default constructor construct class.
 *
 * @param parent wait parent Object.
 */
ReleaseModel::ReleaseModel(QObject *parent) : ModelBase(parent, "sql_release_connection")
{
	setTable("releases");
	setId("id_release");
}
