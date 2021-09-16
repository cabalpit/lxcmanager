#include "configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent): QDialog(parent)
{
	initConfig();
	initDisposale();
	initConnect();

	setAutoFillBackground(true);
	setWindowTitle(tr("LXC Configuration"));
}

ConfigDialog::~ConfigDialog()
{
	delete m_informationLabel;
	delete m_lxcFolderLabel;
	delete m_lxcAutoStartLabel;

	delete m_lxcFolderLineEdit;
	delete m_lxcAutoStartCheckbox;

	delete m_save;
	delete m_close;

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

	QFont bold("lato-bold");

	m_informationLabel = new QLabel(this);
	m_informationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_informationLabel->setFont(bold);

	m_lxcFolderLabel = new QLabel(this);
	m_lxcFolderLabel->setText(tr("LXC folder path:"));

	m_lxcAutoStartLabel = new QLabel(this);
	m_lxcAutoStartLabel->setText(tr("Autostart containers: "));

	QString lxcPath = QDir::homePath() + "/.local/share/lxc/";

	if(m_configFile->isConfigFileOpen() && !m_configFile->find("lxcPath").isEmpty())
		lxcPath = m_configFile->find("lxcPath");

	m_lxcFolderLineEdit = new QLineEdit(this);
	m_lxcFolderLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_lxcFolderLineEdit->setText(lxcPath);

	QString autostart = m_configFile->find("autostart");

	m_lxcAutoStartCheckbox = new QCheckBox(this);
	m_lxcAutoStartCheckbox->setChecked((autostart.isEmpty() || autostart == "0") ? false : true);


	m_save = new QPushButton(tr("Save"), this);
	m_save->setStyleSheet("background-color: rgb(53, 132, 228); \
						  selection-background-color: rgb(26, 95, 180); \
			alternate-background-color: rgb(28, 113, 216); \
color: rgb(255, 255, 255); \
	border-radius: 0; \
padding:0.25em;");


	m_close = new QPushButton(tr("Close"), this);
	m_close->setStyleSheet("background-color: rgb(239, 239, 239); \
						   alternate-background-color: rgb(222, 221, 218); \
			selection-color: rgb(192, 191, 188); \
	border-radius: 0; padding:0.25em;");



	m_layout->addWidget(m_informationLabel, 0,0,2,4, Qt::AlignCenter);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 3);

	m_layout->addWidget(m_lxcFolderLabel, 3, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcFolderLineEdit, 3, 1, 1, 3);

	m_layout->addWidget(m_lxcAutoStartLabel, 4, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcAutoStartCheckbox, 4, 1, 1, 3, Qt::AlignLeft);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 3);

	m_layout->addWidget(m_close, 6, 2);
	m_layout->addWidget(m_save, 6, 3);

	setLayout(m_layout);
	setFixedSize(550, 300);
	setStyleSheet("background-color: white; color: black;");
}

void ConfigDialog::initConnect()
{
	connect(m_save, &QPushButton::clicked, this, &ConfigDialog::save);
	connect(m_close, &QPushButton::clicked, this, &ConfigDialog::close);
}

bool ConfigDialog::initConfig()
{
	m_configFile = new ConfigFile;
	return m_configFile->isConfigFileOpen();
}

void ConfigDialog::save(bool)
{
	QMap<QString, QString> map;
	map.insert("lxcPath", m_lxcFolderLineEdit->text());
	map.insert("autostart", !m_lxcAutoStartCheckbox->isChecked() ? "0" : "1");

	if(m_configFile->save(map))
	{
		m_informationLabel->setText(tr("Configuration Saved!"));
		m_informationLabel->setStyleSheet("background-color: #d1e7dd; color: #145536;");
		emit savedConfig();
	}
	else
	{
		m_informationLabel->setText(tr("Configuration not Saved please try later!"));
		m_informationLabel->setStyleSheet("background-color: #f8d7da; color: #87252d;");
	}
}
