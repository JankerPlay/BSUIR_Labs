#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector.cpp"
#include "pair.cpp"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


vector <vector<vector<pair<pair<123>,pair<123>>>>> a;
QString toString(const vector<int>& vec) {
    QString kal;
    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i]);
        kal.push_back(' ');
    }
    return kal;
}
QString toString(const vector<Pair<int, double>>& vec) {
    QString kal;

    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i].first) + " " + QString::number(vec[i].second);
        kal.push_back(' ');
    }
    return kal;
}
vector<Pair<vector<int>, vector<Pair<int, double>>>> matrix;
vector<int> firstNew;
vector<Pair<int, double>> secondNew;
vector<int> sequence;
void MainWindow::on_pushButton_clicked()
{
    firstNew.clear();
    secondNew.clear();
    firstNew.push_back(ui->lineEdit->text().toInt());
    secondNew.push_back(make_pair(ui->lineEdit_2->text().toInt(), ui->lineEdit_3->text().toDouble()));
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    matrix.push_back(make_pair(firstNew, secondNew));
    for (int i = 0; i < matrix.size(); ++i) {
        ui->textBrowser->append(toString(matrix[i].first));
        ui->textBrowser_2->append(toString(matrix[i].second));
    }
}


void MainWindow::on_pushButton_2_clicked()
{
     ui->textBrowser_3->clear();
     sequence.clear();
     std::string q = ui->lineEdit_4->text().toStdString();
     for(int i = 0; i < q.length();i++)
     {
        sequence.push_back((int)q[i] - 48);
     }
     ui->textBrowser_3->append(toString(sequence));
     vector<int> res;
        for (int i = 0; i < sequence.size(); i += 3) {
             vector<int> a;
             a.clear();
             if(sequence[i] >= 0)
             a.push_back(sequence[i]);
                          if(sequence[i + 1] >= 0)
             a.push_back(sequence[i + 1]);
                                       if(sequence[i + 2] >= 0)
             a.push_back(sequence[i + 2]);
             if (a.size() == 3) {
                int x = a[0] + a[1] + a[2] - std::max(a[0],std::max(a[1],a[2])) - std::min(a[0],std::min(a[1],a[2]));
            res.push_back(x);
             }
             else
             {
                 int average = 0;
                 for(int j = 0; j < a.size();j++)
                 {
                 average +=a[j];
                 }
                 res.push_back(average/a.size());
             }
        }
        ui->textBrowser_3->append(toString(res));
}

vector <int> cast;
void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser_4->clear();
    cast.clear();
    for(int i = 0; i < 20;i++)
    {
        cast.push_back(rand());
    }
    ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.capacity()));
    msgBox.exec();
}


void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.back()));
    msgBox.exec();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser_4->clear();
    cast.clear();
    ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(*cast.data()));
    msgBox.exec();
}


void MainWindow::on_pushButton_8_clicked()
{
    cast.emplace_back(stoi(ui->lineEdit_5->text().toStdString()));
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.empty()));
    msgBox.exec();
}


void MainWindow::on_pushButton_10_clicked()
{
int ind = ui->lineEdit_5->text().toInt();
auto it = cast.begin();
        for (int i = 0; i < ind; ++i) {
            it++;
        }
        cast.erase(it);
        ui->textBrowser_4->clear();
        ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_11_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.front()));
    msgBox.exec();
}


void MainWindow::on_pushButton_13_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.max_size()));
    msgBox.exec();
}


void MainWindow::on_pushButton_14_clicked()
{
    cast.pop_back();
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_16_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::number(cast.size()));
    msgBox.exec();
}


void MainWindow::on_pushButton_12_clicked()
{
    int ind = ui->lineEdit_6->text().toInt();
    auto it = cast.begin();
    for (int i = 0; i < ind; ++i) {
                it++;
            }
    cast.insert(it, ui->lineEdit_5->text().toInt());
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(toString(cast));
}


void MainWindow::on_pushButton_15_clicked()
{

}


void MainWindow::on_pushButton_17_clicked()
{

}

