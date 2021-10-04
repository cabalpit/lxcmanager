#include "clonedialog.h"

CloneDialog::CloneDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();

	setWindowTitle(tr("Duplicate Container"));
}

CloneDialog::~CloneDialog()
{
	delete m_infoLabel;
	delete m_alert;
	delete m_containerLabel;
	delete m_copyLabel;
	delete m_cloneTypeLabel;
	delete m_containersCombo;
	delete m_cloneTypeCombo;
	delete m_newContainerNameLine;
	delete m_cancel;
	delete m_create;

	delete m_layout;
	delete m_loader;
}

void CloneDialog::populateCombo(const QStandardItemModel &model)
{
	m_containersCombo->clear();
	m_containersCombo->addItem(tr("Select container ..."));

	for (int row = 0; row < model.rowCount(); row++)
	{
		m_containersCombo->addItem(model.index(row, 0).data().toString(), row);
	}
}

void CloneDialog::showAlert(bool success)
{
	clear();

	if(success)
		m_alert->success(tr("Container duplicated"));

	else
		m_alert->danger(tr("Duplication failed to create!"));
}

void CloneDialog::initObjects()
{
	m_loading = false;
	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Duplicate an existing container"), this);

	m_alert = new Alert(this);
	m_containerLabel = new QLabel(tr("Containers:"), this);
	m_copyLabel = new QLabel(tr("New Container name:"), this);
	m_cloneTypeLabel = new QLabel(tr("Clone type:"), this);

	m_containersCombo = new QComboBox(this);

	m_cloneTypeCombo = new QComboBox(this);
	m_cloneTypeCombo->addItem(tr("Select clone type ..."));
	m_cloneTypeCombo->addItem(tr("Copy container"), 0);
	m_cloneTypeCombo->addItem(tr("Clone Snapshot"), 6);

	m_newContainerNameLine = new QLineEdit(this);
	m_newContainerNameLine->setPlaceholderText(tr("Container Name"));

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_create = new QPushButton(tr("Create"), this);
	m_create->setStyleSheet(m_css["primary-button"]);
}

void CloneDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 6);
	m_layout->addWidget(m_alert, 1, 0, 1, 6);

	m_layout->addWidget(m_containerLabel, 2, 0, 1, 2);
	m_layout->addWidget(m_copyLabel, 2, 2, 1, 2);
	m_layout->addWidget(m_cloneTypeLabel, 2, 4, 1, 2);

	m_layout->addWidget(m_containersCombo, 3, 0, 1, 2);
	m_layout->addWidget(m_newContainerNameLine, 3, 2, 1, 2);
	m_layout->addWidget(m_cloneTypeCombo, 3, 4, 1, 2);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 4, 0, 1, 4);
	m_layout->addWidget(m_cancel, 4, 4);
	m_layout->addWidget(m_create, 4, 5);

	setStyleSheet(m_css["main"]);
	setFixedSize(QSize(550, 200));
	setLayout(m_layout);
}

void CloneDialog::initConnections()
{
	connect(m_cancel, &QPushButton::clicked, this, &CloneDialog::cancelClick);
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&CloneDialog::update));
	connect(m_create, &QPushButton::clicked, this, &CloneDialog::clone);
}

void CloneDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	if(m_loading)
	{
		QPointF pos(m_create->geometry().center().rx(), m_create->geometry().center().ry());
		m_loader->spinner(painter, pos);
	}

	painter->end();

	QDialog::paintEvent(event);
}

void CloneDialog::closeEvent(QCloseEvent *event)
{
	if(m_loading)
	{
		event->ignore();
		return;
	}

	clear();
	QDialog::closeEvent(event);

}

void CloneDialog::clone()
{
	m_alert->clean();

	uint idxContainer = m_containersCombo->currentIndex();
	uint idxType = m_cloneTypeCombo->currentIndex();
	QString text = m_newContainerNameLine->text().trimmed();

	if(!idxContainer || text.isEmpty() || !idxType)
	{
		m_alert->danger(tr("Please Select a container or define a name"));
		return;
	}

	if(text.contains(' '))
	{
		m_alert->danger(tr("The container name must not contains space"));
		return;
	}

	if(m_containersCombo->findText(text) > -1)
	{
		m_alert->danger(tr("The container name already exists"));
		return;
	}

	startLoader();
	emit cloneClicked(m_containersCombo->currentData().toInt(), text, m_cloneTypeCombo->currentData().toInt());

}

void CloneDialog::cancelClick()
{
	if(!m_loading)
		clear();
}

void CloneDialog::clear()
{
	stopLoader();

	m_alert->clean();
	m_newContainerNameLine->clear();
	m_containersCombo->setCurrentIndex(0);
	m_cloneTypeCombo->setCurrentIndex(0);
}

void CloneDialog::startLoader()
{
	m_loading = true;
	m_loader->start();
	m_create->setVisible(false);
}

void CloneDialog::stopLoader()
{
	m_loading = false;
	m_loader->stop();
	m_create->setVisible(true);
}
