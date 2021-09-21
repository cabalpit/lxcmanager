#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "datalayer/distributionmodel.h"
#include "datalayer/imagemodel.h"

namespace businesslayer {
	class Controller;
}

class Controller : public QObject
{
		Q_OBJECT
	public:
		explicit Controller(QObject *parent = nullptr);

	signals:

	protected:

	private:

};

#endif // CONTROLLER_H
