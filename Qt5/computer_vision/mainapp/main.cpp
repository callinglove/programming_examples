#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("fusion");
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
