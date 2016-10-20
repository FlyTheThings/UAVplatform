#include "uavmain.h"
#include "uavposloaddialog.h"
#include "uavcore.h"

#include <QSettings>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QFileInfo>
#include <QTextStream>
#include "qgsmessagelog.h"

#include "app/delimitedtext/qgsdelimitedtextfile.h"

uavPosLoadDialog::uavPosLoadDialog(QWidget *parent)
	: QDialog(parent),
	mFile( new QgsDelimitedTextFile() )
{
	ui.setupUi(this);

	mSettings = new QSettings;

	//restoreGeometry(mSettings->value( "/Uav/pos/geometry" ).toByteArray());
	
	bool blchk = mSettings->value("/Uav/pos/chkComma", false).toBool();
	ui.chkComma->setChecked(blchk);
	blchk = mSettings->value("/Uav/pos/chkTab", true).toBool();
	ui.chkTab->setChecked(blchk);
	blchk = mSettings->value("/Uav/pos/chkSpace", false).toBool();
	ui.chkSpace->setChecked(blchk);
	blchk = mSettings->value("/Uav/pos/chkColon", false).toBool();
	ui.chkColon->setChecked(blchk);
	blchk = mSettings->value("/Uav/pos/chkSemicolon", false).toBool();
	ui.chkSemicolon->setChecked(blchk);

	blchk = mSettings->value("/Uav/pos/cbxUseHeader", true).toBool();
	ui.cbxUseHeader->setChecked(blchk);
	int num = mSettings->value("/Uav/pos/rowCounter", 0).toInt();
	ui.rowCounter->setValue(num);

	blchk = mSettings->value("/Uav/pos/chkClipSpace", true).toBool();
	ui.chkClipSpace->setChecked(blchk);
	blchk = mSettings->value("/Uav/pos/chkDMSformat", false).toBool();
	ui.chkDMSformat->setChecked(blchk);

	QString str = mSettings->value("/Uav/pos/lePosFile", "").toString();
	ui.lePosFile->setText(str);

	// ���������б���
	ui.cmb_1->view()->setMinimumWidth(ui.cmb_1->view()->sizeHint().width());
	ui.cmb_2->view()->setMinimumWidth(ui.cmb_2->view()->sizeHint().width());
	ui.cmb_3->view()->setMinimumWidth(ui.cmb_3->view()->sizeHint().width());
	ui.cmb_4->view()->setMinimumWidth(ui.cmb_4->view()->sizeHint().width());
	ui.cmb_5->view()->setMinimumWidth(ui.cmb_5->view()->sizeHint().width());
	ui.cmb_6->view()->setMinimumWidth(ui.cmb_6->view()->sizeHint().width());
	ui.cmb_7->view()->setMinimumWidth(ui.cmb_7->view()->sizeHint().width());
	ui.cmb_8->view()->setMinimumWidth(ui.cmb_8->view()->sizeHint().width());
	ui.cmb_9->view()->setMinimumWidth(ui.cmb_9->view()->sizeHint().width());

	connect( ui.chkComma, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.chkTab, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.chkSpace, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.chkColon, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.chkSemicolon, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.cbxUseHeader, SIGNAL( stateChanged( int ) ), this, SLOT( updateFieldLists() ) );
	connect( ui.rowCounter, SIGNAL( valueChanged( int ) ), this, SLOT( updateFieldLists() ) );
}

uavPosLoadDialog::~uavPosLoadDialog()
{
	//mSettings->setValue( "/Uav/pos/geometry", saveGeometry() );
	delete mSettings;
	delete mFile;
}

void uavPosLoadDialog::on_btnOpenPos_clicked()
{
	getOpenFileName();
}

void uavPosLoadDialog::on_buttonBox_accepted()
{
	QSettings settings;

	mSettings->setValue("/Uav/pos/chkComma", ui.chkComma->isChecked());
	mSettings->setValue("/Uav/pos/chkTab", ui.chkTab->isChecked());
	mSettings->setValue("/Uav/pos/chkSpace", ui.chkSpace->isChecked());
	mSettings->setValue("/Uav/pos/chkColon", ui.chkColon->isChecked());
	mSettings->setValue("/Uav/pos/chkSemicolon", ui.chkSemicolon->isChecked());

	mSettings->setValue("/Uav/pos/cbxUseHeader", ui.cbxUseHeader->isChecked());
	mSettings->setValue("/Uav/pos/rowCounter", ui.rowCounter->value());

	mSettings->setValue("/Uav/pos/chkClipSpace", ui.chkClipSpace->isChecked());
	mSettings->setValue("/Uav/pos/chkDMSformat", ui.chkDMSformat->isChecked());

	mSettings->setValue("/Uav/pos/lePosFile", ui.lePosFile->text());

	mSettings->setValue("/Uav/pos/fieldsList/cmb1", ui.cmb_1->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb2", ui.cmb_2->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb3", ui.cmb_3->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb4", ui.cmb_4->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb5", ui.cmb_5->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb6", ui.cmb_6->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb7", ui.cmb_7->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb8", ui.cmb_8->currentIndex());
	mSettings->setValue("/Uav/pos/fieldsList/cmb9", ui.cmb_9->currentIndex());

	writeFieldsToMemory();
	emit getFieldsList( mFields );
}

void uavPosLoadDialog::getOpenFileName()
{
	// ��ȡ�ļ��Ĺ��̣����ӵ�ǰĿ¼���ó�ʼĿ¼�����ʹ��
	QString posFileName = QFileDialog::getOpenFileName(this, 
		"��POS�ļ�", 
		mSettings->value("/Uav/pos/pathName", QDir::homePath()).toString(), 
		"POS (*.txt *.pos *.gps)");
	if (posFileName.isEmpty())
		return;

	// ����LineEdit
	ui.lePosFile->setText(posFileName.replace(QRegExp("/"), "\\"));
}

void uavPosLoadDialog::on_lePosFile_textChanged()
{
	QString filename = ui.lePosFile->text();
	QFileInfo file_info( filename );
	if ( file_info.exists() )
	{
		QSettings settings;
		mSettings->setValue("/Uav/pos/pathName", file_info.path());
	}

	updateFieldLists();
}

void uavPosLoadDialog::updateFieldLists()
{
	// ���ֵ�ǰѡ������
	QString column1 = ui.cmb_1->currentText();
	QString column2 = ui.cmb_2->currentText();
	QString column3 = ui.cmb_3->currentText();
	QString column4 = ui.cmb_4->currentText();
	QString column5 = ui.cmb_5->currentText();
	QString column6 = ui.cmb_6->currentText();
	QString column7 = ui.cmb_7->currentText();
	QString column8 = ui.cmb_8->currentText();
	QString column9 = ui.cmb_9->currentText();

	// ����ֶ��б�
	ui.cmb_1->clear();
	ui.cmb_2->clear();
	ui.cmb_3->clear();
	ui.cmb_4->clear();
	ui.cmb_5->clear();
	ui.cmb_6->clear();
	ui.cmb_7->clear();
	ui.cmb_8->clear();
	ui.cmb_9->clear();

	if ( !loadDelimitedFileDefinition() )
		return;

	int counter = 0;
	QStringList values;
	QList<bool> isEmpty;

	QgsDelimitedTextFile::Status status = mFile->nextRecord( values );
	if ( status == QgsDelimitedTextFile::RecordEOF ) 
		return;
	if ( status != QgsDelimitedTextFile::RecordOk ) 
		return;

	// Look at count of non-blank fields

	int nv = values.size();
	while ( nv > 0 && values[nv-1].isEmpty() ) nv--;

	if ( isEmpty.size() < nv )
	{
		while ( isEmpty.size() < nv )
		{
			isEmpty.append( true );
		}
	}

	// �ֶ��б�
	QStringList fieldList = mFile->fieldNames();

	// ��ע���ֶ�
	if ( isEmpty.size() < fieldList.size() )
	{
		while ( isEmpty.size() < fieldList.size() )
		{
			isEmpty.append( true );
		}
	}

	// ���ֶ���ӵ�cmb�ؼ���
	int fieldNo = 0;
	fieldList.insert(0, "NULL");	// ���ں���
	for ( int i = 0; i < fieldList.size(); i++ )
	{
		QString field = fieldList[i];
		// �������ֶ���
		if ( field.isEmpty() ) continue;
		ui.cmb_1->addItem( field );
		ui.cmb_2->addItem( field );
		ui.cmb_3->addItem( field );
		ui.cmb_4->addItem( field );
		ui.cmb_5->addItem( field );
		ui.cmb_6->addItem( field );
		ui.cmb_7->addItem( field );
		ui.cmb_8->addItem( field );
		ui.cmb_9->addItem( field );
		fieldNo++;
	}

	// ����ʹ�õ��������������õ�ǰֵ
	ui.cmb_1->setCurrentIndex( ui.cmb_1->findText( column1 ) );
	ui.cmb_2->setCurrentIndex( ui.cmb_2->findText( column2 ) );
	ui.cmb_3->setCurrentIndex( ui.cmb_3->findText( column3 ) );
	ui.cmb_4->setCurrentIndex( ui.cmb_4->findText( column4 ) );
	ui.cmb_5->setCurrentIndex( ui.cmb_5->findText( column5 ) );
	ui.cmb_6->setCurrentIndex( ui.cmb_6->findText( column6 ) );
	ui.cmb_7->setCurrentIndex( ui.cmb_7->findText( column7 ) );
	ui.cmb_8->setCurrentIndex( ui.cmb_8->findText( column8 ) );
	ui.cmb_9->setCurrentIndex( ui.cmb_9->findText( column9 ) );

	// ʹ�ñ�������ý��յ�cmb��ֵ
	if (ui.cmb_1->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb1", -1).toInt();
		if (index > ui.cmb_1->count()) ui.cmb_1->setCurrentIndex(-1);
		else ui.cmb_1->setCurrentIndex(index);
	}
	if (ui.cmb_2->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb2", -1).toInt();
		if (index > ui.cmb_2->count()) ui.cmb_2->setCurrentIndex(-1);
		else ui.cmb_2->setCurrentIndex(index);
	}
	if (ui.cmb_3->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb3", -1).toInt();
		if (index > ui.cmb_3->count()) ui.cmb_3->setCurrentIndex(-1);
		else ui.cmb_3->setCurrentIndex(index);
	}
	if (ui.cmb_4->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb4", -1).toInt();
		if (index > ui.cmb_4->count()) ui.cmb_4->setCurrentIndex(-1);
		else ui.cmb_4->setCurrentIndex(index);
	}
	if (ui.cmb_5->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb5", -1).toInt();
		if (index > ui.cmb_5->count()) ui.cmb_5->setCurrentIndex(-1);
		else ui.cmb_5->setCurrentIndex(index);
	}
	if (ui.cmb_6->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb6", -1).toInt();
		if (index > ui.cmb_6->count()) ui.cmb_6->setCurrentIndex(-1);
		else ui.cmb_6->setCurrentIndex(index);
	}
	if (ui.cmb_7->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb7", -1).toInt();
		if (index > ui.cmb_7->count()) ui.cmb_7->setCurrentIndex(-1);
		else ui.cmb_7->setCurrentIndex(index);
	}
	if (ui.cmb_8->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb8", -1).toInt();
		if (index > ui.cmb_8->count()) ui.cmb_8->setCurrentIndex(-1);
		else ui.cmb_8->setCurrentIndex(index);
	}
	if (ui.cmb_9->currentIndex() == -1)
	{
		int index = mSettings->value("/Uav/pos/fieldsList/cmb9", -1).toInt();
		if (index > ui.cmb_9->count()) ui.cmb_9->setCurrentIndex(-1);
		else ui.cmb_9->setCurrentIndex(index);
	}
}

bool uavPosLoadDialog::loadDelimitedFileDefinition()
{
	mFile->setFileName( ui.lePosFile->text() );

	mFile->setTypeCSV( selectedChars() );

	mFile->setSkipLines( ui.rowCounter->value() );
	mFile->setUseHeader( !ui.cbxUseHeader->isChecked() );
	mFile->setDiscardEmptyFields( ui.cbxSkipEmptyFields->isChecked() );
	mFile->setTrimFields( ui.chkClipSpace->isChecked() );
	return mFile->isValid();
}

QString uavPosLoadDialog::selectedChars()
{
	QString chars = "";
	if ( ui.chkComma->isChecked() )
		chars.append( ',' );
	if ( ui.chkSpace->isChecked() )
		chars.append( ' ' );
	if ( ui.chkTab->isChecked() )
		chars.append( '\t' );
	if ( ui.chkSemicolon->isChecked() )
		chars.append( ';' );
	if ( ui.chkColon->isChecked() )
		chars.append( ':' );
	chars = QgsDelimitedTextFile::encodeChars( chars );
	return chars;
}

void uavPosLoadDialog::writeFieldsToMemory()
{
	int icount = 0;
	mFields.clear();	// ���֮ǰ���������

	if (ui.cmb_1->currentIndex() >= 0 && ui.cmb_1->currentText() != "NULL")
		++icount;
	if (ui.cmb_2->currentIndex() >= 0 && ui.cmb_2->currentText() != "NULL")
		++icount;
	if (ui.cmb_3->currentIndex() >= 0 && ui.cmb_3->currentText() != "NULL")
		++icount;
	if (ui.cmb_4->currentIndex() >= 0 && ui.cmb_4->currentText() != "NULL")
		++icount;
	if (ui.cmb_5->currentIndex() >= 0 && ui.cmb_5->currentText() != "NULL")
		++icount;
	if (ui.cmb_6->currentIndex() >= 0 && ui.cmb_6->currentText() != "NULL")
		++icount;
	if (ui.cmb_7->currentIndex() >= 0 && ui.cmb_7->currentText() != "NULL")
		++icount;
	if (ui.cmb_8->currentIndex() >= 0 && ui.cmb_8->currentText() != "NULL")
		++icount;
	if (ui.cmb_9->currentIndex() >= 0 && ui.cmb_9->currentText() != "NULL")
		++icount;

	QStringList values;
	mFile->reset();

	QgsDelimitedTextFile::Status status = mFile->nextRecord( values );

	while (status != QgsDelimitedTextFile::RecordEOF) // �Ƿ��ѵ��ļ�β��
	{
		if ( status == QgsDelimitedTextFile::RecordOk ) // �Ƿ����Ҫ��
		{
			if (values.size() >= icount)
			{
				mFields.append(values);
			}
			else
			{
				QgsMessageLog::logMessage(QString("��ȡ�ع������ : ��%1���ֶ������������Ѻ���.").arg(mFile->recordId()));
			}
		}
		else
		{
			QgsMessageLog::logMessage(QString("��ȡ�ع������ : ��%1��Ϊ����¼���Ѻ���.").arg(mFile->recordId()));
		}

		status = mFile->nextRecord( values );
	}

}

bool uavPosLoadDialog::writePos()
{
	if (mFields.isEmpty())
	{
		return false;
	}

	QFile file(ui.lePosFile->text());
	if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))   //ֻд���ı�����д
	{
		UavMain::instance()->messageBar()->pushMessage( "�ع���ļ���д", "����д���ع���ļ�ʧ��...", 
									QgsMessageBar::WARNING, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage("�ع���ļ���д : ����д���ع���ļ�ʧ��.");
		return false;
	}

	QTextStream out(&file);
	foreach (QStringList strList, mFields)
	{
		QString strLine;
		foreach (QString str, strList)
			strLine.append(str + '\t');
		out << strLine + '\n';
	}

	file.close();
	return true;
}
