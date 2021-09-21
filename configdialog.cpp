#include "configdialog.h"

using namespace businesslayer;

/**
 * @brief ConfigDialog::ConfigDialog							[public]
 *
 * Constructs a ConfigDialog object, and initialize the widget with default disposal, config, and connect.
 *
 * @param parent waits parent widget, default nullptr
 */
ConfigDialog::ConfigDialog(QWidget *parent): QDialog(parent)
{
	initConfig();
	initDisposale();
	initConnect();

	setAutoFillBackground(true);
	setWindowTitle(tr("LXC Configuration"));
}

/**
 * @brief ConfigDialog::~ConfigDialog
 *
 * Destructor delete all object included in this class.
 */
ConfigDialog::~ConfigDialog()
{
	delete m_alertLabel;
	delete m_lxcFolderLabel;
	delete m_hkpLabel;
	delete m_lxcAutoStartLabel;
	delete m_hkpLineEdit;
	delete m_lxcFolderLineEdit;
	delete m_lxcAutoStartCheckbox;

	delete m_save;
	delete m_close;
	delete m_reset;

	delete m_layout;

	delete m_configFile;
}

/**
 * @brief ConfigDialog::initDisposale						[protected]
 *
 * This method initializes the ui disposition of the objects of this class.
 */
void ConfigDialog::initDisposale()
{
	m_layout = new QGridLayout(this);

	QFont bold("lato-bold");
	bold.setBold(true);

	m_alertLabel = new QLabel(this);
	m_alertLabel->setFont(bold);
	m_alertLabel->setFixedHeight(40);
	m_alertLabel->setAlignment(Qt::AlignCenter);


	m_lxcFolderLabel = new QLabel(this);
	m_lxcFolderLabel->setText(tr("LXC folder path:"));

	m_hkpLabel = new QLabel(this);
	m_hkpLabel->setText(tr("Keyserver url"));

	m_lxcAutoStartLabel = new QLabel(this);
	m_lxcAutoStartLabel->setText(tr("Autostart containers: "));

	m_lxcFolderLineEdit = new QLineEdit(this);
	m_lxcFolderLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_lxcFolderLineEdit->setText(m_configFile->find("lxcPath"));

	m_hkpLineEdit = new QLineEdit(this);
	m_hkpLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_hkpLineEdit->setText(m_configFile->find("hkp"));

	QString autostart = m_configFile->find("autostart");

	m_lxcAutoStartCheckbox = new QCheckBox(this);
	m_lxcAutoStartCheckbox->setChecked((autostart.isEmpty() || autostart == "0") ? false : true);


	m_save = new QPushButton(tr("Save"), this);
	m_save->setStyleSheet(m_css["primary-button"]);
	m_save->setAutoFillBackground(true);

	m_close = new QPushButton(tr("Close"), this);
	m_close->setStyleSheet(m_css["default-button"]);
	m_close->setAutoFillBackground(true);

	m_reset = new QPushButton(this);
	m_reset->setIcon(QIcon(":/icons/reset_black"));
	m_reset->setIconSize(QSize(21, 21));
	m_reset->setStyleSheet(m_css["default-rounded-button"]);
	m_reset->setAutoFillBackground(true);
	m_reset->setFixedSize(31, 31);

	m_layout->addWidget(m_reset, 0, 3, Qt::AlignRight);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 3);


	m_layout->addWidget(m_alertLabel, 2, 0, 2, 4);


	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 3);

	m_layout->addWidget(m_lxcFolderLabel, 4, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcFolderLineEdit, 4, 1, 1, 3);

	m_layout->addWidget(m_hkpLabel, 5, 0, Qt::AlignRight);
	m_layout->addWidget(m_hkpLineEdit, 5, 1, 1, 3);

	m_layout->addWidget(m_lxcAutoStartLabel, 6, 0, Qt::AlignRight);
	m_layout->addWidget(m_lxcAutoStartCheckbox, 6, 1, 1, 3, Qt::AlignLeft);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 3);

	m_layout->addWidget(m_close, 8, 2);
	m_layout->addWidget(m_save, 8, 3);

	setLayout(m_layout);
	setFixedSize(550, 300);
	setStyleSheet(m_css["main"]);
}

/**
 * @brief ConfigDialog::initConnect				[protected]
 *
 * This method connect the objects between them or with the slot of this class.
 */
void ConfigDialog::initConnect()
{
	connect(m_save, &QPushButton::clicked, this, &ConfigDialog::save);
	connect(m_close, &QPushButton::clicked, this, &ConfigDialog::close);
	connect(m_reset, &QPushButton::clicked, this, &ConfigDialog::reset);
}

/**
 * @brief ConfigDialog::initConfig				[protected]
 *
 * This method instantiates configFile object of the class ConfigFile.
 *
 * @return true if the configFile object can open the file otherwize false.
 */
bool ConfigDialog::initConfig()
{
	m_configFile = new ConfigFile;
	return m_configFile->isConfigFileOpen();
}

/**
 * @brief ConfigDialog::reset				[protected]
 *
 * This method reset the config file.
 */
void ConfigDialog::reset()
{
	m_lxcFolderLineEdit->setText(QDir::homePath() + "/.local/share/lxc/");
	m_hkpLineEdit->setText("hkp://keyserver.ubuntu.com");
	m_lxcAutoStartCheckbox->setChecked(false);

	save(true);
}

/**
 * @brief ConfigDialog::closeEvent					[protected]
 *
 * Override close event.
 *
 * @param event @see QCloseEvent
 */
void ConfigDialog::closeEvent(QCloseEvent *event)
{
	m_alertLabel->setText("");
	m_alertLabel->setStyleSheet(m_css["transparent"]);

	QDialog::closeEvent(event);
}

/**
 * @brief ConfigDialog::save
 *
 * This method will save to config file the information filled by the user.
 */
void ConfigDialog::save(bool)
{
	QMap<QString, QString> map;
	map.insert("lxcPath", m_lxcFolderLineEdit->text());
	map.insert("hkp", m_hkpLineEdit->text());
	map.insert("autostart", !m_lxcAutoStartCheckbox->isChecked() ? "0" : "1");

	if(m_configFile->save(map))
	{
		m_alertLabel->setStyleSheet("background-color: #d1e7dd; color: #145536;");
		m_alertLabel->setText(tr("Configuration Saved!"));

		emit savedConfig();
	}
	else
	{
		m_alertLabel->setStyleSheet("background-color: #f8d7da; color: #87252d;");
		m_alertLabel->setText(tr("Configuration not Saved please try later!"));
	}
}
