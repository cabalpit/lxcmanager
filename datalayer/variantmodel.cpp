#include "variantmodel.h"

using namespace model;

/**
 * \brief VariantModel::VariantModel			[public]
 *
 * Default constructor, construct object.
 *
 * \param parent waits parent QObject default nullptr
 * \param connectionName waits a connectionName, default connection name sql_variant_connection
 */
VariantModel::VariantModel(QObject *parent, const QString &connectionName) : ModelBase(parent, connectionName)
{
	setTable("variants");
	setId("id_variant");
}
