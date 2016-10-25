#ifndef UAVPOSDIALOG_H
#define UAVPOSDIALOG_H

#include <QDialog>
#include "ui_uavposloaddialog.h"

class QSettings;
class QStringList;
class QgsDelimitedTextFile;

class uavPosLoadDialog : public QDialog
{
	Q_OBJECT

public:
	uavPosLoadDialog(QWidget *parent = 0);
	~uavPosLoadDialog();

signals:
	void getFieldsList( QList< QStringList >& );

private slots:
	void on_buttonBox_accepted();

	// ѡ��POS�ļ�
	void on_btnOpenPos_clicked();

	// POS�ļ�·��lineEdit
	void on_lePosFile_textChanged();

	// �����ֶ��б�
	void updateFieldLists();

	// ���ֶ��б��ڴ�
	void writeFieldsToMemory();

private:
	// ѡ��POS�ļ�
	void getOpenFileName();

	// �ӽ����ò������������Ƿ���Ч
	bool loadDelimitedFileDefinition();

	// ����ѡ��ķָ���
	QString selectedChars();

	// ���ڴ���POS�ļ����������ԭ�ļ�
	bool writePos();

private:
	Ui::uavposdialog ui;
	QgsDelimitedTextFile *mFile;
	QSettings *mSettings;
	QList< QStringList > mFields;
};

#endif // UAVPOSDIALOG_H
