#ifndef ARCHITECTUREMODEL_H
#define ARCHITECTUREMODEL_H

#include <QObject>
#include "modelbase.h"

namespace model
{
	/*!
	 * \brief The ArchitectureModel class
	 * \version 1.0
	 * \since 2021-09-19
	 * \author Peter Cata
	 *
	 * This class represent Architecture table.
	 */
	class ArchitectureModel : public model::ModelBase
	{
			Q_OBJECT
		public:
			explicit ArchitectureModel(QObject *parent = nullptr, const QString &connectionName = "sql_arch_connection");
	};
}

#endif // ARCHITECTUREMODEL_H
