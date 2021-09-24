#include "controller.h"

using namespace model;
using namespace businesslayer;

Controller::Controller(QObject *parent) : QObject(parent)
{
	m_imageModel = new ImageModel();
	m_distribModel = new DistributionModel();
}

Controller::~Controller()
{
	m_imageModel->close();
	delete m_imageModel;

	m_distribModel->close();
	delete m_distribModel;
}

QMap<QString, QByteArray> Controller::distributions()
{
	QSqlQuery *query = m_distribModel->findAll();
	QMap<QString, QByteArray> list;
	list.clear();

	m_distribution.clear();

	while (query->next())
	{
		m_distribution.insert(query->value("id_distribution").toString(), query->value("distribution_name"));
		list.insert(query->value("distribution_name").toString(), query->value("logo").toByteArray());
	}

	delete query;

	return list;
}

QStringList Controller::release(QString distrib)
{
	QHashIterator<QString, QVariant>it(m_distribution);

	if(it.findNext(distrib))
		m_idxDistrib = it.key();


	QSqlQuery *query = m_imageModel->findRelease(m_idxDistrib);
	QStringList list;
	list.clear();

	while(query->next())
	{
		m_release.insert(query->value("id_release").toString(), query->value("release_name"));
		list << query->value("release_name").toString();
	}

	delete query;

	return list;
}

QStringList Controller::architectures(QString release)
{
	QHashIterator<QString, QVariant> it(m_release);
	m_idxRelease.clear();

	if(it.findNext(release))
		m_idxRelease = it.key();

	QMap<int, QString>search;
	search.insert(0, m_idxDistrib);
	search.insert(1, m_idxRelease);


	QSqlQuery *query = m_imageModel->findArch(search);
	QStringList list;
	list.clear();

	while (query->next())
	{
		m_architecture.insert(query->value("id_arch").toString(), query->value("arch_name"));
		list << query->value("arch_name").toString();
	}

	delete query;

	return list;
}

QStringList Controller::variants(QString arch)
{
	QHashIterator<QString, QVariant> it(m_architecture);
	m_idxArch.clear();

	if(it.findNext(arch))
		m_idxArch = it.key();

	QMap<int, QString>search;
	search.insert(0, m_idxDistrib);
	search.insert(1, m_idxRelease);
	search.insert(2, m_idxArch);


	QSqlQuery *query = m_imageModel->findVariant(search);

	QStringList list;
	list.clear();

	if(query)
	{
		while (query->next())
		{
			m_variant.insert(query->value("id_variant").toString(), query->value("variant_name"));
			list << query->value("variant_name").toString();
		}

		delete query;
	}
	return list;
}

void Controller::clear()
{
	m_idxArch.clear();
	m_idxDistrib.clear();
	m_idxRelease.clear();

	m_release.clear();
	m_architecture.clear();
	m_variant.clear();
}
