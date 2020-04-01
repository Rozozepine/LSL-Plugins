/********************************************************************************
** Form generated from reading UI file 'lsl_plugin_prop.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LSL_PLUGIN_PROP_H
#define UI_LSL_PLUGIN_PROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LSLProperties
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QCheckBox *checkBoxRecord;
    QCheckBox *checkBoxStream;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QLabel *label;

    void setupUi(QDialog *LSLProperties)
    {
        if (LSLProperties->objectName().isEmpty())
            LSLProperties->setObjectName(QStringLiteral("LSLProperties"));
        LSLProperties->resize(411, 300);
        centralWidget = new QWidget(LSLProperties);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 20, 261, 45));
        checkBoxRecord = new QCheckBox(centralWidget);
        checkBoxRecord->setObjectName(QStringLiteral("checkBoxRecord"));
        checkBoxRecord->setGeometry(QRect(20, 80, 170, 43));
        checkBoxStream = new QCheckBox(centralWidget);
        checkBoxStream->setObjectName(QStringLiteral("checkBoxStream"));
        checkBoxStream->setGeometry(QRect(20, 140, 170, 43));
        pushButtonStart = new QPushButton(centralWidget);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(60, 230, 161, 51));
        pushButtonStop = new QPushButton(centralWidget);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(230, 230, 161, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(290, 20, 123, 37));

        retranslateUi(LSLProperties);

        QMetaObject::connectSlotsByName(LSLProperties);
    } // setupUi

    void retranslateUi(QDialog *LSLProperties)
    {
        LSLProperties->setWindowTitle(QApplication::translate("LSLProperties", "MainWindow", Q_NULLPTR));
        checkBoxRecord->setText(QApplication::translate("LSLProperties", "record", Q_NULLPTR));
        checkBoxStream->setText(QApplication::translate("LSLProperties", "Stream", Q_NULLPTR));
        pushButtonStart->setText(QApplication::translate("LSLProperties", "Start", Q_NULLPTR));
        pushButtonStop->setText(QApplication::translate("LSLProperties", "Stop", Q_NULLPTR));
        label->setText(QApplication::translate("LSLProperties", "id name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LSLProperties: public Ui_LSLProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LSL_PLUGIN_PROP_H
