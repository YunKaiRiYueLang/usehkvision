#include "QPreviewTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPreviewTest w;
    w.show();
    return a.exec();
}
