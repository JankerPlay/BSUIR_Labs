#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solve.h"
#include <QMessageBox>
Solve tree;
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    QStringList headers;
    headers << "Номер" << "Имя";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    QVector<QString> names = {"Жук", "Ибрагим", "Мясоед", "Вадим", "Кирилд", "Егор", "Мамба", "Феня", "Августина",
                              "Катя", "Дима", "Коля"};
    for (int i = 0; i < names.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(names[i]));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ShowTree()
{
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(rootItem);
    tree.addNode(tree.root, rootItem);
}
void MainWindow::on_pushButton_clicked()
{
    tree.clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        tree.insert(ui->tableWidget->item(i, 0)->text().toInt(), ui->tableWidget->item(i, 1)->text());
    }
    ShowTree();
}
void MainWindow::on_pushButton_remove_clicked()
{
    tree.DeleteBranchWithKey(ui->lineEdit->text().toInt());
    ShowTree();
}
void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QMessageBox::information(this, "Значение", tree[item->text(column).toInt()]);

}
void MainWindow::on_pushButton_removeKey_clicked()
{
    tree.remove(ui->lineEdit_key->text().toInt());
    ShowTree();
}
QString preOrderOut;
QString postOrderOut;
QString inOrderOut;
void MainWindow::on_pushButton_preOrder_clicked()
{
    preOrderOut.clear();
    tree.preOrder();
    ui->textBrowser->setText(preOrderOut);
}
void MainWindow::on_pushButton_postOrder_clicked()
{
    postOrderOut.clear();
    tree.postOrder();
    ui->textBrowser->setText(postOrderOut);
}
void MainWindow::on_pushButton_order_clicked()
{
    inOrderOut.clear();
    tree.inOrder();
    ui->textBrowser->setText(inOrderOut);
}