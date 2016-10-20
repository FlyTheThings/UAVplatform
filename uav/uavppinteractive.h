#ifndef PPINTERACTIVE_H
#define PPINTERACTIVE_H

#include <QObject>
#include <QColor>
#include <QMap>

class QgsVectorLayer;
class QgsSymbolV2;

/*
 *�����ع������Ƭ�����л���ϸ��
 **/
class uavPPInteractive : public QObject
{
	Q_OBJECT

public:
	uavPPInteractive(QObject *parent);
	uavPPInteractive(QObject *parent, QgsVectorLayer* layer, QList< QStringList >* fieldsList);
	~uavPPInteractive();

	bool isValid();
	bool islinked(){ return isLinked; };

	void setVectorLayer(QgsVectorLayer* layer);
	void setFieldsList(QList< QStringList >* fieldsList);

	// ����POS��Photo������ϵ
	void createPPlinkage();

	// �Ͽ�������ϵ
	void unPPlinkage();

	// �����ع������Ƭ�ѹ����ķ���
	void upDataLinkedSymbol();
	// �����ع������Ƭδ�����ķ���
	void upDataUnLinkedSymbol();

signals:
	void startProcess();
	void stopProcess();

private:

	// ��ʼ��ͼ�����Ⱦ��ʽΪ������Ⱦ
	void initLayerCategorizedSymbolRendererV2();

	// �����ѹ�����δ�����ķ�����ʽ
	void definitionLinkedSymbolV2();
	void definitionUnLinkedSymbolV2();

	// �����ѹ�����δ�����ķ�����ʽ����
	QgsSymbolV2* linkedSymbolV2();
	QgsSymbolV2* unlinkedSymbolV2();

private:
	QObject *parent;

	// �Ƿ������ɹ�
	bool isLinked;

	// ��Ƭ�б�,�����ļ�baseName������·��
	QMap<QString, QString> mPhotoMap;
	QgsVectorLayer* mLayer;
	QList< QStringList >* mFieldsList;

	QColor cLinked;		// �ѹ����ķ�����ɫ
	QColor cUnlinked;	// δ����������ɫ

	QgsSymbolV2* mLinkedSymbolV2;
	QgsSymbolV2* mUnlinkedSymbolV2;
};

#endif // PPINTERACTIVE_H
