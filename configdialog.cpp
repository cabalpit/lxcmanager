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
	delete m_infoLabel;
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
	bold.setBold(true);

	m_infoLabel = new QLabel(this);
	m_infoLabel->setFont(bold);
	m_infoLabel->setFixedHeight(40);
	m_infoLabel->setAlignment(Qt::AlignCenter);


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
	m_save->setStyleSheet(m_css("primary-button"));

	m_close = new QPushButton(tr("Close"), this);
	m_close->setStyleSheet(m_css("default-button"));

	m_layout->addWidget(m_infoLabel, 0, 0, 2, 4);

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
		m_infoLabel->setStyleSheet("background-color: #d1e7dd; color: #145536;");
		m_infoLabel->setText(tr("Configuration Saved!"));

		emit savedConfig();
	}
	else
	{
		m_infoLabel->setStyleSheet("background-color: #f8d7da; color: #87252d;");
		m_infoLabel->setText(tr("Configuration not Saved please try later!"));
	}
}
