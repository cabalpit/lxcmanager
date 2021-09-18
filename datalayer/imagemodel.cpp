#include "imagemodel.h"

using namespace model;

ImageModel::ImageModel(QObject *parent) : ModelBase(parent)
{
	setTable("images");
	setId("id_image");
}
