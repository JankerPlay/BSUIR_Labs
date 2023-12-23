#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
        {
    ui->setupUi(this);
}
MainWindow::~MainWindow() {
    delete ui;
}
deque <int> d;
QString vivod()
{
    QString line;
    for (const auto &e1: d)
    {
        line += QString::number(e1) + " ";
    }
return line;
}
void MainWindow::on_pushButton_clicked()
{
    d.push_back(rand() % 25);
    ui->textBrowser->setText(vivod());
}
void MainWindow::on_pushButton_2_clicked()
{
    d.push_front(rand() % 25);
    ui->textBrowser->setText(vivod());
}
void MainWindow::on_pushButton_3_clicked()
{
    d.pop_back();
    ui->textBrowser->setText(vivod());
}
void MainWindow::on_pushButton_4_clicked()
{
    d.pop_front();
    ui->textBrowser->setText(vivod());
}
void MainWindow::on_pushButton_5_clicked()
{
    d.clear();
    ui->textBrowser->setText(vivod());
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser->setText(QString::number(d.capacity()));
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser->setText(QString::number(d.size()));
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->textBrowser->setText(d.empty() ? "True" : "False");
}

