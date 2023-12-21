#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solve.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
Solve slv;
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Show()
{
    ui->listWidget->clear();
    auto stacks = slv.Stacks();
    for (const auto &stack : stacks)
    {
        if (stack.size())
            ui->listWidget->addItem(stack);
        else
            ui->listWidget->addItem("null");
    }
}
void MainWindow::on_pushButton_create_clicked()
{
    slv.clear();
    slv.CreateRandom(-10, 10);
    Show();
}
void MainWindow::on_pushButton_removeNegative_clicked()
{
    slv.RemoveNegative();
    Show();
}
void MainWindow::on_pushButton_random_clicked()
{
    slv.clear();
    slv.CreateRandom(-50, 50);
    Show();
}
void MainWindow::on_pushButton_remove_clicked()
{
    bool ok;
    int key = ui->lineEdit_remove->text().toInt(&ok);
    if (ok)
    {
        slv.erase(key);
        Show();
    }
    else
    {
        ui->lineEdit_remove->clear();
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}
void MainWindow::on_pushButton_insert_clicked()
{
    bool ok;
    int key = ui->lineEdit_insert->text().toInt(&ok);
    if (ok)
    {
        slv.insert(key, 0);
        Show();
    }
    else
    {
        ui->lineEdit_insert->clear();
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}
void MainWindow::on_pushButton_clear_clicked()
{
    slv.clear();
    Show();
}
