#include "variantmodel.h"

using namespace model;

/**
 * @brief VariantModel::VariantModel			[public]
 *
 * Default constructor, construct object.
 *
 * @param parent
 */
VariantModel::VariantModel(QObject *parent) : ModelBase(parent, "sql_variant_connection")
{
	setTable("variants");
	setId("id_variant");
}
