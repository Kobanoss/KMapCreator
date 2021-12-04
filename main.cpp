#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {

    // Создание и вызов окна
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
