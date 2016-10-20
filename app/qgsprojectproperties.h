/***************************************************************************
                             qgsprojectproperties.h
       Set various project properties (inherits qgsprojectpropertiesbase)
                              -------------------
  begin                : May 18, 2004
  copyright            : (C) 2004 by Gary E.Sherman
  email                : sherman at mrcc.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "qgsoptionsdialogbase.h"
#include "ui_qgsprojectpropertiesbase.h"
#include "qgis.h"
#include "qgisgui.h"
#include "qgscontexthelp.h"

class QgsMapCanvas;
class QgsLayerTreeGroup;

/** Dialog to set project level properties

  @note actual state is stored in QgsProject singleton instance

 */
class APP_EXPORT QgsProjectProperties : public QgsOptionsDialogBase, private Ui::QgsProjectPropertiesBase
{
    Q_OBJECT

  public:
    //! ���캯��
    QgsProjectProperties( QgsMapCanvas* mapCanvas, QWidget *parent = nullptr, Qt::WindowFlags fl = QgisGui::ModalDialogFlags );

    //! ��������
    ~QgsProjectProperties();

    /** ��ȡ��ǰѡ���ĵ�ͼ��λ
     */
    QGis::UnitType mapUnits() const;

    /*!
     * ���õ�ͼ��λ
     */
    void setMapUnits( QGis::UnitType );

    /*!
       ÿ����Ŀ����һ������
     */
    QString title() const;
    void title( QString const & title );

    /** ��ʾ��ͶӰ���ؽ�ͨ */
    bool isProjected();

  public slots:
    /*!
     * Ӧ�ð�ť(slot)
     */
    void apply();

    /*!
     * �Ի�����ʾͶӰѡ���ʱ(slot)
     */
    void showProjectionsTab();

    /** ���û��ı�����ӵ���Ͽ�Ĺ�ģ����������Щȫ����Ŀʹ�ñ����б� */
    void on_pbnAddScale_clicked();

    /** ���û��ڹ�ģ��Ͽ򣬶�������Щȫ����Ŀʹ�ñ����б���ɾ����ģ */
    void on_pbnRemoveScale_clicked();

    /** ���û����ļ��м��ر��� */
    void on_pbnImportScales_clicked();

    /** ���û��������������ļ� */
    void on_pbnExportScales_clicked();

    /** A scale in the list of project scales changed ����Ŀ�߶ȵ��б�ı����߱仯*/
    void scaleItemChanged( QListWidgetItem* changedScaleItem );

    /*!
     * Slot to show the context help for this dialog
     */
    void on_buttonBox_helpRequested() { QgsContextHelp::run( metaObject()->className() ); }

    void on_cbxProjectionEnabled_toggled( bool onFlyEnabled );

    /*!
      * ����û�������CSS��������Ӧ�ĵ�ͼ��λ
      */
    void srIdUpdated();

    /* ������ѡ����µ��������µ�ComboBox����������ѡ������*/
    void updateEllipsoidUI( int newIndex );

    //! ������ȷ��������������ã�
    void projectionSelectorInitialized();

  signals:
    //! ����֪ͨ�����ʾ���ȿ����Ѿ��ı�
    void displayPrecisionChanged();

    //! ����֪ͨ������Ŀ�����б�����Ѿ��ı�
    void scalesChanged( const QStringList &scales = QStringList() );

    //! �û���֪��ˢ��
    void refresh();

  private:

    //! ������ʾ��ʽ
    enum CoordinateFormat
    {
      DecimalDegrees, /*!< ʮ���ƶ� */
      DegreesMinutes, /*!< ��, �� */
      DegreesMinutesSeconds, /*!< �ȣ��֣���*/
      MapUnits, /*! ��ʾ��ͼ���굥λ */
    };

    QgsMapCanvas* mMapCanvas;

    /*!
     * ����ǻ����Ի�״̬
     */
    void saveState();

    /*!
     * ���ָܻ��ǻ����Ի�״̬
     */
    void restoreState();

    long mProjectSrsId;
    long mLayerSrsId;

    // �б��е����������壬Ҳû�к��Զ���
    struct EllipsoidDefs
    {
      QString acronym;
      QString description;
      double semiMajor;
      double semiMinor;
    };
    QList<EllipsoidDefs> mEllipsoidList;
    int mEllipsoidIndex;

	//! ��SQLITE3 db������������б�
    void populateEllipsoidList();

    //! ����һ���µı��������������ӵ������б�
    QListWidgetItem* addScaleToScaleList( const QString &newScale );

	//! ���һ����������������б�
    void addScaleToScaleList( QListWidgetItem* newItem );

    static const char * GEO_NONE_DESC;

    void updateGuiForMapUnits( QGis::UnitType units );
};
