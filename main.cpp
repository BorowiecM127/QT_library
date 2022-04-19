#include "mainwindow.h"
#include "librarydbmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Biblioteka");
    w.show();
    return a.exec();
}
