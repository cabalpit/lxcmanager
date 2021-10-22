#include "aboutdialog.h"

using namespace businesslayer;

AboutDialog::AboutDialog(QWidget *parent): QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();

	setWindowTitle(tr("About"));
	setAutoFillBackground(true);
	setStyleSheet(m_css["about"]);
}

AboutDialog::~AboutDialog()
{
	delete m_aboutText;
	delete m_licenseText;
	delete m_logo;
	delete m_aboutButton;
	delete m_licenseButton;

	delete m_layout;
}

void AboutDialog::initObjects()
{
	m_layout = new QGridLayout(this);

	QPixmap pxlogo(":/images/logo");

	m_logo = new QLabel(this);
	m_logo->setPixmap(pxlogo);
	m_logo->setFixedSize(152, 152);
	m_logo->setStyleSheet(m_css["transparent"]);

	m_aboutButton = new QPushButton(tr("About"), this);
	m_aboutButton->setObjectName("about");

	m_licenseButton = new QPushButton(tr("License"), this);
	m_licenseButton->setObjectName("license");

	m_aboutText = new QTextBrowser(this);
	m_aboutText->setReadOnly(true);
	m_aboutText->setFrameShape(QFrame::NoFrame);
	m_aboutText->setOpenLinks(false);
	m_aboutText->setStyleSheet(m_css["transparent"]);

	QFile about(":/text/about");

	if(about.open(QIODevice::ReadOnly))
	{
		QString text = about.readAll();
		QVariant version = (ConfigFile()).find("version", "1.0");

		m_aboutText->setHtml(text.arg(version.toString()));
	}

	about.close();

	m_licenseText = new QTextBrowser(this);
	m_licenseText->setReadOnly(true);
	m_licenseText->setFrameShape(QFrame::NoFrame);
	m_licenseText->setOpenLinks(false);
	m_licenseText->setStyleSheet(m_css["transparent"]);
	m_licenseText->setVisible(false);

	QFile license(":/text/license");

	if(license.open(QIODevice::ReadOnly))
	{
		QString text= license.readAll();
		m_licenseText->setHtml(text);
		m_licenseText->setAlignment(Qt::AlignJustify);
	}

	license.close();
}

void AboutDialog::initDisposal()
{
	m_layout->addWidget(m_logo, 0, 0, 1, 2,  Qt::AlignCenter);
	m_layout->addItem(new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 0, 2);
	m_layout->addWidget(m_aboutText, 0, 3, 2, 1);
	m_layout->addWidget(m_aboutButton, 1, 0);
	m_layout->addWidget(m_licenseButton, 1, 1);

	setFixedSize(770, 325);
	setLayout(m_layout);
}

void AboutDialog::initConnections()
{
	connect(m_aboutButton, &QPushButton::clicked, this, [=](bool)
	{
		m_licenseText->setVisible(false);
		m_layout->replaceWidget(m_licenseText, m_aboutText);
		m_aboutText->setVisible(true);
	});

	connect(m_licenseButton, &QPushButton::clicked, this, [=](bool)
	{
		m_aboutText->setVisible(false);
		m_layout->replaceWidget(m_aboutText, m_licenseText);
		m_licenseText->setVisible(true);
	});

	connect(m_aboutText, &QTextBrowser::anchorClicked, this, [=](const QUrl &link) { QDesktopServices::openUrl(link); });
	connect(m_licenseText, &QTextBrowser::anchorClicked, this, [=] (const QUrl &link) { QDesktopServices::openUrl(link); });
}
