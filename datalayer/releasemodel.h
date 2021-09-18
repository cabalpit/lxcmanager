#ifndef RELEASEMODEL_H
#define RELEASEMODEL_H

#include "modelbase.h"

class ReleaseModel : public model::ModelBase
{
		Q_OBJECT
	public:
		explicit ReleaseModel(QObject *parent = nullptr);
};

#endif // RELEASEMODEL_H
