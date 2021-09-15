#include "configdialog.h"

ConfigDialog::ConfigDialog()
{
	initDisposale();
	initConnect();
	initConfig();
}

ConfigDialog::~ConfigDialog()
{
	delete m_titleLabel;
	delete m_lxcFolderLabel;

	delete m_lxcFolderLineEdit;

	delete m_save;
	delete m_cancel;

	delete m_layout;

	delete m_configFile;
}

void ConfigDialog::initDisposale()
{
	m_layout = new QGridLayout(this);

	QFont titleFont("lato-bold");
	titleFont.setBold(true);
	titleFont.setWeight(QFont::Bold);
	titleFont.setPointSize(16);

	m_titleLabel = new QLabel(this);
	m_titleLabel->setText(tr("LXC Configuration"));
	m_titleLabel->setFont(titleFont);

	m_lxcFolderLabel = new QLabel(this);
	m_lxcFolderLabel->setText(tr("LXC Folder containers path"));

	m_lxcFolderLineEdit = new QLineEdit(this);

	m_save = new QPushButton(tr("Save"), this);

	m_cancel = new QPushButton(tr("Close"), this);

	m_layout->addWidget(m_titleLabel, 0, 0, 1, 2, Qt::AlignCenter);
	m_layout->addWidget(m_lxcFolderLabel, 1, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcFolderLineEdit, 1, 1, Qt::AlignLeft);
	m_layout->addWidget(m_cancel, 2, 0);
	m_layout->addWidget(m_save, 2, 1);

	setLayout(m_layout);
	setFixedSize(550, 300);
	setStyleSheet("background-color: white; color: black;");
}

void ConfigDialog::initConnect()
{
	connect(m_save, &QPushButton::clicked, this, &ConfigDialog::save);
	connect(m_cancel, &QPushButton::clicked, this, &ConfigDialog::cancel);
}

void ConfigDialog::initConfig()
{
	QString lxcPath = QDir::homePath() + "/.local/share/lxc/";
	m_configFile = new ConfigFile;


	if(m_configFile->isConfigFileOpen())
		lxcPath = m_configFile->find("lxcPath");

	m_lxcFolderLineEdit->setText(lxcPath);
}

void ConfigDialog::save(bool)
{
	QMap<QString, QString> map;
	map.insert("lxcPath", m_lxcFolderLineEdit->text());

	m_configFile->save(map);
}

void ConfigDialog::cancel(bool)
{
	this->close();
}
