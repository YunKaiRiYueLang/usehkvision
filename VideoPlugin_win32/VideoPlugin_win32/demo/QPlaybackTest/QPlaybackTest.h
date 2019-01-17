#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QPlaybackTest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include "./../public/include/VideoPlugin/VideoPlugin.h"

#ifdef _DEBUG
#pragma comment(lib, "./../public/lib/win32/VideoPlugin_D.lib")
#else
#pragma comment(lib, "./../public/lib/win32/VideoPlugin.lib")
#endif // DEBUG

class QPlaybackTest : public QMainWindow
{
    Q_OBJECT

public:
    QPlaybackTest(QWidget *parent = Q_NULLPTR);
    ~QPlaybackTest();

private:
    Ui::QPlaybackTestClass ui;
    void __initUi();
    void __initConnector();

private:
    void* m_pInstance = nullptr;
};
