#include "mainwindow.h"
//#include "tests/test_subcipher.h"

#include <QApplication>
//#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTest::qExec(new test_subcipher);
    MainWindow w;
    w.show();
    return a.exec();
}
