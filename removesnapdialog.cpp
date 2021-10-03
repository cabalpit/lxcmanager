#include "removesnapdialog.h"

using namespace businesslayer;

RemoveSnapDialog::RemoveSnapDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

RemoveSnapDialog::~RemoveSnapDialog()
{
	delete m_infoLabel;
	delete m_alert;
	delete m_containerLabel;
	delete m_snapshotLabel;

	delete m_containerCombo;
	delete m_snapshotView;

	delete m_cancel;
	delete m_remove;

	delete m_layout;

	if(m_containers)
	{
		for(int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = 0;
		}

		delete [] m_containers;
	}
}

void RemoveSnapDialog::updateContainers()
{
	if(m_containers)
	{
		for(int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = 0;
		}

		delete [] m_containers;
	}


	LxcContainer *lxc = new LxcContainer(m_config.find("lxcpath", QDir::homePath() + "/.local/share/lxc").toLatin1().data());
	m_containersCount = lxc->lxcCountAll();
	m_containers = lxc->allContainersList();


	if(m_containers)
	{
		m_containerCombo->addItem(tr("Select container ..."));

		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_snapshot *snapshot = nullptr;
			int snapCount = m_containers[i]->snapshot_list(m_containers[i], &snapshot);

			if(snapCount)
				m_containerCombo->addItem(m_containers[i]->name, i);


			delete [] snapshot;
		}
	}

	delete lxc;
}

void RemoveSnapDialog::showAlert(bool success, const QString &message)
{
	clear();

	QString css = success ? m_css["alert-success"] : m_css["alert-danger"];

	m_alert->setText(message);
	m_alert->setStyleSheet(css);
}

void RemoveSnapDialog::removeSnap()
{
	int idxC = !m_containerCombo->currentIndex() ? -1 : m_containerCombo->currentData().toInt();
	int idxS = m_snapshotView->currentIndex().row();

	m_alert->clean();

	if(idxC < 0 || idxS < 0)
	{
		m_alert->setText(tr("Please make a selection container and snapshot"));
		m_alert->setStyleSheet(m_css["alert-danger"]);
		return;
	}

	startLoader();
	emit snapRemoved(idxC, idxS);
}

void RemoveSnapDialog::initObjects()
{
	m_containers = nullptr;
	m_containersCount = 0;

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Remove Snapshost cannot be undo!"), this);

	QFont font("Lato");
	font.setBold(true);
	font.setPixelSize(14);

	m_alert = new Alert(this);
	m_alert->setFont(font);
	m_alert->setFixedHeight(50);
	m_alert->setStyleSheet(m_css["transparent"]);

	m_containerLabel = new QLabel(tr("Containers:"), this);
	m_snapshotLabel = new QLabel(tr("Snapshots list:"), this);

	m_containerCombo = new QComboBox(this);
	m_containerCombo->setFixedWidth(250);

	m_snapshotView = new QListView(this);
	m_snapshotView->setModel(&m_model);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_remove = new QPushButton(tr("Remove"), this);
	m_remove->setStyleSheet(m_css["primary-button"]);


	m_timer.setInterval(1000 * 12 / 360);
	m_spinnerRotate = 0;
	m_loading = false;
}

void RemoveSnapDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 4);
	m_layout->addWidget(m_alert, 1, 0, 1, 4);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 2, 0, 1, 4);

	m_layout->addWidget(m_containerLabel, 3, 0, 1, 2);
	m_layout->addWidget(m_snapshotLabel, 3, 2, 1, 2);

	m_layout->addWidget(m_containerCombo, 4, 0, 1, 2);
	m_layout->addWidget(m_snapshotView, 4, 2, 1, 2);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 5, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 5, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 5, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 5, 3);

	m_layout->addWidget(m_cancel, 6, 2);
	m_layout->addWidget(m_remove, 6, 3);

	setWindowTitle(tr("Remove Snapshots"));
	setFixedSize(550, 395);
	setStyleSheet(m_css["main"]);
	setLayout(m_layout);
}

void RemoveSnapDialog::initConnections()
{
	connect(&m_timer, &QTimer::timeout, this, QOverload<>::of(&RemoveSnapDialog::update));
	connect(m_cancel, &QPushButton::clicked, this, &RemoveSnapDialog::cancelClick);
	connect(m_remove, &QPushButton::clicked, this, &RemoveSnapDialog::removeSnap);
	connect(m_containerCombo, &QComboBox::currentIndexChanged, this, &RemoveSnapDialog::populateSnapsView);
}

void RemoveSnapDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHints(QPainter::Antialiasing);

	if(m_loading)
	{
		painter->save();

		painter->setPen(QPen(QBrush(QColor(95, 158, 160)), 5));

		painter->translate(m_remove->geometry().center().rx(), m_remove->geometry().center().ry());
		painter->rotate(m_spinnerRotate);

		QRectF pos(-12.0f, -12.0f, 24.0f, 24.0f);
		painter->drawArc(pos, 0, 270 * 16);

		m_spinnerRotate += (360 / 12);

		if(m_spinnerRotate >= 360)
			m_spinnerRotate = 0;

		painter->restore();
	}

	painter->end();

	QDialog::paintEvent(event);
}

void RemoveSnapDialog::closeEvent(QCloseEvent *event)
{
	if(m_loading)
	{
		event->ignore();
		return;
	}

	clear();
	QDialog::closeEvent(event);
}

void RemoveSnapDialog::populateSnapsView()
{
	m_model.clear();

	if(!m_containerCombo->currentIndex())
		return;

	int idx = m_containerCombo->currentData().toInt();
	lxc_snapshot *snapshot = nullptr;

	int snapCount = m_containers[idx]->snapshot_list(m_containers[idx], &snapshot);

	QList<QStandardItem *> items;

	for (int i = 0; i < snapCount; i++)
	{
		QString name = QString("%1\t%2").arg(snapshot[i].name, snapshot[i].timestamp);
		items.append(new QStandardItem(QIcon(":/icons/image_black"), name));
	}

	delete [] snapshot;

	m_model.appendColumn(items);
}

void RemoveSnapDialog::cancelClick()
{
	if(m_loading)
		return;

	clear();
}

void RemoveSnapDialog::clear()
{
	m_containerCombo->setCurrentIndex(0);
	m_model.clear();

	m_alert->clean();
	stopLoader();
}

void RemoveSnapDialog::stopLoader()
{
	m_loading = false;
	m_spinnerRotate = 0;
	m_remove->setVisible(true);
	m_timer.stop();
}

void RemoveSnapDialog::startLoader()
{
	m_loading = true;
	m_spinnerRotate = 0;
	m_remove->setVisible(false);
	m_timer.start();
}
