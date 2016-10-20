/***************************************************************************
   uavstatusbarcoordinateswidget.h
    --------------------------------------
   Date                 : 05.08.2015
   Copyright            : (C) 2015 Denis Rouzaud
   Email                : denis.rouzaud@gmail.com
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#ifndef UAVSTATUSBARCOORDINATESWIDGET_H
#define UAVSTATUSBARCOORDINATESWIDGET_H


class QFont;
class QLabel;
class QLineEdit;
class QTimer;
class QToolButton;
class QValidator;

class QgsMapCanvas;
class QgsPoint;

#include <QWidget>

class APP_EXPORT UavStatusBarCoordinatesWidget : public QWidget
{
    Q_OBJECT

    enum CrsMode
    {
      MapCanvas,
      Custom
    };

  public:
    UavStatusBarCoordinatesWidget( QWidget *parent );

    //! �������������ĵ�ͼ����
    void setMapCanvas( QgsMapCanvas* mapCanvas );

    void setFont( const QFont& myFont );

    void setMouseCoordinatesPrecision( unsigned int precision );

  signals:
    void coordinatesChanged();

  private slots:
    void showMouseCoordinates( const QgsPoint &p );
	//! ��ͼ��Χ�л�
    void extentsViewToggled( bool theFlag );
	//! ������������������ͼ�������������������繦��
    void validateCoordinates();
    void dizzy();
    void showExtent();

  private:
    void refreshMapCanvas();

    QLineEdit *mLineEdit;
    QToolButton *mToggleExtentsViewButton;
    //! ��״̬������ʾ��ġ�����/�ȡ�
    QLabel *mLabel;

    QValidator *mCoordsEditValidator;
    QTimer *mDizzyTimer;
    QgsMapCanvas* mMapCanvas;

    //! С��λ������
    unsigned int mMousePrecisionDecimalPlaces;

};

#endif // UAVSTATUSBARCOORDINATESWIDGET_H
