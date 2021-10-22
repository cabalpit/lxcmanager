#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QDesktopServices>

#include "businesslayer/style.h"
#include "businesslayer/configfile.h"

class AboutDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit AboutDialog(QWidget *parent);
		~AboutDialog();

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

	protected slots:

	private:
		QGridLayout *m_layout;
		QLabel *m_logo;
		QTextBrowser *m_aboutText;
		QTextBrowser *m_licenseText;
		QPushButton *m_aboutButton;
		QPushButton *m_licenseButton;

		businesslayer::Style m_css;
};

#endif // ABOUTDIALOG_H
