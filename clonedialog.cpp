#include "clonedialog.h"

CloneDialog::CloneDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnection();

	setWindowTitle(tr("Duplicate Container"));
}

CloneDialog::~CloneDialog()
{
	delete m_infoLabel;
	delete m_alertLabel;
	delete m_containerLabel;
	delete m_copyLabel;
	delete m_cloneTypeLabel;
	delete m_containersCombo;
	delete m_cloneTypeCombo;
	delete m_newContainerNameLine;
	delete m_cancel;
	delete m_create;

	delete m_layout;
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
	{
		m_alertLabel->setText(tr("Container Duplicate"));
		m_alertLabel->setStyleSheet(m_css["alert-success"]);
	}
	else
	{
		m_alertLabel->setText(tr("Duplication failed!"));
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
	}
}

void CloneDialog::initObjects()
{
	m_loading = false;
	m_timer.setInterval(1000 * 12 / 360);
	m_spinnerRotation = 0;

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Duplicate an existing container"), this);

	m_alertLabel = new QLabel(this);
	m_alertLabel->setStyleSheet(m_css["transparent"]);
	m_alertLabel->setFixedHeight(30);
	m_alertLabel->setWordWrap(true);

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
	m_layout->addWidget(m_alertLabel, 1, 0, 1, 6);

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

void CloneDialog::initConnection()
{
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(m_cancel, &QPushButton::clicked, this, &CloneDialog::cancelClick);
	connect(m_create, &QPushButton::clicked, this, &CloneDialog::clone);
}

void CloneDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	if(m_loading)
	{
		painter->save();

		painter->setPen(QPen(QBrush(QColor(95, 158, 160)), 5));

		painter->translate(m_create->geometry().center().rx(), m_create->geometry().center().ry());
		painter->rotate(m_spinnerRotation);

		painter->drawArc(-12, -12, 24, 24, 0, 270 * 16);

		if(m_spinnerRotation >= 360)
			m_spinnerRotation = 0;

		m_spinnerRotation += (360 / 12);

		painter->restore();
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
	clearAlert();

	uint idxContainer = m_containersCombo->currentIndex();
	uint idxType = m_cloneTypeCombo->currentIndex();
	QString text = m_newContainerNameLine->text().trimmed();

	if(!idxContainer || text.isEmpty() || !idxType)
	{
		m_alertLabel->setText(tr("Please Select a container or define a name"));
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		return;
	}

	if(text.contains(' '))
	{
		m_alertLabel->setText(tr("The container name must not contains space"));
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		return;
	}

	if(m_containersCombo->findText(text) > -1)
	{
		m_alertLabel->setText(tr("The container name already exists"));
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		return;
	}

	startSpinner();
	emit cloneClicked(m_containersCombo->currentData().toInt(), text, m_cloneTypeCombo->currentData().toInt());

}

void CloneDialog::cancelClick()
{
	if(!m_loading)
		clear();
}

void CloneDialog::clear()
{
	stopSpinner();
	clearAlert();

	m_newContainerNameLine->clear();
	m_containersCombo->setCurrentIndex(0);
	m_cloneTypeCombo->setCurrentIndex(0);
}

void CloneDialog::clearAlert()
{
	m_alertLabel->setStyleSheet(m_css["transparent"]);
	m_alertLabel->clear();
}

void CloneDialog::startSpinner()
{
	m_loading = true;
	m_spinnerRotation = 0;
	m_create->setVisible(false);
	m_timer.start();
}

void CloneDialog::stopSpinner()
{
	m_loading = false;
	m_spinnerRotation = 0;
	m_create->setVisible(true);
	m_timer.stop();
}
