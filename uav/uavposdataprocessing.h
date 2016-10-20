#ifndef POSDATAPROCESSING_H
#define POSDATAPROCESSING_H

#include <QObject>
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

	//! ����POS�Ի������ò���һ������POS�ļ�
	void oneButtonOrganizePosFiles();

	// POS��ʽ����
	void autoPosFormat();

	// POS����ת��
	void autoPosTransform();

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
	QgsPolygon rectangle( const QgsPoint& point, const double& h );

	// ����Դ��Ŀ���������ϵ
	QgsCoordinateReferenceSystem& sourceCrs();
	QgsCoordinateReferenceSystem& targetCrs();

private:

	QObject *parent;
	QList< QStringList > mFieldsList;
	QStringList descriptionList;
	QStringList descriptionUserList;

	QgsCoordinateReferenceSystem mSourceCrs;
	QgsCoordinateReferenceSystem mTargetCrs;
};

#endif // POSDATAPROCESSING_H
