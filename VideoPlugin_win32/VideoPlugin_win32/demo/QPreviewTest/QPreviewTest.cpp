#include "QPreviewTest.h"

QPreviewTest::QPreviewTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    __initUi();
    __initConnector();
}

QPreviewTest::~QPreviewTest()
{
    if (m_pInstance != nullptr)
    {
        VideoPlugin_DestroyPluginInstance(m_pInstance);
        m_pInstance = nullptr;
    }
}

void QPreviewTest::__initUi()
{
    this->setFixedSize(840, 850);
    ui.m_pWidget->resize(840, 620);
    ui.m_pLETPort->setText(QString("80"));
    ui.m_pLETSnapDir->setText(QApplication::applicationDirPath() + "/SnapShot");

    ui.m_pCBLayout->addItem("1x1", 0);
    ui.m_pCBLayout->addItem("2x2", 1);
    ui.m_pCBLayout->addItem("3x3", 2);
    ui.m_pCBLayout->addItem("4x4", 3);
    ui.m_pCBLayout->setCurrentIndex(1);

    ui.m_pCBStreamType->addItem(QString::fromLocal8Bit("主码流"), 0);
    ui.m_pCBStreamType->addItem(QString::fromLocal8Bit("子码流"), 1);
    ui.m_pCBStreamType->setCurrentIndex(0);

    ui.m_pCBTransMode->addItem("UDP", 0);
    ui.m_pCBTransMode->addItem("TCP", 1);
    ui.m_pCBTransMode->setCurrentIndex(1);

    ui.m_pCBGpuMode->addItem(QString::fromLocal8Bit("不启用"), 0);
    ui.m_pCBGpuMode->addItem(QString::fromLocal8Bit("启用"), 1);
    ui.m_pCBGpuMode->setCurrentIndex(0);

    m_pInstance = VideoPlugin_CreatePluginInstance(reinterpret_cast<void*>(ui.m_pWidget->winId()));
}

void QPreviewTest::__initConnector()
{
    connect(ui.m_pBtnInit, &QPushButton::clicked, this, [this]() {
        QString qszAppkey = ui.m_pLETAppkey->text();
        if (qszAppkey.isEmpty())
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化appkey参数不能为空"));
            return;
        }

        QString qszSecret = ui.m_pLETSecret->text();
        if (qszSecret.isEmpty())
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化secret参数不能为空"));
            return;
        }

        QString qszIp = ui.m_pLETIp->text();
        if (qszIp.isEmpty())
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化ip参数不能为空"));
            return;
        }

        QString qszPort = ui.m_pLETPort->text();
        if (qszPort.isEmpty())
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化端口参数不能为空"));
            return;
        }

        bool bOk = true;
        int iPort = qszPort.toInt(&bOk, 10);
        if (!bOk)
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化端口参数不是有效值，请输入数字"));
            return;
        }

        if (iPort < 0 || iPort > 65535)
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：初始化端口参数需在0~65535范围内"));
            return;
        }

        QString qszLayout = ui.m_pCBLayout->currentText();

        QJsonObject obj;
        QJsonDocument doc;
        obj.insert("appkey", qszAppkey);
        obj.insert("secret", qszSecret);
        obj.insert("ip", qszIp);
        obj.insert("port", iPort);
        obj.insert("playMode", 0);
        obj.insert("layout", qszLayout);
        obj.insert("snapDir", ui.m_pLETSnapDir->text());
        doc.setObject(obj);

        QJsonObject objRoot;
        QJsonDocument docRoot;
        objRoot.insert("argument", doc.toJson(QJsonDocument::Compact).toStdString().c_str());
        objRoot.insert("funcName", "init");
        docRoot.setObject(objRoot);
        char* pszRet = VideoPlguin_GerneralRequest(m_pInstance, docRoot.toJson(QJsonDocument::Compact).toStdString().c_str());
        if (pszRet != nullptr)
        {
            ui.m_pEdtMsgTip->setText(QString(pszRet));
            delete[] pszRet;
        }
    });

    connect(ui.m_pBtnPreview, &QPushButton::clicked, this, [this] {
        QString qszCameraIndex = ui.m_pLETCameraIndex->text();
        if (qszCameraIndex.isEmpty())
        {
            ui.m_pEdtMsgTip->setText(QString::fromLocal8Bit("错误：开始回放监控点编号参数不能为空"));
            return;
        }

        QJsonObject obj;
        QJsonDocument doc;
        obj.insert("cameraIndexCode", qszCameraIndex);
        obj.insert("gpuMode", ui.m_pCBGpuMode->currentIndex());
        obj.insert("streamMode", ui.m_pCBStreamType->currentIndex());
        obj.insert("transMode", ui.m_pCBTransMode->currentIndex());
        doc.setObject(obj);

        QJsonObject objRoot;
        QJsonDocument docRoot;
        objRoot.insert("argument", doc.toJson(QJsonDocument::Compact).toStdString().c_str());
        objRoot.insert("funcName", "startPreview");
        docRoot.setObject(objRoot);
        char* pszRet = VideoPlguin_GerneralRequest(m_pInstance, docRoot.toJson(QJsonDocument::Compact).toStdString().c_str());
        if (pszRet != nullptr)
        {
            ui.m_pEdtMsgTip->setText(QString(pszRet));
            delete[] pszRet;
        }
    });

    connect(ui.m_pBtnStopAll, &QPushButton::clicked, this, [this] {
        QJsonObject objRoot;
        QJsonDocument docRoot;
        objRoot.insert("funcName", "stopAllPreview");
        docRoot.setObject(objRoot);
        char* pszRet = VideoPlguin_GerneralRequest(m_pInstance, docRoot.toJson(QJsonDocument::Compact).toStdString().c_str());
        if (pszRet != nullptr)
        {
            ui.m_pEdtMsgTip->setText(QString(pszRet));
            delete[] pszRet;
        }
    });

    connect(ui.m_pBtnUninit, &QPushButton::clicked, this, [this] {
        QJsonObject objRoot;
        QJsonDocument docRoot;
        objRoot.insert("funcName", "uninit");
        docRoot.setObject(objRoot);
        char* pszRet = VideoPlguin_GerneralRequest(m_pInstance, docRoot.toJson(QJsonDocument::Compact).toStdString().c_str());
        if (pszRet != nullptr)
        {
            ui.m_pEdtMsgTip->setText(QString(pszRet));
            delete[] pszRet;
        }
    });
}
