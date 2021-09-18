#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "modelbase.h"
#include <QObject>

class ImageModel : public model::ModelBase
{
		Q_OBJECT
	public:
		explicit ImageModel(QObject *parent = nullptr);
};

#endif // IMAGEMODEL_H
