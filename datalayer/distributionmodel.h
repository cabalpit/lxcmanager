#ifndef DISTRIBUTIONMODEL_H
#define DISTRIBUTIONMODEL_H

#include "modelbase.h"
#include <QObject>
#include <QWidget>

namespace model
{
	/*!
	 * \brief The DistributionModel class
	 * \version 1.0
	 * \since 2021-09-19
	 * \author Peter Cata
	 *
	 * This class represent Distribution table.
	 */
	class DistributionModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit DistributionModel(QObject *parent = nullptr, const QString &connectionName = "sql_distrib_connection");


	};

}
#endif // DISTRIBUTIONMODEL_H
