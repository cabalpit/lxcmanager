#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QStandardItemModel>
#include <QPainter>
#include "businesslayer/style.h"

class CloneDialog : public QDialog
{
		Q_OBJECT
	public:
		CloneDialog(QWidget *parent = nullptr);
		~CloneDialog();

	signals:
		void cloneClicked(const int idxContainer, const QString &newName, const int cloneType);

	public slots:
		void populateCombo(const QStandardItemModel &model);
		void alert(bool success);

	protected:
		void initObjects();
		void initDisposal();
		void initConnection();

		void paintEvent(QPaintEvent *event) override;

	protected slots:
		void clone();
		void clear();
		void clearAll();
		void clearAlert();
		void startSpinner();
		void stopSpinner();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		QLabel *m_alertLabel;
		QLabel *m_containerLabel;
		QLabel *m_copyLabel;
		QLabel *m_cloneTypeLabel;
		QComboBox *m_containersCombo;
		QComboBox *m_cloneTypeCombo;
		QLineEdit *m_newContainerNameLine;
		QPushButton *m_cancel;
		QPushButton *m_create;

		businesslayer::Style m_css;
		bool m_loader;
		QTimer m_timer;
		qreal m_spinnerRotation;

};

#endif // CLONEDIALOG_H
