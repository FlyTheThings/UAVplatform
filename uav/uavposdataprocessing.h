#ifndef POSDATAPROCESSING_H
#define POSDATAPROCESSING_H

#include <QObject>
#include <QSettings>
#include "qgscoordinatereferencesystem.h"
#include "qgsgeometry.h"

class QgsVectorLayer;

// ���������ع��������ص���
class uavPosDataProcessing : public QObject
{
	Q_OBJECT

public:
	uavPosDataProcessing(QObject *parent = nullptr);
	~uavPosDataProcessing();

	bool isValid();

	QList< QStringList >* fieldsList();

	// POS��ʽ����
	void autoPosFormat();

	// POS����ת��
	bool autoPosTransform();

	// ������ͼ
	QgsVectorLayer* autoSketchMap();

signals:
	void startProcess();
	void stopProcess();

private slots:

	// ����POS�б�
	void setFieldsList(QList< QStringList >&);

private:

	// �������뾭��, �Զ�Ϊ׼
	int getCentralMeridian();

	// ����Ŀ��ͶӰ�ο�����ϵ
	bool createTargetCrs();

	// ����ϵͳ���ݿ�srs.db�л�õĲ�������ϵ��������б�
	bool descriptionForDb(QStringList &list);

	// �����û����ݿ��л�õĲ�������ϵ��������б�
	bool descriptionForUserDb(QStringList &list);

	// �����ع��������������Ը̼߳�����Ƭ4���ǵ�����꣬������
	QgsPolygon rectangle( const QgsPoint& point, const double& resolution );

	// ����ֱ���
	double calculateResolution(const double &absoluteHeight, const double &groundHeight);

	// ����Դ��Ŀ���������ϵ
	QgsCoordinateReferenceSystem& sourceCrs();
	QgsCoordinateReferenceSystem& targetCrs();

private:
	QObject *parent;
	QSettings mSettings;
	QList< QStringList > mFieldsList;
	QStringList descriptionList;
	QStringList descriptionUserList;

	QgsCoordinateReferenceSystem mSourceCrs;
	QgsCoordinateReferenceSystem mTargetCrs;
};

#endif // POSDATAPROCESSING_H
