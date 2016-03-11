#include "apc_annotation.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    APC_annotation w;
    w.setWindowTitle(QString::fromUtf8("MainWindow"));
    w.resize(450,300);
    w.start();
    return Qapp.exec();
}
