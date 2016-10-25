#include "uavppinteractive.h"
#include "uavmain.h"
#include "uavcore.h"

#include "qgsmapcanvas.h"
#include "qgsmessagelog.h"
#include "qgslayertreeview.h"
#include "qgsvectorlayer.h"
#include "qgssymbolv2.h"
#include "qgssinglesymbolrendererv2.h"
#include "qgscategorizedsymbolrendererv2.h"

uavPPInteractive::uavPPInteractive(QObject *parent)
	: QObject(parent),
	mLayer(nullptr),
	mFieldsList(nullptr),
	mLinkedSymbolV2(nullptr),
	mUnlinkedSymbolV2(nullptr)
{
	this->parent = parent;
	isLinked = false;

	cLinked.setRgb(186, 221, 105);
	cUnlinked = Qt::gray;

	definitionLinkedSymbolV2();
	definitionUnLinkedSymbolV2();
}

uavPPInteractive::uavPPInteractive(QObject *parent, QgsVectorLayer* layer, QList< QStringList >* fieldsList)
	: QObject(parent),
	mLayer(layer),
	mFieldsList(fieldsList),
	mLinkedSymbolV2(nullptr),
	mUnlinkedSymbolV2(nullptr)
{
	this->parent = parent;
	isLinked = false;

	cLinked.setRgb(186, 221, 105);
	cUnlinked = Qt::gray;

	definitionLinkedSymbolV2();
	definitionUnLinkedSymbolV2();
}

uavPPInteractive::~uavPPInteractive()
{

}

void uavPPInteractive::createPPlinkage()
{
	if (mFieldsList->isEmpty())
		return;

	QSettings mSetting;
	QString phtotPath = mSetting.value("/Uav/pos/lePosFile", "").toString();
	phtotPath = QFileInfo(phtotPath).path();
	phtotPath += "/" + mSetting.value("/Uav/pos/options/lePhotoFolder", "").toString();

	if (!QFileInfo(phtotPath).exists())
	{
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 δָ����ȷ����Ƭ·��, ����������ϵʧ��...").arg(phtotPath));
		isLinked = false;
		return;
	}

	emit startProcess();
	QStringList list = uavCore::searchFiles(phtotPath, QStringList() << "*.tif" << "*.jpg", 0, "������Ƭ...");
	emit stopProcess();

	if (list.isEmpty())
	{
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 ·����δ������tif��jpg��ʽ�ĺ�����Ƭ, ����������ϵʧ��...").arg(phtotPath));
		isLinked = false;
		return;
	}
	else
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 ·����������%2����Ƭ.").arg(phtotPath).arg(list.size()));

	// ��POS����ȡ��Ƭ����
	QStringList basePos;
	foreach (QStringList subList, *mFieldsList)
		basePos.append(subList.at(0));

	// ���mPhotoMap
	foreach (QString str, list)
		mPhotoMap[QFileInfo(str).baseName()] = str;
	
	QMap<QString, QString>::iterator it = mPhotoMap.begin();
	while (it != mPhotoMap.end())
	{
		if (!basePos.contains(it.key()))
		{
			QgsMessageLog::logMessage(QString("PP��̬���� : \t--> %1���ع���ļ���δ�ҵ���Ӧ��¼.").arg(it.key()));
			mPhotoMap.remove(it.key());
		}
		++it;
	}

	QgsMessageLog::logMessage(QString("PP��̬���� : \t�ɹ�����PP������ϵ..."));
	isLinked = true;
}

void uavPPInteractive::unPPlinkage()
{
	upDataUnLinkedSymbol();
	mPhotoMap.clear();
	isLinked = false;
}

void uavPPInteractive::initLayerCategorizedSymbolRendererV2()
{
	QgsCategoryList cats;
	QgsFeature f;
	QgsFeatureIterator it = mLayer->getFeatures();
	while (it.nextFeature(f))
	{
		cats << QgsRendererCategoryV2(f.attribute("��Ƭ���"), unlinkedSymbolV2(), "δ����");
	}

	mLayer->setRendererV2( new QgsCategorizedSymbolRendererV2("��Ƭ���", cats) );
	UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
}

void uavPPInteractive::upDataLinkedSymbol()
{
	// ���Ŀǰͼ��ķ�����ʽ������Ⱦ��
	QgsCategorizedSymbolRendererV2* cRenderer;
	cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	if (!cRenderer)
	{
		initLayerCategorizedSymbolRendererV2();
		cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	}
	

	QMap<QString, QString>::iterator it = mPhotoMap.begin();
	while (it != mPhotoMap.end())
	{
		// ����Ⱦ���в����Ƿ��и����б��е���Ƭ���
		int index = cRenderer->categoryIndexForValue(QVariant(it.key()));

		// ���ݲ��ҽ�����и���
		if (-1 == index)
		{
			cRenderer->addCategory(QgsRendererCategoryV2(QVariant(it.key()), linkedSymbolV2(), QString("�ѹ��� "+)));
		}
		else
		{
			cRenderer->deleteCategory(index);
			cRenderer->addCategory(QgsRendererCategoryV2(QVariant(it.key()), unlinkedSymbolV2(), "δ����"));
		}
		++it;
	}

	UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
	UavMain::instance()->refreshMapCanvas();
}

void uavPPInteractive::upDataUnLinkedSymbol()
{
	// ���Ŀǰͼ��ķ�����ʽ������Ⱦ��
	QgsCategorizedSymbolRendererV2* cRenderer;
	cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	if (!cRenderer)
	{
		initLayerCategorizedSymbolRendererV2();
		cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	}

	QgsCategoryList cgList = cRenderer->categories();
	for (int i=0; i<cgList.size(); i++)
	{
		cRenderer->updateCategorySymbol(i, unlinkedSymbolV2());
	}

	//foreach (QString str_value, list)
	//{
	//	// ����Ⱦ���в����Ƿ��и����б��е���Ƭ���
	//	int index = cRenderer->categoryIndexForValue(QVariant(str_value));

	//	// ���ݲ��ҽ�����и���
	//	if (-1 == index)
	//	{
	//		cRenderer->addCategory(QgsRendererCategoryV2(QVariant(str_value), unlinkedSymbolV2(), "δ����"));
	//	} 
	//	else
	//	{
	//		cRenderer->deleteCategory(index);
	//		cRenderer->addCategory(QgsRendererCategoryV2(QVariant(str_value), unlinkedSymbolV2(), "δ����"));
	//	}
	//}

	UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
	UavMain::instance()->refreshMapCanvas();
}

void uavPPInteractive::definitionLinkedSymbolV2()
{
	// ���ȱʡ�ķ���
	mLinkedSymbolV2 = QgsSymbolV2::defaultSymbol(mLayer->geometryType());

	// ����͸��������ɫ
	mLinkedSymbolV2->setAlpha(0.5);
	mLinkedSymbolV2->setColor(cLinked);
}

void uavPPInteractive::definitionUnLinkedSymbolV2()
{
	// ���ȱʡ�ķ���
	mUnlinkedSymbolV2 = QgsSymbolV2::defaultSymbol(mLayer->geometryType());

	// ����͸��������ɫ
	mUnlinkedSymbolV2->setAlpha(0.5);
	mUnlinkedSymbolV2->setColor(cUnlinked);
}

QgsSymbolV2* uavPPInteractive::linkedSymbolV2()
{
	return mLinkedSymbolV2->clone();
}

QgsSymbolV2* uavPPInteractive::unlinkedSymbolV2()
{
	return mUnlinkedSymbolV2->clone();
}

bool uavPPInteractive::isValid()
{
	if (!mLayer || !mFieldsList)
	{
		return false;
	}
	if (!mLayer->isValid() || mFieldsList->isEmpty())
	{
		return false;
	}
	return true;
}

void uavPPInteractive::setVectorLayer( QgsVectorLayer* layer )
{
	if (!layer || !layer->isValid())
		return;
	mLayer = layer;
}

void uavPPInteractive::setFieldsList( QList< QStringList >* fieldsList )
{
	if (!fieldsList)
		return;
	mFieldsList = fieldsList;
}
