#ifndef DISTRIBUTIONMODEL_H
#define DISTRIBUTIONMODEL_H

#include "modelbase.h"
#include <QObject>
#include <QWidget>

namespace model {

	class DistributionModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit DistributionModel(QObject *parent = nullptr, const QString &connectionName = "sql_distrib_connection");


	};

}
#endif // DISTRIBUTIONMODEL_H
