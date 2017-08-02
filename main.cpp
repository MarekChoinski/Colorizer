#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSettings settings("MarekChoinski","Colorizer" );


        //qDebug()<<settings.value("pref/s_openAfterCoding").toInt();


        //settings.setValue("pref/s_openAfterCoding", 7);

        //qDebug()<<settings.contains("MarekChoinski");
        //qDebug()<<settings.contains("Colorizer");
        //qDebug()<<settings.contains("pref/s_useAlphaChannel");
        //qDebug()<<settings.contains("pref/s_openAfterCoding");


    w.show();

    return a.exec();
}
