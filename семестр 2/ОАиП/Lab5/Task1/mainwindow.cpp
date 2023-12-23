#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ans.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
ans answer;
void MainWindow::on_pushButton_clicked()
{
    answer.create();
    ui->textBrowser->setText(answer.tostr());
}
void MainWindow::on_pushButton_2_clicked()
{
answer.task();
ui->textBrowser->setText(answer.tostr());
}

