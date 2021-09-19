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
			explicit DistributionModel(QObject *parent = nullptr);


	};

}
#endif // DISTRIBUTIONMODEL_H
