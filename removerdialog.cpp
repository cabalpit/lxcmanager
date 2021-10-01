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
	delete m_alertLabel;
	delete m_containerCombobox;
	delete m_cancel;
	delete m_destroy;

	delete m_layout;
}

void RemoverDialog::populateCombo(const QStandardItemModel &model)
{
	m_containerCombobox->clear();
	m_containerCombobox->addItem(tr("Select Container ..."));

	for (int row = 0; row < model.rowCount(); row++)
	{
		m_containerCombobox->addItem(model.index(row, 0).data(Qt::DisplayRole).toString(), row);
	}
}

void RemoverDialog::showAlert(bool success, const QString &message)
{
	clear();
	QString css = success ? m_css["alert-success"] : m_css["alert-danger"];

	m_alertLabel->setText(message);
	m_alertLabel->setStyleSheet(css);
}

void RemoverDialog::initObjects()
{
	m_loading = false;
	m_spinnerRotation = 0;
	m_timer.setInterval(1000 * 12 / 360);

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Please select a container to destroy. Destroy a container cannot be undo."), this);
	m_infoLabel->setWordWrap(true);

	m_alertLabel = new QLabel(this);
	m_alertLabel->setWordWrap(true);
	m_alertLabel->setFixedHeight(30);
	m_alertLabel->setStyleSheet(m_css["transparent"]);

	m_containerCombobox = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_destroy = new QPushButton(tr("Destroy"), this);
	m_destroy->setStyleSheet(m_css["primary-button"]);
}

void RemoverDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 3);
	m_layout->addWidget(m_alertLabel, 1, 0, 1, 3);
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
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(m_cancel, &QPushButton::clicked, this, &RemoverDialog::cancelClick);
	connect(m_destroy, &QPushButton::clicked, this, &RemoverDialog::remove);
}

void RemoverDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	if(m_loading)
	{
		painter->save();

		painter->setPen(QPen(QBrush(QColor(95, 158, 160)), 5));

		painter->translate(m_destroy->geometry().center().rx(), m_destroy->geometry().center().ry());
		painter->rotate(m_spinnerRotation);

		QRectF pos(-12, -12, 24.0f, 24.0f);
		painter->drawArc(pos, 0, 270 * 16);

		m_spinnerRotation += (360 / 12);

		if(m_spinnerRotation >= 360)
			m_spinnerRotation = 0;

		painter->restore();
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
		m_alertLabel->setText(tr("Please make a selection first!"));
		m_alertLabel->setStyleSheet(m_css["alert-warning"]);
		return;
	}

	startSpinner();
	emit distroyClicked(m_containerCombobox->currentData().toInt());
}

void RemoverDialog::cancelClick()
{
	if(!m_loading)
		clear();
}

void RemoverDialog::clear()
{
	m_containerCombobox->setCurrentIndex(0);
	m_alertLabel->setText(QString());
	m_alertLabel->setStyleSheet(m_css["transparent"]);

	stopSpinner();
}

void RemoverDialog::startSpinner()
{
	m_loading = true;
	m_spinnerRotation = 0;
	m_destroy->setVisible(false);
	m_timer.start();
}

void RemoverDialog::stopSpinner()
{
	m_loading = false;
	m_spinnerRotation = 0;
	m_destroy->setVisible(true);
	m_timer.stop();
}

