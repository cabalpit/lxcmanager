#include "architecturemodel.h"

using namespace model;

/**
 * @brief ArchitectureModel::ArchitectureModel						[public]
 *
 * Default constructor construct class.
 *
 * @param parent wait parent Object.
 */
ArchitectureModel::ArchitectureModel(QObject *parent) : ModelBase(parent, "sql_arch_connection")
{
	setTable("architectures");
	setId("id_arch");
}
