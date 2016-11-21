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
	cError = Qt::red;
	cWarning = Qt::yellow;

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
		UavMain::instance()->messageBar()->pushMessage( "PP��̬����", 
			QString("%1 δָ����ȷ����Ƭ·��, ����������ϵʧ��...").arg(QDir::toNativeSeparators(phtotPath)), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 δָ����ȷ����Ƭ·��, ����������ϵʧ��...").arg(QDir::toNativeSeparators(phtotPath)));
		isLinked = false;
		return;
	}

	emit startProcess();
	QStringList list = uavCore::searchFiles(phtotPath, QStringList() << "*.tif" << "*.jpg");
	emit stopProcess();

	if (list.isEmpty())
	{
		UavMain::instance()->messageBar()->pushMessage( "PP��̬����", 
			QString("\t%1 ·����δ������tif��jpg��ʽ�ĺ�����Ƭ, ����������ϵʧ��...").arg(QDir::toNativeSeparators(phtotPath)), 
			QgsMessageBar::CRITICAL, UavMain::instance()->messageTimeout() );
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 ·����δ������tif��jpg��ʽ�ĺ�����Ƭ, ����������ϵʧ��...").arg(QDir::toNativeSeparators(phtotPath)));
		isLinked = false;
		return;
	}
	else
		QgsMessageLog::logMessage(QString("PP��̬���� : \t%1 ·����������%2����Ƭ.").arg(QDir::toNativeSeparators(phtotPath)).arg(list.size()));

	// ��POS����ȡ�ع������
	QStringList basePos;
	foreach (QStringList subList, *mFieldsList)
		basePos.append(subList.at(0));

	//matchPosName(list, basePos);

	// ���mPhotoMap, mPhotoMap[001] = "D:\��������\ƽ̨����\photo\001.tif"
	foreach (QString str, list)
		mPhotoMap[QFileInfo(str).baseName()] = str;
	
	QMap<QString, QString>::iterator it = mPhotoMap.begin();
	while (it != mPhotoMap.end())
	{
		QString key = it.key();
		if (!basePos.contains(key))
		{
			QgsMessageLog::logMessage(QString("PP��̬���� : \t||--> ��Ƭ:%1���ع���ļ���δ�ҵ���Ӧ��¼.").arg(key));
			it = mPhotoMap.erase(it);
		}
		else
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
		cats << QgsRendererCategoryV2(f.attribute("��Ƭ���"), unlinkedSymbolV2(), f.attribute("��Ƭ���").toString());
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
		 if (-1 != index)
		{
			cRenderer->deleteCategory(index);
			cRenderer->addCategory(QgsRendererCategoryV2(QVariant(it.key()), linkedSymbolV2(), it.key()));
		}
		++it;
	}

	cRenderer->sortByValue();
	UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
	UavMain::instance()->refreshMapCanvas();
}

void uavPPInteractive::upDataUnLinkedSymbol()
{
	// ���Ŀǰͼ��ķ�����ʽ������Ⱦ��
	//QgsCategorizedSymbolRendererV2* cRenderer;
	//cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	//if (!cRenderer)
	//{
	//	initLayerCategorizedSymbolRendererV2();
	//	cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	//}

	//QgsCategoryList cgList = cRenderer->categories();
	//for (int i=0; i<cgList.size(); i++)
	//{
	//	cRenderer->updateCategorySymbol(i, unlinkedSymbolV2());
	//}

	//UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
	//UavMain::instance()->refreshMapCanvas();
	// 
	QMap<QString, QString>::iterator it = mPhotoMap.begin();
	while (it != mPhotoMap.end())
	{
		addChangedItem(it.key());
		++it;
	}

	updata(unlinkedSymbolV2());
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

void uavPPInteractive::matchPosName(const QStringList& photoList, QStringList& posList)
{
	QString photoName;
	QStringList tmpPosList;
	QStringList photoNameList;
	foreach (QString photoPath, photoList)
		photoNameList.append(QFileInfo(photoPath).baseName());
	if (photoNameList.isEmpty())
		return;

	tmpPosList = posList;

	QgsMessageLog::logMessage(QString("ƥ���ع������ : \t��ʼƥ���ع������Ƭ����..."));

	for (int i=0; i<tmpPosList.size(); ++i)
	{
		int count = 0;
		QString posName = tmpPosList.at(i);
		foreach (const QString tmpPhotoName, photoNameList)
		{
			if (tmpPhotoName.contains(posName, Qt::CaseInsensitive))
			{
				photoName = tmpPhotoName;
				++count;
			}
		}
		if (count==0)	// ûƥ�䵽
		{
			int i = 0;
			while (i<posName.size())
			{
				if (posName.at(i).isNumber())
				{
					if (posName.at(i)==QChar('0'))
					{
						posName.remove(i, 1);
					}
					else
						break;
				}
				++i;
			}
			tmpPosList[i] = posName;
			--i;
		}
		else if (count==1) // ƥ�䵽һ��
		{
			QgsMessageLog::logMessage(QString("\t\tƥ�䵽�ع��: %1����Ƭ����: %2���Ϲ���, ���Զ������ع������.").arg(posList.at(i)).arg(photoName));
			posList[i] = photoName;
		}
		else				// ƥ�䵽���
		{
			if (posName.size() < photoName.size())
			{
				tmpPosList[i] = posName.insert(0, '0');
				--i;
			}
			else
				QgsMessageLog::logMessage(QString("\t\tδƥ�䵽�ع��: %1.").arg(posList.at(i)));
		}
	}
}

void uavPPInteractive::addChangedItem( const QString& item )
{
	mChangeList.append(item);
}

void uavPPInteractive::clearAllChangedItem()
{
	mChangeList.clear();
}

void uavPPInteractive::updata(QgsSymbolV2* v2)
{
	// ���Ŀǰͼ��ķ�����ʽ������Ⱦ��
	QgsCategorizedSymbolRendererV2* cRenderer;
	cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	if (!cRenderer)
	{
		initLayerCategorizedSymbolRendererV2();
		cRenderer = dynamic_cast< QgsCategorizedSymbolRendererV2* >( mLayer->rendererV2() );
	}

	foreach (QString str, mChangeList)
	{
		int index = cRenderer->categoryIndexForValue(QVariant(str));
		if (index != -1)
		{
			cRenderer->updateCategorySymbol(index, v2);
		}
	}

	UavMain::instance()->layerTreeView()->refreshLayerSymbology(mLayer->id());
	UavMain::instance()->refreshMapCanvas();
	clearAllChangedItem();
}
