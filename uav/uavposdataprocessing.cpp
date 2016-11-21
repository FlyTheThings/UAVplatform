#include "uavposdataprocessing.h"
#include "uavmain.h"
#include "uavcore.h"
#include "uavprj.h"
#include "uavinquiredemvalue.h"

#include "qgssinglesymbolrendererv2.h"
#include "qgscategorizedsymbolrendererv2.h"
#include "qgscoordinatereferencesystem.h"
#include "qgsvectordataprovider.h"
#include "qgscoordinatetransform.h"
#include "qgsmessagelog.h"
#include "qgslayertreeview.h"
#include "qgsmaplayerregistry.h"
#include "qgsvectorlayer.h"
#include "qgsmapcanvas.h"
#include "qgsfeature.h"
#include "qgscrscache.h"
#include "sqlite3.h"
#include <QUuid>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QColor>
#include <QStringList>

#include "proj_api.h"

uavPosDataProcessing::uavPosDataProcessing(QObject *parent)
	: QObject(parent)
{
	this->parent = parent;
}

uavPosDataProcessing::~uavPosDataProcessing()
{

}

void uavPosDataProcessing::setFieldsList( QList< QStringList >& list )
{
	if (list.isEmpty())
	{
		UavMain::instance()->messageBar()->pushMessage( "��ȡ�ع���ļ�����", 
			"��ȡ�ֶ�ʧ��, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage("��ȡ�ع���ļ����� : \t��ȡ�ֶ�ʧ��, ��������ֹ...");
		return;
	}
	mFieldsList = list;
}

void uavPosDataProcessing::autoPosFormat()
{
	QList<int> indexList;

	indexList << mSettings.value("/Uav/pos/fieldsList/cmb1", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb2", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb3", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb4", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb5", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb6", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb7", -1).toInt()
			  << mSettings.value("/Uav/pos/fieldsList/cmb8", -1).toInt();

	// ������˳�����������ֶ�
	for (int i=0; i<mFieldsList.size(); ++i)
	{
		QStringList newOutLineFields;
		QStringList outLineFields = mFieldsList.at(i);
		foreach (int j, indexList)
		{
			if (j != -1)
			{
				if (j)
					newOutLineFields.append(outLineFields.at(j-1));
				else
					newOutLineFields.append(QString::null);
			}
		}
		mFieldsList[i] = newOutLineFields;
	}

	QgsMessageLog::logMessage("�ع���ļ���ʽ�ع� : \t���.");
}

bool uavPosDataProcessing::autoPosTransform()
{	
	// ����Ŀ��ͶӰ
	if (!createTargetCrs())
	{
		return false;
	}

	// ����ת����ϵ
	QgsCoordinateTransform ct(mSourceCrs, mTargetCrs);
	if (!ct.isInitialised())
	{
		UavMain::instance()->messageBar()->pushMessage( "�ع������ת��", 
			"��������ת����ϵʧ��, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage("�ع������ת�� : \t��������ת����ϵʧ��, ��������ֹ.");
		return false;
	}

	// ��ʼת��
	for (int i=0; i<mFieldsList.size(); ++i)
	{
		QStringList list = mFieldsList.at(i);
		QgsPoint p = ct.transform(list.at(1).toDouble(), list.at(2).toDouble());
		list[1] = QString::number(p.x(), 'f');
		list[2] = QString::number(p.y(), 'f');
		mFieldsList[i] = list;
	}
	QgsMessageLog::logMessage("�ع������ת�� : \t���.");
	return true;
}

int uavPosDataProcessing::getCentralMeridian()
{
	QMap< QString, int > cmMap;

	for (int i=0; i<mFieldsList.size(); ++i)
	{
		bool isok = false;
		QStringList list = mFieldsList.at(i);
		QString str_x = list.at(1);
		double x = str_x.toDouble(&isok);
		if (!isok)
		{
			QgsMessageLog::logMessage(QString("�ع�����뾭�ȼ��� : \t||--> ��%1�к����겻��ʶ��, ��������������.").arg(i));
			mFieldsList.removeAt(i);
		}

		// �������뾭��
		int cm = uavPrj::getCentralmeridian3(x);

		// ͳ����ͬ���뾭�߳��ִ���
		if (cmMap.contains(QString::number(cm)))
		{
			int count = cmMap[QString::number(cm)];
			cmMap[QString::number(cm)] = count + 1;
		}
		else
		{
			cmMap[QString::number(cm)] = 1;
		}
	}

	// ���س��ִ����������뾭��
	QMap< QString, int >::iterator it = cmMap.begin();
	QString strCm;
	int count=0;
	while (it!=cmMap.end())
	{
		if (it.value() > count)
		{
			strCm = it.key();
		}
		++it;
	}

	return strCm.toInt();
}

QgsVectorLayer* uavPosDataProcessing::autoSketchMap()
{
	UavMain::instance()->mapCanvas()->freeze();

	emit startProcess();

	QString layerProperties = "Polygon?";													// ��������
	layerProperties.append(QString( "field=id:integer&field=��Ƭ���:string(50)"				// ����ֶ�
													"&field=�ع������:string(30)"
													"&field=Omega:string(10)"
													"&field=Phi:string(10)"
													"&field=Kappa:string(10)"
													"&field=����ֱ���:string(10)&"));
	layerProperties.append(QString( "index=yes&" ));										// ��������
	layerProperties.append(QString( "memoryid=%1" ).arg( QUuid::createUuid().toString() ));	// ��ʱ����

	QString sketchMapName;
	sketchMapName = mSettings.value("/Uav/pos/lePosFile", "").toString();
	sketchMapName = QFileInfo(sketchMapName).baseName();
	if (sketchMapName.isEmpty())
		sketchMapName = "������ͼ";

	QgsVectorLayer* newLayer = new QgsVectorLayer( 
		layerProperties, sketchMapName, QString( "memory" ) );
	
	if (!newLayer->isValid())
	{
		UavMain::instance()->messageBar()->pushMessage( "����������ͼ", 
			"������ͼʧ��, ��������ֹ, ע����plugins�ļ���!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("����������ͼ : \t������ͼʧ��, ��������ֹ, ע����plugins�ļ��С�"));
		return nullptr;
	}

	// ����ͼ���������ϵ
	QgsCoordinateReferenceSystem srs( mTargetCrs.srsid(), QgsCoordinateReferenceSystem::InternalCrsId );
	newLayer->setCrs(srs);

	// ����ͼ��������Ϊ��ͼ��ͬ���Ĳ�������ϵ
	UavMain::instance()->mapCanvas()->setDestinationCrs(srs);

	// ��ӵ���ͼ
	QgsMapLayerRegistry::instance()->addMapLayer(newLayer);

	QgsVectorDataProvider* dateProvider = newLayer->dataProvider();

	// ������Ƭ����ֱ���
	uavInquireDemValue dem(this);
	QList< QgsPoint > pointFirst;
	QList< qreal > elevations;

	foreach(QStringList list, mFieldsList)
	{
		// ȡ���ֶ�����
		QgsPoint point;
		point.setX(list.at(1).toDouble());
		point.setY(list.at(2).toDouble());
		pointFirst.append(point);
	}

	bool isbl = false;
	if ( uavInquireDemValue::eOK == dem.inquireElevations(pointFirst, elevations, &srs) )
	{
		isbl = true;
		if (mFieldsList.size() == elevations.size())
			isbl = true;
		else 
			isbl = false;
	}

	int index = 0;
	while (index != mFieldsList.size())
	{
		qreal elevation = 0.0;
		QStringList list = mFieldsList.at(index);
		if (isbl)
			elevation = elevations.at(index);
		else
			elevation = -9999;
		double resolution = calculateResolution(list.at(3).toDouble(), elevation);
		list.append(QString::number(resolution, 'f', 2));
		mFieldsList[index] = list;
		++index;
	}

	// ������Ҫ��
	int icount = 0;
	QgsFeatureList featureList;
	foreach(QStringList list, mFieldsList)
	{
		// ȡ���ֶ�����
		double x = list.at(1).toDouble();
		double y = list.at(2).toDouble();
		double resolution = list.at(list.size()-1).toDouble();
		double mRotate = list.at(6).toDouble();

		if (resolution == 0.0)
		{
			QgsMessageLog::logMessage(QString("\t\t||-->��Ƭ:%1 �߳��쳣������ֱ��ʼ���Ϊ0��������������Ƭ.").arg(list.at(0)));
			continue;
		}

		// ������Ҫ��, ������Omegaѡ��Ƕ�
		QgsPolygon polygon = rectangle( QgsPoint(x, y), resolution );
		QgsGeometry* mGeometry = QgsGeometry::fromPolygon(polygon);
		mGeometry->rotate( mRotate, QgsPoint(x, y) );

		// ���ü���Ҫ��������
		QgsFeature MyFeature;
		MyFeature.setGeometry( mGeometry );
		MyFeature.setAttributes(QgsAttributes() << QVariant(++icount)
												<< QVariant(list.first())
												<< QVariant(QString(list.at(1)+","+list.at(2)))
												<< QVariant(list.at(4))
												<< QVariant(list.at(5))
												<< QVariant(list.at(6))
												<< QVariant(list.at(list.size()-1)));
		featureList.append(MyFeature);
	}

	// ��ʼ�༭
	newLayer->startEditing();

	// ���Ҫ�ؼ���ͼ����
	dateProvider->addFeatures(featureList);

	// ����
	newLayer->commitChanges();

	// ���·�Χ
	newLayer->updateExtents();

	// ��ʼ������
	// ���ȱʡ�ķ���
	QgsSymbolV2* newSymbolV2 = QgsSymbolV2::defaultSymbol(newLayer->geometryType());
	// ����͸��������ɫ
	newSymbolV2->setAlpha(0.5);
	newSymbolV2->setColor(Qt::gray);
	QgsSingleSymbolRendererV2* singleRenderer = new QgsSingleSymbolRendererV2(newSymbolV2);
	newLayer->setRendererV2(singleRenderer);

	emit stopProcess();

	QgsMessageLog::logMessage(QString("����������ͼ : \t���. ������%1����Ƭ��ͼ.").arg(newLayer->featureCount()));
	UavMain::instance()->mapCanvas()->freeze( false );
	UavMain::instance()->refreshMapCanvas();
	return newLayer;
}

bool uavPosDataProcessing::createTargetCrs()
{
	// ��õ�ǰ�ع��Ĳ�������ϵ
	QString myDefaultCrs = mSettings.value( "/Uav/pos/options/projectDefaultCrs", GEO_EPSG_CRS_AUTHID ).toString();
	mSourceCrs.createFromOgcWmsCrs( myDefaultCrs );

	// ��֤Դ��������ϵ
	if (!mSourceCrs.isValid())
	{
		UavMain::instance()->messageBar()->pushMessage( "�ع������ת��", 
			"��Ŀû��ָ����ȷ�Ĳ�������ϵ, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage("�ع������ת�� : \t��Ŀû��ָ����ȷ�Ĳ�������ϵ, ��������ֹ!");
		return false;
	}

	// ���������Ƿ���4�ֳ��õĵ�������ϵ
	if ( !( (mSourceCrs.authid() == "EPSG:4326") ||		// WGS84
		(mSourceCrs.authid() == "EPSG:4490") ) )		// CGCS2000
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			"��Ŀָ���˴���Ĳ�������ϵ, Ŀǰ��֧��WGS84��CGCS2000, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage("������������ϵ : \t��Ŀָ���˴���Ĳ�������ϵ, Ŀǰ��֧��WGS84��CGCS2000, ��������ֹ!");
		return false;
	}

	// ����ع���ļ��е����뾭��
	int cm = getCentralMeridian();

	// ��龭���Ƿ���������Χ��
	if ( !((cm>74 && cm<136) || (cm>24 && cm<46) || (cm>12 && cm<24)) )
	{
		UavMain::instance()->messageBar()->pushMessage( "�����Զ�����", 
			"�ع���ļ��еľ��Ȳ������й���Χ��, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("�����Զ����� : \t�ع���ļ��еľ��� %1 �������й���Χ��, ��������ֹ!").arg(cm));
		return false;
	}

	// ����WKT��ʽͶӰ����ϵ
	QString wkt;
	QString strDescription;
	if (mSourceCrs.authid() == "EPSG:4326")
	{
		wkt = uavPrj::createProj4Wgs84Gcs(cm);

		//���Ӵ���
		if (cm>74 && cm<136)
			strDescription = QString("WGS 84 / Gauss-Kruger CM %1E").arg(cm);
		//�Ӵ���
		if (cm>12 && cm<46)
			strDescription = QString("WGS 84 / Gauss-Kruger zone %1").arg(cm);
	}
	else if (mSourceCrs.authid() == "EPSG:4490")
	{
		wkt = uavPrj::createProj4Cgcs2000Gcs(cm);

		//���Ӵ���
		if (cm>74 && cm<136)
			strDescription = QString("CGCS2000 / Gauss-Kruger CM %1E").arg(cm);
		//�Ӵ���
		if (cm>12 && cm<46)
			strDescription = QString("CGCS2000 / Gauss-Kruger zone %1").arg(cm);
	}

	mTargetCrs.createFromProj4(wkt);
	
	if ( !mTargetCrs.isValid() )
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("�ع�����뾭�߼���Ϊ%1, ����ͶӰ�ο�����ϵʧ��, ��������ֹ!").arg(cm), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \t�ع�����뾭�߼���Ϊ%1, ����ͶӰ�ο�����ϵʧ��, ��������ֹ!").arg(cm));
		return false;
	}
	
	QgsMessageLog::logMessage(QString("������������ϵ : \t�ع�����뾭�߼���Ϊ%1, ����ͶӰ�ο�����ϵ\"%2\"�ɹ�.").arg(cm).arg(mTargetCrs.description()));

	// ����������ϵ�����б�
	if (descriptionList.isEmpty())
	{
		if (!descriptionForDb(descriptionList))
			return false;
	}
	if (descriptionUserList.isEmpty())
	{
		if (!descriptionForUserDb(descriptionUserList))
			return false;
	}
	
	// ������ݿ���û�������������ϵ����д��
	if (descriptionList.contains(strDescription) || descriptionUserList.contains(strDescription))
		return true;
	else
	{
		long return_id = mTargetCrs.saveAsUserCRS( strDescription );
		if (!(return_id == -1))
		{
			descriptionUserList.clear();
			if (!descriptionForUserDb(descriptionUserList))
				return false;
		}
		else
		{
			UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
				QString("�����ݿ���д�� %1 �ο�����ϵʧ��, ��������ֹ!").arg(strDescription), 
				QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
			QgsMessageLog::logMessage(QString("������������ϵ : \t�����ݿ���д�� %1 �ο�����ϵʧ��, ��������ֹ!").arg(strDescription));
			return false;
		}
	}

	return true;
}

QgsCoordinateReferenceSystem& uavPosDataProcessing::sourceCrs()
{
	return mSourceCrs;
}

QgsCoordinateReferenceSystem& uavPosDataProcessing::targetCrs()
{
	return mTargetCrs;
}

QgsPolygon uavPosDataProcessing::rectangle( const QgsPoint& point, const double& resolution )
{
	int weight = mSettings.value("/Uav/pos/options/leWidth", 0).toInt();
	int height = mSettings.value("/Uav/pos/options/leHeight", 0).toInt();
	double midx = (weight*resolution) / 2;
	double midy = (height*resolution) / 2;

	QgsPolyline polyline;
	QgsPolygon polyon;
	polyline << QgsPoint( point.x()-midx, point.y()+midy )
		     << QgsPoint( point.x()+midx, point.y()+midy )
		     << QgsPoint( point.x()+midx, point.y()-midy )
		     << QgsPoint( point.x()-midx, point.y()-midy );
	polyon << polyline;

	return polyon;
}

bool uavPosDataProcessing::descriptionForDb( QStringList &list )
{
	sqlite3      *myDatabase;
	const char   *myTail;
	sqlite3_stmt *myPreparedStatement;
	int           myResult;

	QString databaseFileName = QDir::currentPath() + "/Resources/srs.db";
	if ( !QFileInfo( databaseFileName ).exists() )
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("û���ҵ�srs.db, ��������ֹ!"), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \tû���ҵ�srs.db, ��������ֹ!"));
		return false;
	}

	// ������ݿ��Ƿ����
	myResult = sqlite3_open_v2(databaseFileName.toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, nullptr);
	if ( myResult )
	{
		QString errInfo = QString( "���ܴ����ݿ�: %1" ).arg( sqlite3_errmsg( myDatabase ) );
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("%1, ��������ֹ!").arg(errInfo), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \t%1, ��������ֹ!").arg(errInfo));
		return false;
	}

	// ���ò�ѯ�����б������ͶӰ��Ϣ
	QString mySql = "select description, srs_id, upper(auth_name||':'||auth_id), is_geo, name, parameters, deprecated from vw_srs where 1 order by name,description";
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );

	if ( myResult == SQLITE_OK )
	{
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			QString strDescription = ( const char * )sqlite3_column_text( myPreparedStatement, 0 );
			
			list.append(strDescription);
		}
	}
	else
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("��ѯϵͳ���ݿ�, ���������ͶӰ��Ϣʧ��, ��������ֹ!"), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \t��ѯϵͳ���ݿ�, ���������ͶӰ��Ϣʧ��, ��������ֹ!"));
		sqlite3_finalize( myPreparedStatement );
		sqlite3_close( myDatabase );
		return false;
	}

	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );
	return true;
}

bool uavPosDataProcessing::descriptionForUserDb( QStringList &list )
{
	QString databaseFileName = QDir::currentPath() + "/Resources/qgis.db";
	if ( !QFileInfo( databaseFileName ).exists() )
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			"û���ҵ�qgis.db, ��������ֹ!", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \tû���ҵ�qgis.db, ��������ֹ!"));
		return false;
	}

	sqlite3      *database;
	const char   *tail;
	sqlite3_stmt *stmt;
	// ������ݿ��Ƿ����
	int result = sqlite3_open_v2( databaseFileName.toUtf8().constData(), &database, SQLITE_OPEN_READONLY, nullptr );
	if ( result )
	{
		QString errInfo = QString( "���ܴ����ݿ�: %1" ).arg( sqlite3_errmsg( database ) );
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("%1, ��������ֹ!").arg(errInfo), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \t%1, ��������ֹ!").arg(errInfo));
		return false;
	}

	// ���ò�ѯ�Լ���������б������ͶӰ��Ϣ
	QString sql = QString( "select description, srs_id from vw_srs where 1" );

	result = sqlite3_prepare( database, sql.toUtf8(), sql.toUtf8().length(), &stmt, &tail );

	if ( result == SQLITE_OK )
	{
		while ( sqlite3_step( stmt ) == SQLITE_ROW )
		{
			QString strDescription = ( const char * )sqlite3_column_text( stmt, 0 );
			list.append(strDescription);
		}
	}
	else
	{
		UavMain::instance()->messageBar()->pushMessage( "������������ϵ", 
			QString("��ѯϵͳ���ݿ�, ���������ͶӰ��Ϣʧ��, ��������ֹ!"), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("������������ϵ : \t��ѯϵͳ���ݿ�, ���������ͶӰ��Ϣʧ��, ��������ֹ!"));
		sqlite3_finalize( stmt );
		sqlite3_close( database );
		return false;
	}

	sqlite3_finalize( stmt );
	sqlite3_close( database );
	return true;
}

bool uavPosDataProcessing::isValid()
{
	return !mFieldsList.isEmpty();
}

QList< QStringList >* uavPosDataProcessing::fieldsList()
{
	return &mFieldsList;
}

double uavPosDataProcessing::calculateResolution( const double &absoluteHeight, const double &groundHeight )
{
	double resolution = 0.0;
	double elevation = 0.0;
	double pixelSize = 0.0;
	double focal = 0.0;

	QString tmp;
	if (groundHeight == -9999)
		elevation = mSettings.value("/Uav/pos/options/leAverageEle", 0.0).toDouble();
	else
		elevation = groundHeight;

	pixelSize = mSettings.value("/Uav/pos/options/lePixelSize", 0.0).toDouble();
	focal = mSettings.value("/Uav/pos/options/leFocal", 0.0).toDouble();
	resolution = (absoluteHeight-elevation)*pixelSize/1000/focal;

	return resolution;
}

bool uavPosDataProcessing::posExport()
{
	if (mFieldsList.isEmpty())
	{
		UavMain::instance()->messageBar()->pushMessage( "�����ع���ļ�", 
			"�ڴ����鱻�ƻ���δ��ȷ����������ϵ������Ա���.", 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("�����ع���ļ� : \t�ڴ����鱻�ƻ���δ��ȷ����������ϵ������Ա���."));
		return false;
	}

	QString path = mSettings.value("/Uav/pos/lePosFile", "").toString();
	path.insert(path.size()-4, "out");
	QFile file(path);
	if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))   //ֻд���ı�����д
	{
		UavMain::instance()->messageBar()->pushMessage( "�����ع���ļ�", 
			QString("����%1�ع���ļ�ʧ��.").arg(QDir::toNativeSeparators(path)), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("�����ع���ļ� : \t����%1�ع���ļ�ʧ��.").arg(QDir::toNativeSeparators(path)));
		return false;
	}

	QTextStream out(&file);
	foreach (QStringList strList, mFieldsList)
	{
		QString strLine;
		for (int i=0; i<(strList.size()-2); ++i)
		{
			QString str = strList.at(i);
			strLine.append(str + ' ');
		}
		out << strLine + '\n';
	}

	file.close();
	UavMain::instance()->messageBar()->pushMessage( "�����ع���ļ�", 
		QString("����%1�ع���ļ��ɹ�.").arg(QDir::toNativeSeparators(path)), 
		QgsMessageBar::SUCCESS, UavMain::instance()->messageTimeout() );
	QgsMessageLog::logMessage(QString("�����ع���ļ� : \t����%1�ع���ļ��ɹ�.").arg(QDir::toNativeSeparators(path)));
	return true;
}

const QStringList uavPosDataProcessing::checkPosSettings()
{
	QStringList errList;
	double tmpDouble = 0.0;
	int tmpInt = 0;
	
	tmpDouble = mSettings.value("/Uav/pos/options/leFocal", 0.0).toDouble();
	if (!tmpDouble)
		errList.append("�������");
	tmpDouble = mSettings.value("/Uav/pos/options/lePixelSize", 0.0).toDouble();
	if (!tmpDouble)
		errList.append("�����С");
	tmpInt = mSettings.value("/Uav/pos/options/leHeight", 0.0).toInt();
	if (!tmpInt)
		errList.append("�����С(��)");
	tmpInt = mSettings.value("/Uav/pos/options/leWidth", 0.0).toInt();
	if (!tmpInt)
		errList.append("�����С(��)");

	return errList;
}
