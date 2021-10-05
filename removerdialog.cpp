#include "removerdialog.h"

using namespace businesslayer;

RemoverDialog::RemoverDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();

	setWindowTitle(tr("Destroy container"));
}

RemoverDialog::~RemoverDialog()
{
	delete m_infoLabel;
	delete m_alert;
	delete m_containerCombobox;
	delete m_cancel;
	delete m_destroy;

	delete m_layout;
	delete m_loader;

	delete m_lxc;

	if(m_containers)
	{
		for(int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}
}

void RemoverDialog::updateContainers(bool populate)
{
	if(!populate)
		return;

	m_containerCombobox->clear();

	if(m_containers)
	{
		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}

	m_containers = m_lxc->allContainersList();
	m_containersCount = m_lxc->lxcCountAll();

	if(m_containers)
	{
		m_containerCombobox->addItem(tr("Select Container ..."));

		for (int i = 0; i < m_containersCount; i++)
			m_containerCombobox->addItem(m_containers[i]->name);
	}
}

void RemoverDialog::showAlert(bool success)
{
	clear();

	if(success)
		m_alert->success(tr(""));

	else
		m_alert->danger(tr(""));
}

void RemoverDialog::initObjects()
{
	m_lxc = new LxcContainer((new ConfigFile)->find("lxcpath", QDir::homePath() + DEFAULT_FOLDER).toLatin1().data(), this);
	m_containers = nullptr;
	m_containersCount = 0;

	m_loading = false;
	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Please select a container to destroy. Destroy a container cannot be undo."), this);
	m_infoLabel->setWordWrap(true);

	m_alert = new Alert(this);

	m_containerCombobox = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_destroy = new QPushButton(tr("Destroy"), this);
	m_destroy->setStyleSheet(m_css["primary-button"]);

	updateContainers(true);
}

void RemoverDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 3);
	m_layout->addWidget(m_alert, 1, 0, 1, 3);
	m_layout->addWidget(m_containerCombobox, 2, 0, 1, 3);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 3, 0);

	m_layout->addWidget(m_cancel, 3, 1);
	m_layout->addWidget(m_destroy, 3, 2);

	setFixedSize(QSize(360, 180));
	setStyleSheet(m_css["main"]);
	setLayout(m_layout);
}

void RemoverDialog::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&RemoverDialog::update));
	connect(m_cancel, &QPushButton::clicked, this, &RemoverDialog::cancelClick);
	connect(m_destroy, &QPushButton::clicked, this, &RemoverDialog::remove);
	connect(m_lxc, &LxcContainer::containerDestroyed, this, [&](bool status) {showAlert(status); updateContainers(status); emit containerDestroyed(status); });
}

void RemoverDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	if(m_loading)
	{
		QPointF pos(m_destroy->geometry().center().rx(), m_destroy->geometry().center().ry());
		m_loader->spinner(painter, pos);
	}

	painter->end();

	QDialog::paintEvent(event);
}

void RemoverDialog::closeEvent(QCloseEvent *event)
{
	if(m_loading)
	{
		event->ignore();
		return;
	}

	clear();
	QDialog::closeEvent(event);
}

void RemoverDialog::remove()
{
	if(!m_containerCombobox->currentIndex())
	{
		m_alert->information(tr("Please make a selection first!"));
		return;
	}

	startLoader();

	m_lxc->destroy(m_containers[m_containerCombobox->currentIndex() - 1]);
}

void RemoverDialog::cancelClick()
{
	if(!m_loading)
		clear();
}

void RemoverDialog::clear()
{
	m_containerCombobox->setCurrentIndex(0);
	m_alert->clean();

	stopLoader();
}

void RemoverDialog::startLoader()
{
	m_loading = true;
	m_loader->start();
	m_destroy->setVisible(false);
}

void RemoverDialog::stopLoader()
{
	m_loading = false;
	m_loader->stop();
	m_destroy->setVisible(true);
}

