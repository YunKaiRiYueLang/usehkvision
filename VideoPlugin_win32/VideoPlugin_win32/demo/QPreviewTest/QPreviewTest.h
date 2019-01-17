#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QPreviewTest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include "./../public/include/VideoPlugin/VideoPlugin.h"

#ifdef _DEBUG
#pragma comment(lib, "./../public/lib/win32/VideoPlugin_D.lib")
#else
#pragma comment(lib, "./../public/lib/win32/VideoPlugin.lib")
#endif // DEBUG

class QPreviewTest : public QMainWindow
{
    Q_OBJECT

public:
    QPreviewTest(QWidget *parent = Q_NULLPTR);
    ~QPreviewTest();

private:
    Ui::QPreviewTestClass ui;

    void __initUi();
    void __initConnector();

private:
    void* m_pInstance = nullptr;
};
