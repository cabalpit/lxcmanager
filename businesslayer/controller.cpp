#include "controller.h"

using namespace model;
using namespace businesslayer;

/*!
 * \brief Controller::Controller					[public]
 *
 * Construct the object controller.
 *
 * \param parent waits the parent object default nullptr
 */
Controller::Controller(QObject *parent) : QObject(parent)
{
	m_imageModel = new ImageModel();
	m_distribModel = new DistributionModel();
}

/*!
 * \brief Controller::~Controller
 *
 * Destruct the object constructed in this class;
 */
Controller::~Controller()
{
	m_imageModel->close();
	delete m_imageModel;

	m_distribModel->close();
	delete m_distribModel;
}

/*!
 * \brief Controller::distributions					[public]
 *
 * This method retrieves all data list from \c DistributionModel.
 * \return a list of \c Distribution
 */
QList<Distribution> Controller::distributions()
{
	QSqlQuery *query = m_distribModel->findAll();
	m_distribution.clear();

	while (query->next())
	{
		Distribution distrib = {
			.id = query->value("id_distribution").toInt(),
			.name = query->value("distribution_name").toString(),
			.icon = query->value("logo").toByteArray()
		};

		m_distribution.append(distrib);
	}

	delete query;

	return m_distribution;
}

/*!
 * \brief Controller::release							[public]
 *
 * This method retrieves data releases from \c ReleaseModel sorted by id distribution.
 *
 * \param idDistrib waits the distribution id.
 * \return QHash with key is id of release, value is the release name
 */
QHash<int, QVariant> Controller::release(int idDistrib)
{
	QSqlQuery *query = m_imageModel->findRelease(idDistrib);
	m_release.clear();

	while(query->next())
	{
		m_release.insert(query->value("id_release").toInt(), query->value("release_name"));
	}

	delete query;

	return m_release;
}

/*!
 * \brief Controller::architectures							[public]
 *
 * This method retrieves data architectures from \c ArchitectuerModel sorted by id distribution and id release.
 *
 * \param idDistrib waits the id distribution associated to architecture
 * \param idRelease waits the id release associated to architecture.
 * \return QHash with key is id of architecture, value is the architecture name.
 */
QHash<int, QVariant> Controller::architectures(int idDistrib, int idRelease)
{
	QMap<int, QString>search;
	search.insert(0, QString::number(idDistrib));
	search.insert(1, QString::number(idRelease));


	QSqlQuery *query = m_imageModel->findArch(search);
	m_architecture.clear();

	while (query->next())
	{
		m_architecture.insert(query->value("id_arch").toInt(), query->value("arch_name"));
	}

	delete query;

	return m_architecture;
}

/*!
 * \brief Controller::variants								[public]
 *
 * This method retrieves data variants from \c VariantModel sorted by id distribution, id release, id architecture.
 *
 * \param idDistrib waits the id distribution associated to variant
 * \param idRelease waits the id release associated to variant.
 * \param idArch waits the id release associated to variant.
 * \return QHash with key is id of variant, value is the variant name.
 */
QHash<int, QVariant> Controller::variants(int idDistrib, int idRelease, int idArch)
{
	QMap<int, QString>search;
	search.insert(0, QString::number(idDistrib));
	search.insert(1, QString::number(idRelease));
	search.insert(2, QString::number(idArch));


	QSqlQuery *query = m_imageModel->findVariant(search);
	m_variant.clear();

	if(query)
	{
		while (query->next())
		{
			m_variant.insert(query->value("id_variant").toInt(), query->value("variant_name"));
		}

		delete query;
	}
	return m_variant;
}

/*!
 * \brief Controller::clear									[public]
 *
 * The method clear all attribute of the class.
 */
void Controller::clear()
{
	m_release.clear();
	m_architecture.clear();
	m_variant.clear();
}
