#include "controller.h"

using namespace model;

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_imageModel = new ImageModel(this);
    m_distribModel = new DistributionModel(this);
}

Controller::~Controller()
{
    delete m_distribModel;
    delete m_imageModel;
}

QStringList Controller::distributions()
{
    QSqlQuery *query = m_distribModel->findAll();
    QStringList list;
    list.clear();

    m_distribution.clear();

    while (query->next())
    {
        m_distribution.insert(query->value("id_distribution").toString(), query->value("distribution_name"));
        list << query->value("distribution_name").toString();
    }

    delete query;

    return list;
}

QStringList Controller::release(QString distrib)
{
    QHash<QString, QVariant>::Iterator it;
    m_idxDistrib.clear();

    for(it = m_distribution.begin(); it != m_distribution.end() || !m_idxDistrib.isEmpty(); it++)
    {
        if(it.value() == distrib)
            m_idxDistrib = it.key();
    }

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
    QHash<QString, QVariant>::Iterator it;
    m_idxRelease.clear();

    for(it = m_release.begin(); it != m_release.end() || !m_idxRelease.isEmpty(); it++)
    {
        if(it.value() == release)
            m_idxRelease = it.key();
    }

    QMap<QString, QString>search;
    search.insert("id_distribution", m_idxDistrib);
    search.insert("id_release", m_idxRelease);

    QSqlQuery *query = m_imageModel->findArch(search);
    QStringList list;
    list.clear();

    while (query->next())
    {
        m_architecture.insert(query->value("id_arch").toString(), query->value("architecture_name"));
        list << query->value("architecture_name").toString();
    }

    delete query;

    return list;
}

QStringList Controller::variants(QString arch)
{
    QHash<QString, QVariant>::Iterator it;
    m_idxArch.clear();

    for(it = m_architecture.begin(); it != m_architecture.end() || !m_idxArch.isEmpty(); it++)
    {
        if(it.value() == arch)
            m_idxArch = it.key();
    }

    QMap<QString, QString>search;
    search.insert("id_distribution", m_idxDistrib);
    search.insert("id_release", m_idxRelease);
    search.insert("id_arch", m_idxArch);

    QSqlQuery *query = m_imageModel->findVariant(search);

    QStringList list;
    list.clear();

    while (query->next())
    {
        m_variant.insert(query->value("id_variant").toString(), query->value("variant_name"));
        list << query->value("variant_name").toString();
    }

    delete query;
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
