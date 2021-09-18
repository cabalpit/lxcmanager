#include "releasemodel.h"

using namespace model;
/**
 * @brief ReleaseModel::ReleaseModel						[public]
 *
 * Default constructor construct class.
 *
 * @param parent wait parent Object.
 */
ReleaseModel::ReleaseModel(QObject *parent) : ModelBase(parent)
{
	setTable("releases");
	setId("id_release");
}
