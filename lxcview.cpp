#include "lxcview.h"

using namespace businesslayer;

LxcView::LxcView(QWidget *parent) : QTableView(parent)
{
	m_lxc = new LxcContainer(this);

	initModel();

	horizontalHeader()->setVisible(false);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setStyleSheet(m_css["card"]);
}

LxcView::~LxcView()
{
	delete m_lxc;
}

void LxcView::createContainer(const QStringList &container)
{

}

void LxcView::destroyContainer()
{

}

void LxcView::initModel()
{
	m_model.clear();

	lxc_container **containers = m_lxc->allContainersList();
	int allCount = m_lxc->lxcCountAll();

	for (int i = 0; i < allCount; i++)
	{
		QList<QStandardItem *> items;
		items.append(new QStandardItem(containers[i]->name));

		const char *state = containers[i]->state(containers[i]);

		items.append(new QStandardItem(state));

		// get all ips
		if(qstrcmp(state, "RUNNING") == 0)
		{
			QStringList ipsList = QStringList();

			char **interfaces = containers[i]->get_interfaces(containers[i]);

			for(int itf = 0; interfaces[itf] != NULL; itf++)
			{
				char *interface = interfaces[itf];
				char **ips = containers[i]->get_ips(containers[i], interface, "inet", 0);

				for(int ip = 0; ips[ip] != NULL; ip++)
				{
					if(qstrcmp(ips[ip], "127.0.0.1") != 0)
						ipsList.append(ips[ip]);
				}
			}

			if(!ipsList.empty())
			{
				items.append(new QStandardItem(ipsList.join(";")));
			}
			else
			{
				items.append(new QStandardItem("-"));
			}
		}
		else
		{
			items.append(new QStandardItem("-"));
		}


		QPushButton *playStopBtn = new QPushButton();
		playStopBtn->setIcon(qstrcmp(state, "RUNNING") == 0 ? QIcon(":/icons/pause_black") : QIcon(":/icons/play_black"));
		playStopBtn->setFixedWidth(26);
		playStopBtn->setObjectName(QString("state_") + QString(containers[i]->name));

		QPushButton *configBtn = new QPushButton();
		configBtn->setIcon(QIcon(":/icons/settings_black"));
		configBtn->setFixedWidth(26);
		configBtn->setObjectName(QString("setting_") + QString(containers[i]->name));


		items.append(new QStandardItem());
		items.append(new QStandardItem());

		m_model.appendRow(items);

		qDebug() << m_model.rowCount() - 1;

		setIndexWidget(m_model.index(m_model.rowCount() - 1, 3) , playStopBtn);
		setIndexWidget(m_model.index(m_model.rowCount() - 1, 4) , configBtn);

		setModel(&m_model);
	}
}

void LxcView::startContainer()
{

}

void LxcView::stopContainer()
{

}

void LxcView::configContainer()
{

}

