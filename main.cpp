#include "uav/uavmain.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QSettings>
#include <QTranslator>

#include "qgsapplication.h"	
#include "qgseditorwidgetregistry.h"

int main(int argc, char *argv[])
{
	/* ���ó�֧������ */
	QTextCodec *codec=QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	//! ʹ�� QSettings
	QCoreApplication::setOrganizationName( "YuanLong" );
	QCoreApplication::setApplicationName( "uavplatform" );

	QgsApplication a(argc, argv, true);
	a.setDefaultSvgPaths( QStringList( "../images/svg" ) ); // svg file path
	a.setWindowIcon( QIcon( "plane.ico" ) );
	QgsApplication::setPrefixPath( "C:/qgis-2.14.4/dev", true );
	QgsApplication::initQgis();

	// ʹ�÷����ļ�
	QTranslator qtTranslator; 
	qtTranslator.load("qgis_zh-Hans.qm"); 
	a.installTranslator(&qtTranslator);

	UavMain uav;
	uav.setWindowState(Qt::WindowMaximized);
	uav.show();

	QgsEditorWidgetRegistry::initEditors();

	return a.exec();
}
