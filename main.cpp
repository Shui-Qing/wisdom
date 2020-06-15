#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/new/prefix1/setqstylesheet.qss");
    if (!qss.open(QFile::ReadOnly))
        qDebug()<<"No file found.";
    else
        qApp->setStyleSheet(qss.readAll());
    qss.close();

    Widget w;
    w.show();

    return a.exec();
}
