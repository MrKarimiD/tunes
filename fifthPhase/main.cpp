#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(500,500);
    w.show();
    w.setWindowTitle(QApplication::translate("toplevel", "Tunes - Last Phase"));

    return a.exec();
}
