#include "restoresnapdialog.h"

using namespace businesslayer;

RestoreSnapDialog::RestoreSnapDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

RestoreSnapDialog::~RestoreSnapDialog()
{
	delete m_infoLabel;
	delete m_containerLabel;
	delete m_snapLabel;
	delete m_newNameLabel;
	delete m_alert;

	delete m_containerCombo;
	delete m_snapListView;
	delete m_newNameLienEdit;

	delete m_cancel;
	delete m_restore;

	delete m_layout;
	delete m_loader;
	delete m_lxc;

	if(m_containers)
	{
		for(int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = NULL;
		}

		delete [] m_containers;
	}
}

void RestoreSnapDialog::updateContainers(bool populate)
{
	if(!populate)
		return;

	disconnect(m_containerCombo, &QComboBox::currentIndexChanged, this, &RestoreSnapDialog::populateSnapView);

	if(m_containers)
	{
		for (int i = 0; i < m_containersCount; i++)
		{
			if(m_containers[i])
			{
				lxc_container_put(m_containers[i]);
				m_containers[i] = NULL;
			}
		}

		delete [] m_containers;
		m_containers = NULL;
	}

	clear();
	m_containerCombo->clear();

	m_containers = m_lxc->allContainersList();
	m_containersCount = m_lxc->lxcCountAll();


	if(m_containersCount)
	{
		m_containerCombo->addItem(tr("Select a container ..."));

		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_snapshot *snapshots = NULL;
			int snapCount = m_containers[i]->snapshot_list(m_containers[i], &snapshots);

			if(snapCount)
			{
				m_containerCombo->addItem(m_containers[i]->name, i);
				delete [] snapshots;
			}
		}
	}

	connect(m_containerCombo, &QComboBox::currentIndexChanged, this, &RestoreSnapDialog::populateSnapView);
}

void RestoreSnapDialog::showAlert(bool success, const QString &message)
{
	QString name = m_snapListView->currentIndex().data().toString();

	clearAll();

	if(success)
	{
		QString text = QString(tr("Snapshot %1 restored with success!")).arg(name);
		m_alert->success(text);
	}
	else
	{
		m_alert->danger(message);
	}
}

void RestoreSnapDialog::initObjects()
{
	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Restor a container from a snapshot"), this);
	m_containerLabel = new QLabel(tr("Containers with snapshot"), this);
	m_snapLabel = new QLabel(tr("Select a snapshot to restore"), this);
	m_newNameLabel = new QLabel(tr("New name (optional):"), this);

	QFont font;
	font.setBold(true);
	font.setPixelSize(14);

	m_alert = new Alert(this);

	m_lxc = new LxcContainer((new ConfigFile)->find("lxcpath", QString(QDir::homePath() + DEFAULT_FOLDER)).toLatin1().data(), this);
	m_containers = nullptr;
	m_containersCount = 0;

	m_containerCombo = new QComboBox(this);
	m_containerCombo->setFixedWidth(250);

	m_snapListView = new QListView(this);
	m_snapListView->setAutoScroll(true);
	m_snapListView->setDragDropMode(QAbstractItemView::NoDragDrop);
	m_snapListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_snapListView->setModel(&m_model);
	m_model.clear();

	m_newNameLienEdit = new QLineEdit(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);
	m_restore = new QPushButton(tr("Restor"), this) ;
	m_restore->setStyleSheet(m_css["primary-button"]);

	m_loading = false;
	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	updateContainers(true);
}

void RestoreSnapDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 4);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0, 1, 4);
	m_layout->addWidget(m_alert, 2, 0, 1, 4);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 4);

	m_layout->addWidget(m_containerLabel, 4, 0, 1, 2);
	m_layout->addWidget(m_snapLabel, 4, 2, 1, 2);
	m_layout->addWidget(m_containerCombo, 5, 0, 1, 2, Qt::AlignTop);
	m_layout->addWidget(m_snapListView, 5, 2, 1, 2);

	m_layout->addWidget(m_newNameLabel, 6, 0, 1, 2, Qt::AlignRight);
	m_layout->addWidget(m_newNameLienEdit, 6, 2, 1, 2);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 0, 1, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 3);

	m_layout->addWidget(m_cancel, 7, 2);
	m_layout->addWidget(m_restore, 7, 3);

	setStyleSheet(m_css["body"]);
	setFixedSize(570, 410);
	setLayout(m_layout);
}

void RestoreSnapDialog::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&RestoreSnapDialog::update));
	connect(m_restore, &QPushButton::clicked, this, &RestoreSnapDialog::restore);
	connect(m_cancel, &QPushButton::clicked, this, &RestoreSnapDialog::cancelClick);
	connect(m_lxc, &LxcContainer::containerRestrored, this, [&] (bool status, const QString &message) { showAlert(status, message); updateContainers(status); emit restored(status); });
}

void RestoreSnapDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);

	if(m_loading)
	{
		QPointF pos(m_restore->geometry().center().x(), m_restore->geometry().center().y());
		m_loader->spinner(painter, pos);
	}

	painter->end();

	QDialog::paintEvent(event);
}

void RestoreSnapDialog::closeEvent(QCloseEvent *event)
{
	if(m_loading)
	{
		event->ignore();
		return;
	}

	clearAll();
	QDialog::closeEvent(event);
}

void RestoreSnapDialog::populateSnapView()
{
	m_model.clear();

	if(!m_containerCombo->currentIndex())
		return;

	int idx = m_containerCombo->currentData().toInt();

	lxc_snapshot *snapshots = nullptr;
	int count = m_containers[idx]->snapshot_list(m_containers[idx], &snapshots);

	if(count && snapshots)
	{
		QList<QStandardItem *>items;

		for (int i = 0; i < count; i++)
		{
			QString name = QString("%1\t%2").arg(snapshots[i].name, snapshots[i].timestamp);
			items.append(new QStandardItem(QIcon(":/icons/image_black"), name));
		}

		m_model.appendColumn(items);
		delete [] snapshots;
	}
}

void RestoreSnapDialog::cancelClick()
{
	if(m_loading)
		return;

	clear();
	m_alert->clean();
	stopSpinner();
}

void RestoreSnapDialog::clear()
{
	m_model.clear();
	m_containerCombo->setCurrentIndex(0);
	m_newNameLienEdit->clear();
}

void RestoreSnapDialog::clearAll()
{
	clear();
	m_alert->clean();
	stopSpinner();
}

void RestoreSnapDialog::restore()
{
	m_alert->clean();
	int idxC = !m_containerCombo->currentIndex() ? -1 : m_containerCombo->currentData().toInt();
	int idxS = m_snapListView->currentIndex().row();

	if(idxC < 0 || idxS < 0)
	{
		m_alert->information(tr("Please select a container and snapshot!"));
		return;
	}

	QString newName = m_newNameLienEdit->text();
	QRegularExpression regex("(\\s+|[*^&%$#=!.,\\/\\\\]+)");

	if(!newName.isEmpty() && newName.contains(regex))
	{
		m_alert->information(tr("New name must not contains space or special characters *^&%$#=!.,/\\"));
		return;
	}

	startSpinner();
	m_lxc->restoreSnapshot(m_containers[idxC], idxS, newName.toLatin1().data());
}

void RestoreSnapDialog::stopSpinner()
{
	m_loading = false;
	m_loader->stop();
	m_restore->setVisible(true);
}

void RestoreSnapDialog::startSpinner()
{
	m_loading = true;
	m_loader->start();
	m_restore->setVisible(false);
}
