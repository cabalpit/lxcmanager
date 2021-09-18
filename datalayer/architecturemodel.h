#ifndef ARCHITECTUREMODEL_H
#define ARCHITECTUREMODEL_H

#include "modelbase.h"

class ArchitectureModel : public model::ModelBase
{
		Q_OBJECT
	public:
		explicit ArchitectureModel(QObject *parent = nullptr);
};

#endif // ARCHITECTUREMODEL_H
