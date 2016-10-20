#ifndef UAVINQUIREDEMVALUE_H
#define UAVINQUIREDEMVALUE_H

#include <QObject>
#include <QList>
#include <QMap>

class QPointF;
class QString;
class QgsRasterLayer;
class QgsCoordinateReferenceSystem;

class uavInquireDemValue : public QObject
{
	Q_OBJECT

public:
	enum ErrorType
	{
		eOK,						// ��Ч
		eInvalidDefaultDemPath,		// ��Ч��Ĭ��·��
	};

	uavInquireDemValue(QObject *parent);
	~uavInquireDemValue();
	
	/**
    * @brief                    ����Ŀ��ο�����ϵ
    * @author                   YuanLong
    * @param crs				���ݲο�����ϵ
	* @warning					���øú������ڲ�ѯ�߳���Ϣʱ���û������
	*							�ο�����ϵ����Ĭ��ʹ�øú��������Crs��
    * @return
    */
	void setTargetCrs(const QgsCoordinateReferenceSystem& crs);

	
	/**
    * @brief                    ��ʾָ��DEM�ļ�·��
    * @author                   YuanLong
    * @param demPath			����DEM�ļ�����·��
	* @warning					������ݵ���һ����ЧDEM·���������ڸ�DEM��ѯ�߳���Ϣ��
	*							�������Ĭ��DEM���ݡ��ú���ֻ������Ҫʹ���Լ���DEM����
	*							ʱ�ŵ��á�
    * @return
    */
	void setDemPath(const QString& demPath);

	/**
    * @brief                    ��ѯ������������꼯��Ӧ�ĸ߳���Ϣ
    * @author                   YuanLong
    * @param point				ƽ�����꣨���꼯��
    * @param elevation			�����ѯ�ĸ߳���Ϣ
    * @param crs				���ݲο�����ϵ
	* @warning					���û��ָ��crs����Ĭ�ϵ���setTargetCrs()����
	*							��crs�����ϲ�����δ������ᷢ�ʹ�����Ϣ��
	*							�ú����ڲ��������һϵ�к�������ɸ̲߳�ѯ������
    * @return
    */
	uavInquireDemValue::ErrorType inquireElevation(const QPointF& point, qreal& elevation, const QgsCoordinateReferenceSystem* crs = nullptr);
	uavInquireDemValue::ErrorType inquireElevation(const QList< QPointF >& points, QList< qreal >& elevations, const QgsCoordinateReferenceSystem* crs = nullptr);

private:
	/**
    * @brief                    ���ݴ��ݵ�ƽ������������漰��DEM��Χ
    * @author                   YuanLong
    * @return
    */
	void involved();

	/**
    * @brief                    �������漰��DEM����
    * @author                   YuanLong
	* @warning					����involved()�������DEM��Χ����Ĭ��·������setDemPath()��
	*							�¼���DEM������դ��ͼ����ʽ�洢��
    * @return
    */
	void loadDem();

	/**
    * @brief                    �����߳�ֵ
    * @author                   YuanLong
    * @param point				ƽ������
	* @warning					�ú�������crs��DEM���ݶ�׼���õ�����µ��ã�
	*							�����������Ӧ��DEM�ϵĸ߳�ֵ��
    * @return
    */
	const qreal& searchElevationValue(const QPointF& point);

private:
	QList< QPointF > mPoints;
	QString mDefaultDemPath;
	QString mCustomizeDemPath;
	QgsCoordinateReferenceSystem mTargetCrs;
	QMap< QString, QgsRasterLayer* > mRasterLayersMap;
};

#endif // UAVINQUIREDEMVALUE_H
