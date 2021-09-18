#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H

#include "modelbase.h"

class VariantModel : public model::ModelBase
{
		Q_OBJECT
	public:
		explicit VariantModel(QObject *parent = nullptr);
};

#endif // VARIANTMODEL_H
