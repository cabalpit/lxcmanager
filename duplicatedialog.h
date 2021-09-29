#ifndef DUPLICATEDIALOG_H
#define DUPLICATEDIALOG_H

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

class DuplicateDialog : public QDialog
{
		Q_OBJECT
	public:
		DuplicateDialog(QWidget *parent = nullptr);
		~DuplicateDialog();

	signals:
		void createClicked(const int idxContainer, const QString &newContainerName);

	public slots:
		void populateCombo(const QStandardItemModel &model);
		void message(bool success);

	protected:
		void initObjects();
		void initDisposal();
		void initConnection();

		void paintEvent(QPaintEvent *event) override;

	protected slots:
		void create();
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
		QComboBox *m_containersCombo;
		QLineEdit *m_newContainerNameLine;
		QPushButton *m_cancel;
		QPushButton *m_create;

		businesslayer::Style m_css;
		bool m_loader;
		QTimer m_timer;
		qreal m_spinnerRotation;

};

#endif // DUPLICATEDIALOG_H
