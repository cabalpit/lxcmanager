#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "modelbase.h"
#include <QObject>

namespace model {

	/**
	 * @brief The ImageModel class
	 *
	 * This class represent images table.
	 *
	 * @version 1.0
	 * @since 2021-09-19
	 * @author pcata
	 */
	class ImageModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit ImageModel(QObject *parent = nullptr);
	};
}

#endif // IMAGEMODEL_H
