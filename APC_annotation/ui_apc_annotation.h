/********************************************************************************
** Form generated from reading UI file 'apc_annotation.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APC_ANNOTATION_H
#define UI_APC_ANNOTATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_APC_annotationClass
{
public:

    void setupUi(QWidget *APC_annotationClass)
    {
        if (APC_annotationClass->objectName().isEmpty())
            APC_annotationClass->setObjectName(QString::fromUtf8("APC_annotationClass"));
        APC_annotationClass->resize(400, 300);

        retranslateUi(APC_annotationClass);

        QMetaObject::connectSlotsByName(APC_annotationClass);
    } // setupUi

    void retranslateUi(QWidget *APC_annotationClass)
    {
        APC_annotationClass->setWindowTitle(QApplication::translate("APC_annotationClass", "APC_annotation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class APC_annotationClass: public Ui_APC_annotationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APC_ANNOTATION_H
