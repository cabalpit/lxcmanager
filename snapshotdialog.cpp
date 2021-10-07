#include "snapshotdialog.h"

SnapshotDialog::SnapshotDialog(SnapType type, QWidget *parent): QDialog(parent)
{
	m_type = type;
}
