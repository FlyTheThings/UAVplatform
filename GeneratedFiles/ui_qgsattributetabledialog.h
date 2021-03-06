/********************************************************************************
** Form generated from reading UI file 'qgsattributetabledialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGSATTRIBUTETABLEDIALOG_H
#define UI_QGSATTRIBUTETABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "qgsdualview.h"
#include "qgsfieldexpressionwidget.h"
#include "qgsfilterlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QgsAttributeTableDialog
{
public:
    QAction *mActionAdvancedFilter;
    QAction *mActionShowAllFilter;
    QAction *mActionSelectedFilter;
    QAction *mActionVisibleFilter;
    QAction *mActionFilterColumnsMenu;
    QAction *mActionEditedFilter;
    QAction *mActionApplyFilter;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *mToggleEditingButton;
    QToolButton *mSaveEditsButton;
    QToolButton *mReloadButton;
    QFrame *line;
    QToolButton *mAddFeature;
    QToolButton *mDeleteSelectedButton;
    QFrame *line_2;
    QToolButton *mExpressionSelectButton;
    QToolButton *mSelectAllButton;
    QToolButton *mInvertSelectionButton;
    QToolButton *mRemoveSelectionButton;
    QToolButton *mSelectedToTopButton;
    QToolButton *mPanMapToSelectedRowsButton;
    QToolButton *mZoomMapToSelectedRowsButton;
    QToolButton *mCopySelectedRowsButton;
    QToolButton *mPasteFeatures;
    QFrame *line_3;
    QToolButton *mRemoveAttribute;
    QToolButton *mAddAttribute;
    QToolButton *mOpenFieldCalculator;
    QSpacerItem *horizontalSpacer;
    QToolButton *mSetStyles;
    QToolButton *mHelpButton;
    QgsDualView *mMainView;
    QHBoxLayout *hboxLayout;
    QToolButton *mFilterButton;
    QWidget *mFilterContainer;
    QGridLayout *mFilterLayout;
    QgsFilterLineEdit *mFilterQuery;
    QToolButton *mApplyFilterButton;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *mAttributeViewButton;
    QToolButton *mTableViewButton;
    QFrame *mUpdateExpressionBox;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *mFieldCombo;
    QLabel *label;
    QgsFieldExpressionWidget *mUpdateExpressionText;
    QToolButton *mRunFieldCalc;
    QToolButton *mRunFieldCalcSelected;
    QButtonGroup *mMainViewButtonGroup;

    void setupUi(QDialog *QgsAttributeTableDialog)
    {
        if (QgsAttributeTableDialog->objectName().isEmpty())
            QgsAttributeTableDialog->setObjectName(QString::fromUtf8("QgsAttributeTableDialog"));
        QgsAttributeTableDialog->resize(837, 570);
        mActionAdvancedFilter = new QAction(QgsAttributeTableDialog);
        mActionAdvancedFilter->setObjectName(QString::fromUtf8("mActionAdvancedFilter"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/themes/default/mActionFilter.png"), QSize(), QIcon::Normal, QIcon::Off);
        mActionAdvancedFilter->setIcon(icon);
        mActionShowAllFilter = new QAction(QgsAttributeTableDialog);
        mActionShowAllFilter->setObjectName(QString::fromUtf8("mActionShowAllFilter"));
        mActionShowAllFilter->setIcon(icon);
        mActionSelectedFilter = new QAction(QgsAttributeTableDialog);
        mActionSelectedFilter->setObjectName(QString::fromUtf8("mActionSelectedFilter"));
        mActionSelectedFilter->setIcon(icon);
        mActionVisibleFilter = new QAction(QgsAttributeTableDialog);
        mActionVisibleFilter->setObjectName(QString::fromUtf8("mActionVisibleFilter"));
        mActionVisibleFilter->setIcon(icon);
        mActionFilterColumnsMenu = new QAction(QgsAttributeTableDialog);
        mActionFilterColumnsMenu->setObjectName(QString::fromUtf8("mActionFilterColumnsMenu"));
        mActionEditedFilter = new QAction(QgsAttributeTableDialog);
        mActionEditedFilter->setObjectName(QString::fromUtf8("mActionEditedFilter"));
        mActionEditedFilter->setIcon(icon);
        mActionApplyFilter = new QAction(QgsAttributeTableDialog);
        mActionApplyFilter->setObjectName(QString::fromUtf8("mActionApplyFilter"));
        gridLayout = new QGridLayout(QgsAttributeTableDialog);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 0);
        mToggleEditingButton = new QToolButton(QgsAttributeTableDialog);
        mToggleEditingButton->setObjectName(QString::fromUtf8("mToggleEditingButton"));
        mToggleEditingButton->setIconSize(QSize(18, 18));
        mToggleEditingButton->setCheckable(false);
        mToggleEditingButton->setAutoRaise(true);

        horizontalLayout->addWidget(mToggleEditingButton);

        mSaveEditsButton = new QToolButton(QgsAttributeTableDialog);
        mSaveEditsButton->setObjectName(QString::fromUtf8("mSaveEditsButton"));
        mSaveEditsButton->setIconSize(QSize(18, 18));
        mSaveEditsButton->setCheckable(false);
        mSaveEditsButton->setAutoRaise(true);

        horizontalLayout->addWidget(mSaveEditsButton);

        mReloadButton = new QToolButton(QgsAttributeTableDialog);
        mReloadButton->setObjectName(QString::fromUtf8("mReloadButton"));
        mReloadButton->setIconSize(QSize(18, 18));
        mReloadButton->setCheckable(false);
        mReloadButton->setAutoRaise(true);

        horizontalLayout->addWidget(mReloadButton);

        line = new QFrame(QgsAttributeTableDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        mAddFeature = new QToolButton(QgsAttributeTableDialog);
        mAddFeature->setObjectName(QString::fromUtf8("mAddFeature"));
        mAddFeature->setEnabled(false);
        mAddFeature->setIconSize(QSize(18, 18));
        mAddFeature->setAutoRaise(true);

        horizontalLayout->addWidget(mAddFeature);

        mDeleteSelectedButton = new QToolButton(QgsAttributeTableDialog);
        mDeleteSelectedButton->setObjectName(QString::fromUtf8("mDeleteSelectedButton"));
        mDeleteSelectedButton->setIconSize(QSize(18, 18));
        mDeleteSelectedButton->setAutoRaise(true);

        horizontalLayout->addWidget(mDeleteSelectedButton);

        line_2 = new QFrame(QgsAttributeTableDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        mExpressionSelectButton = new QToolButton(QgsAttributeTableDialog);
        mExpressionSelectButton->setObjectName(QString::fromUtf8("mExpressionSelectButton"));
        mExpressionSelectButton->setIconSize(QSize(18, 18));
        mExpressionSelectButton->setAutoRaise(true);

        horizontalLayout->addWidget(mExpressionSelectButton);

        mSelectAllButton = new QToolButton(QgsAttributeTableDialog);
        mSelectAllButton->setObjectName(QString::fromUtf8("mSelectAllButton"));
        mSelectAllButton->setIconSize(QSize(18, 18));
        mSelectAllButton->setAutoRaise(true);

        horizontalLayout->addWidget(mSelectAllButton);

        mInvertSelectionButton = new QToolButton(QgsAttributeTableDialog);
        mInvertSelectionButton->setObjectName(QString::fromUtf8("mInvertSelectionButton"));
        mInvertSelectionButton->setIconSize(QSize(18, 18));
        mInvertSelectionButton->setAutoRaise(true);

        horizontalLayout->addWidget(mInvertSelectionButton);

        mRemoveSelectionButton = new QToolButton(QgsAttributeTableDialog);
        mRemoveSelectionButton->setObjectName(QString::fromUtf8("mRemoveSelectionButton"));
        mRemoveSelectionButton->setIconSize(QSize(18, 18));
        mRemoveSelectionButton->setAutoRaise(true);

        horizontalLayout->addWidget(mRemoveSelectionButton);

        mSelectedToTopButton = new QToolButton(QgsAttributeTableDialog);
        mSelectedToTopButton->setObjectName(QString::fromUtf8("mSelectedToTopButton"));
        mSelectedToTopButton->setIconSize(QSize(18, 18));
        mSelectedToTopButton->setCheckable(true);
        mSelectedToTopButton->setAutoRaise(true);

        horizontalLayout->addWidget(mSelectedToTopButton);

        mPanMapToSelectedRowsButton = new QToolButton(QgsAttributeTableDialog);
        mPanMapToSelectedRowsButton->setObjectName(QString::fromUtf8("mPanMapToSelectedRowsButton"));
        mPanMapToSelectedRowsButton->setIconSize(QSize(18, 18));
        mPanMapToSelectedRowsButton->setAutoRaise(true);

        horizontalLayout->addWidget(mPanMapToSelectedRowsButton);

        mZoomMapToSelectedRowsButton = new QToolButton(QgsAttributeTableDialog);
        mZoomMapToSelectedRowsButton->setObjectName(QString::fromUtf8("mZoomMapToSelectedRowsButton"));
        mZoomMapToSelectedRowsButton->setIconSize(QSize(18, 18));
        mZoomMapToSelectedRowsButton->setAutoRaise(true);

        horizontalLayout->addWidget(mZoomMapToSelectedRowsButton);

        mCopySelectedRowsButton = new QToolButton(QgsAttributeTableDialog);
        mCopySelectedRowsButton->setObjectName(QString::fromUtf8("mCopySelectedRowsButton"));
        mCopySelectedRowsButton->setIconSize(QSize(18, 18));
        mCopySelectedRowsButton->setAutoRaise(true);

        horizontalLayout->addWidget(mCopySelectedRowsButton);

        mPasteFeatures = new QToolButton(QgsAttributeTableDialog);
        mPasteFeatures->setObjectName(QString::fromUtf8("mPasteFeatures"));
        mPasteFeatures->setIconSize(QSize(18, 18));
        mPasteFeatures->setAutoRaise(true);

        horizontalLayout->addWidget(mPasteFeatures);

        line_3 = new QFrame(QgsAttributeTableDialog);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        mRemoveAttribute = new QToolButton(QgsAttributeTableDialog);
        mRemoveAttribute->setObjectName(QString::fromUtf8("mRemoveAttribute"));
        mRemoveAttribute->setIconSize(QSize(18, 18));
        mRemoveAttribute->setAutoRaise(true);

        horizontalLayout->addWidget(mRemoveAttribute);

        mAddAttribute = new QToolButton(QgsAttributeTableDialog);
        mAddAttribute->setObjectName(QString::fromUtf8("mAddAttribute"));
        mAddAttribute->setIconSize(QSize(18, 18));
        mAddAttribute->setAutoRaise(true);

        horizontalLayout->addWidget(mAddAttribute);

        mOpenFieldCalculator = new QToolButton(QgsAttributeTableDialog);
        mOpenFieldCalculator->setObjectName(QString::fromUtf8("mOpenFieldCalculator"));
        mOpenFieldCalculator->setIconSize(QSize(18, 18));
        mOpenFieldCalculator->setAutoRaise(true);

        horizontalLayout->addWidget(mOpenFieldCalculator);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mSetStyles = new QToolButton(QgsAttributeTableDialog);
        mSetStyles->setObjectName(QString::fromUtf8("mSetStyles"));
        mSetStyles->setCheckable(true);
        mSetStyles->setAutoRepeat(false);
        mSetStyles->setAutoRaise(true);

        horizontalLayout->addWidget(mSetStyles);

        mHelpButton = new QToolButton(QgsAttributeTableDialog);
        mHelpButton->setObjectName(QString::fromUtf8("mHelpButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mHelpButton->sizePolicy().hasHeightForWidth());
        mHelpButton->setSizePolicy(sizePolicy);
        mHelpButton->setMinimumSize(QSize(0, 0));
        mHelpButton->setAutoRaise(true);

        horizontalLayout->addWidget(mHelpButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        mMainView = new QgsDualView(QgsAttributeTableDialog);
        mMainView->setObjectName(QString::fromUtf8("mMainView"));

        gridLayout->addWidget(mMainView, 7, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(3, 0, 3, 3);
        mFilterButton = new QToolButton(QgsAttributeTableDialog);
        mFilterButton->setObjectName(QString::fromUtf8("mFilterButton"));
        mFilterButton->setPopupMode(QToolButton::MenuButtonPopup);
        mFilterButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        hboxLayout->addWidget(mFilterButton);

        mFilterContainer = new QWidget(QgsAttributeTableDialog);
        mFilterContainer->setObjectName(QString::fromUtf8("mFilterContainer"));
        mFilterLayout = new QGridLayout(mFilterContainer);
        mFilterLayout->setContentsMargins(0, 0, 0, 0);
        mFilterLayout->setObjectName(QString::fromUtf8("mFilterLayout"));
        mFilterLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        mFilterQuery = new QgsFilterLineEdit(mFilterContainer);
        mFilterQuery->setObjectName(QString::fromUtf8("mFilterQuery"));

        mFilterLayout->addWidget(mFilterQuery, 0, 0, 1, 1);


        hboxLayout->addWidget(mFilterContainer);

        mApplyFilterButton = new QToolButton(QgsAttributeTableDialog);
        mApplyFilterButton->setObjectName(QString::fromUtf8("mApplyFilterButton"));
        mApplyFilterButton->setToolButtonStyle(Qt::ToolButtonTextOnly);

        hboxLayout->addWidget(mApplyFilterButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mAttributeViewButton = new QToolButton(QgsAttributeTableDialog);
        mMainViewButtonGroup = new QButtonGroup(QgsAttributeTableDialog);
        mMainViewButtonGroup->setObjectName(QString::fromUtf8("mMainViewButtonGroup"));
        mMainViewButtonGroup->addButton(mAttributeViewButton);
        mAttributeViewButton->setObjectName(QString::fromUtf8("mAttributeViewButton"));
        mAttributeViewButton->setCheckable(true);

        horizontalLayout_2->addWidget(mAttributeViewButton);

        mTableViewButton = new QToolButton(QgsAttributeTableDialog);
        mMainViewButtonGroup->addButton(mTableViewButton);
        mTableViewButton->setObjectName(QString::fromUtf8("mTableViewButton"));
        mTableViewButton->setCheckable(true);
        mTableViewButton->setChecked(true);

        horizontalLayout_2->addWidget(mTableViewButton);


        hboxLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(hboxLayout, 9, 0, 1, 1);

        mUpdateExpressionBox = new QFrame(QgsAttributeTableDialog);
        mUpdateExpressionBox->setObjectName(QString::fromUtf8("mUpdateExpressionBox"));
        horizontalLayout_3 = new QHBoxLayout(mUpdateExpressionBox);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(3, 1, 0, 3);
        mFieldCombo = new QComboBox(mUpdateExpressionBox);
        mFieldCombo->setObjectName(QString::fromUtf8("mFieldCombo"));

        horizontalLayout_3->addWidget(mFieldCombo);

        label = new QLabel(mUpdateExpressionBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        mUpdateExpressionText = new QgsFieldExpressionWidget(mUpdateExpressionBox);
        mUpdateExpressionText->setObjectName(QString::fromUtf8("mUpdateExpressionText"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mUpdateExpressionText->sizePolicy().hasHeightForWidth());
        mUpdateExpressionText->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(mUpdateExpressionText);

        mRunFieldCalc = new QToolButton(mUpdateExpressionBox);
        mRunFieldCalc->setObjectName(QString::fromUtf8("mRunFieldCalc"));

        horizontalLayout_3->addWidget(mRunFieldCalc);

        mRunFieldCalcSelected = new QToolButton(mUpdateExpressionBox);
        mRunFieldCalcSelected->setObjectName(QString::fromUtf8("mRunFieldCalcSelected"));

        horizontalLayout_3->addWidget(mRunFieldCalcSelected);


        gridLayout->addWidget(mUpdateExpressionBox, 6, 0, 1, 1);

        QWidget::setTabOrder(mToggleEditingButton, mSaveEditsButton);
        QWidget::setTabOrder(mSaveEditsButton, mReloadButton);
        QWidget::setTabOrder(mReloadButton, mAddFeature);
        QWidget::setTabOrder(mAddFeature, mDeleteSelectedButton);
        QWidget::setTabOrder(mDeleteSelectedButton, mExpressionSelectButton);
        QWidget::setTabOrder(mExpressionSelectButton, mRemoveSelectionButton);
        QWidget::setTabOrder(mRemoveSelectionButton, mSelectAllButton);
        QWidget::setTabOrder(mSelectAllButton, mSelectedToTopButton);
        QWidget::setTabOrder(mSelectedToTopButton, mInvertSelectionButton);
        QWidget::setTabOrder(mInvertSelectionButton, mPanMapToSelectedRowsButton);
        QWidget::setTabOrder(mPanMapToSelectedRowsButton, mZoomMapToSelectedRowsButton);
        QWidget::setTabOrder(mZoomMapToSelectedRowsButton, mCopySelectedRowsButton);
        QWidget::setTabOrder(mCopySelectedRowsButton, mPasteFeatures);
        QWidget::setTabOrder(mPasteFeatures, mRemoveAttribute);
        QWidget::setTabOrder(mRemoveAttribute, mAddAttribute);
        QWidget::setTabOrder(mAddAttribute, mOpenFieldCalculator);
        QWidget::setTabOrder(mOpenFieldCalculator, mSetStyles);
        QWidget::setTabOrder(mSetStyles, mHelpButton);
        QWidget::setTabOrder(mHelpButton, mFieldCombo);
        QWidget::setTabOrder(mFieldCombo, mRunFieldCalc);
        QWidget::setTabOrder(mRunFieldCalc, mRunFieldCalcSelected);
        QWidget::setTabOrder(mRunFieldCalcSelected, mFilterButton);
        QWidget::setTabOrder(mFilterButton, mFilterQuery);
        QWidget::setTabOrder(mFilterQuery, mApplyFilterButton);
        QWidget::setTabOrder(mApplyFilterButton, mAttributeViewButton);
        QWidget::setTabOrder(mAttributeViewButton, mTableViewButton);

        retranslateUi(QgsAttributeTableDialog);
        QObject::connect(mToggleEditingButton, SIGNAL(toggled(bool)), mSaveEditsButton, SLOT(setEnabled(bool)));
        QObject::connect(mMainViewButtonGroup, SIGNAL(buttonClicked(int)), mMainView, SLOT(setCurrentIndex(int)));
        QObject::connect(mToggleEditingButton, SIGNAL(toggled(bool)), mReloadButton, SLOT(setDisabled(bool)));

        mMainView->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QgsAttributeTableDialog);
    } // setupUi

    void retranslateUi(QDialog *QgsAttributeTableDialog)
    {
        QgsAttributeTableDialog->setWindowTitle(QApplication::translate("QgsAttributeTableDialog", "Attribute Table", 0, QApplication::UnicodeUTF8));
        mActionAdvancedFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Advanced Filter (Expression)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mActionAdvancedFilter->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Use the Expression Builder to define the filter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mActionAdvancedFilter->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        mActionShowAllFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Show All Features", 0, QApplication::UnicodeUTF8));
        mActionSelectedFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Show Selected Features", 0, QApplication::UnicodeUTF8));
        mActionVisibleFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Show Features Visible On Map", 0, QApplication::UnicodeUTF8));
        mActionFilterColumnsMenu->setText(QApplication::translate("QgsAttributeTableDialog", "Field Filter", 0, QApplication::UnicodeUTF8));
        mActionEditedFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Show Edited and New Features", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mActionEditedFilter->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Filter all the features which have been edited but not yet saved", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mActionApplyFilter->setText(QApplication::translate("QgsAttributeTableDialog", "Apply", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mToggleEditingButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Toggle editing mode (Ctrl+E)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mToggleEditingButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mToggleEditingButton->setText(QString());
        mToggleEditingButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+E", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSaveEditsButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Save Edits (Ctrl+S)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mSaveEditsButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mSaveEditsButton->setText(QString());
        mSaveEditsButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+S", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mReloadButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Reload the table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mReloadButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        mAddFeature->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Add feature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mAddFeature->setText(QString());
#ifndef QT_NO_TOOLTIP
        mDeleteSelectedButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Delete selected features (DEL)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mDeleteSelectedButton->setText(QApplication::translate("QgsAttributeTableDialog", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mExpressionSelectButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Select features using an expression", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mExpressionSelectButton->setText(QApplication::translate("QgsAttributeTableDialog", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSelectAllButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Select all (Ctrl+A)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mSelectAllButton->setText(QString());
        mSelectAllButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+A", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mInvertSelectionButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Invert selection (Ctrl+R)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mInvertSelectionButton->setText(QString());
        mInvertSelectionButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+R", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mRemoveSelectionButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Deselect all (Ctrl+Shift+A)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mRemoveSelectionButton->setText(QString());
        mRemoveSelectionButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSelectedToTopButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Move selection to top (Ctrl+T)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mSelectedToTopButton->setText(QString());
        mSelectedToTopButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+T", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mPanMapToSelectedRowsButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Pan map to the selected rows (Ctrl+P)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mPanMapToSelectedRowsButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mPanMapToSelectedRowsButton->setText(QString());
        mPanMapToSelectedRowsButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+P", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mZoomMapToSelectedRowsButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Zoom map to the selected rows (Ctrl+J)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mZoomMapToSelectedRowsButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mZoomMapToSelectedRowsButton->setText(QString());
        mZoomMapToSelectedRowsButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+J", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mCopySelectedRowsButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Copy selected rows to clipboard (Ctrl+C)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mCopySelectedRowsButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mCopySelectedRowsButton->setText(QString());
        mCopySelectedRowsButton->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+C", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mPasteFeatures->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Paste features from clipboard (Ctrl+V)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mPasteFeatures->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        mPasteFeatures->setText(QString());
        mPasteFeatures->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mRemoveAttribute->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Delete field (Ctrl+L)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mRemoveAttribute->setText(QString());
        mRemoveAttribute->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+L", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mAddAttribute->setToolTip(QApplication::translate("QgsAttributeTableDialog", "New field (Ctrl+W)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mAddAttribute->setText(QString());
        mAddAttribute->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+W", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mOpenFieldCalculator->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Open field calculator (Ctrl+I)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mOpenFieldCalculator->setText(QString());
        mOpenFieldCalculator->setShortcut(QApplication::translate("QgsAttributeTableDialog", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        mSetStyles->setText(QApplication::translate("QgsAttributeTableDialog", "Cond", 0, QApplication::UnicodeUTF8));
        mHelpButton->setText(QApplication::translate("QgsAttributeTableDialog", "?", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mFilterButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "The filter defines which features are currently shown in the list or on the table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mFilterButton->setText(QApplication::translate("QgsAttributeTableDialog", "Filter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mApplyFilterButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Filters the visible features according to the current filter selection and filter string.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mApplyFilterButton->setText(QApplication::translate("QgsAttributeTableDialog", "Apply", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mAttributeViewButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Switch to form view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mAttributeViewButton->setText(QApplication::translate("QgsAttributeTableDialog", "Form View", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mTableViewButton->setToolTip(QApplication::translate("QgsAttributeTableDialog", "Switch to table view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mTableViewButton->setText(QApplication::translate("QgsAttributeTableDialog", "Table View", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QgsAttributeTableDialog", "=", 0, QApplication::UnicodeUTF8));
        mRunFieldCalc->setText(QApplication::translate("QgsAttributeTableDialog", "Update All", 0, QApplication::UnicodeUTF8));
        mRunFieldCalcSelected->setText(QApplication::translate("QgsAttributeTableDialog", "Update Selected", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QgsAttributeTableDialog: public Ui_QgsAttributeTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGSATTRIBUTETABLEDIALOG_H
