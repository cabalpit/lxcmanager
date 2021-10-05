#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QSqlQuery>

#include "datalayer/distributionmodel.h"
#include "datalayer/imagemodel.h"
#include "datalayer/distribution.h"

namespace businesslayer
{
	/*!
	 * \class Controller
	 * \brief The Controller class access to models
	 * \since 2021-09-25
	 * \ingroup businesslayer
	 * \author Peter Cata
	 *
	 * Controller accesses to models and retrieves data through \b models classes, and returns
	 * the necessary values.
	 *
	 * It access to the following models \c DistributionModel, \c ReleaseModel, \c ArchitectureModel, \c VariantModel, \c ImageModel.
	 */
	class Controller: public QObject
	{
			Q_OBJECT
		public:
			Controller(QObject *parent = nullptr);
			~Controller();

			QList<model::Distribution> distributions();
			QHash<int, QVariant> release(int idDistrid);
			QHash<int, QVariant> architectures(int idDistrib, int idRelease);
			QHash<int, QVariant> variants(int idDistrib, int idRelease, int idArch);

		public slots:
			void clear();

		protected:

		private:
			model::ImageModel *m_imageModel;
			model::DistributionModel *m_distribModel;

			QList<model::Distribution> m_distribution;
			QHash<int, QVariant> m_release;
			QHash<int, QVariant> m_architecture;
			QHash<int, QVariant> m_variant;
	};
}
#endif // CONTROLLER_H
