#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow ui;
    ui.show();
    return QApplication::exec();
}
