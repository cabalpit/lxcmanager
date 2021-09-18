#include "imagemodel.h"

using namespace model;

/**
 * @brief ImageModel::ImageModel
 *
 * Default constructor, construct object.
 *
 * @param parent waits parent QObject default nullptr.
 */
ImageModel::ImageModel(QObject *parent) : ModelBase(parent)
{
	setTable("images");
	setId("id_image");
}
