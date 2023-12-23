#include "mainwindow.h"             // 11 вариант
#include "ui_mainwindow.h"

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

List work;
QString path;

void MainWindow::on_pushButton_2_clicked()
{


}
void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    work.clear();
    field ab;
    path = QFileDialog::getOpenFileName(this, "выберите файл", "C:/Users/kira1/OneDrive/Рабочий стол/файлы", "*.txt");
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
          QString info = file.readLine();
          QStringList infolist = info.split(" ");
          QString Name = infolist[0] + " " + infolist[1] + " " + infolist[2];
          QString math = infolist[3];
          QString physics = infolist[4];
          QString rus = infolist[5];
          ab.set(Name, math.toLongLong(), physics.toLongLong(), rus.toLongLong());
          work.push_back(ab);
        }
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
    }
    file.close();
    for(ll i = 0; i < work.size(); i++)
    {
        QString number = QString::number(work[i].get_number());
        QString time = QString::number(work[i].get_time());
        QString rate = QString::number(work[i].get_rate());
        ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->listWidget->clear();
    ll zpconst = ui->lineEdit_10->text().toLongLong();
    for(ll i = 0; i < work.size(); i++)
    {
        ll time = work[i].get_time();
        ll rate = work[i].get_rate();
        ll zp = 0;
        if(time > 144)
        {
            zp = rate * 144 + (time - 144) * 2 * rate;
        }
        else
        {
            zp = rate * time;
        }
        if(zp > zpconst)
        {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
        }
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->listWidget->clear();
    ll timeconst = ui->lineEdit_9->text().toLongLong();
    for(ll i = 0; i < work.size(); i++)
    {
        ll time = work[i].get_time();
        if(time > timeconst)
        {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
        }
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->listWidget->clear();
    for(ll i = 0; i < work.size(); i++)
    {
        ll time = work[i].get_time();
        if(time > 144)
        {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
        }
    }
}

bool check(QString name)
{
    ll x = 0;
    for(ll i = 0; i < name.length(); i++)
    {
        if(name[i] == ' ')
            x++;
    }
    if(x == 2)
        return 1;
    else
        return 0;
}
void MainWindow::on_pushButton_12_clicked()
{
     ui->listWidget->clear();
     QString name = ui->lineEdit_6->text();
     ll number = ui->lineEdit->text().toLongLong();
     ll time = ui->lineEdit_2->text().toLongLong();
     ll rate = ui->lineEdit_3->text().toLongLong();
     field ab;
     if(!number or !time or !rate or !check(name))
        QMessageBox::critical(this, "Ошибка", "Ввод");
     else
     {
     ab.set(name, number, time, rate);
     work.push_back(ab);
     }
     for(ll i = 0; i < work.size(); i++)
     {
             QString number = QString::number(work[i].get_number());
             QString time = QString::number(work[i].get_time());
             QString rate = QString::number(work[i].get_rate());
             ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
     }
}


void MainWindow::on_pushButton_9_clicked()
{
    if (ui->listWidget->currentRow() >= 0)
   work.erase(ui->listWidget->currentRow());
    else
        QMessageBox::critical(this, "Ошибка", "Удаление не выбранной строки");
     ui->listWidget->clear();
    for(ll i = 0; i < work.size(); i++)
    {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
    }
}
void MainWindow::on_pushButton_4_clicked()
{
    path = QFileDialog::getSaveFileName(this, "выберите файл", "C:/Users/kira1/OneDrive/Рабочий стол/файлы", "*.txt");
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        for(ll i = 0; i < ui->listWidget->count();i++)
        {
             QListWidgetItem *item = ui->listWidget->item(i);
            QTextStream out(&file);
            out << item->text();
        }
    }
}
bool cmpName(const field& ab1, const field& ab2) {
    QString str1 = ab1.get_name();
    QString str2 = ab2.get_name();
    for (int i = 0; i < ab1.get_name().length() and i < ab2.get_name().length(); i++)
    {
        if (str1[i].toLower() < str2[i].toLower())
            return true;
        if (str1[i].toLower() > str2[i].toLower())
            return false;
    }
    return false;
}
void MainWindow::on_pushButton_5_clicked()
{
    auto arr = new field[work.size()];
        for (ll i = 0; i < work.size(); i++)
        {
            arr[i] = work[i];
        }
        merge_sort(arr, work.size(), cmpName);
        ui->listWidget->clear();
        for(ll i = 0; i < work.size(); i++)
        {
                work[i] = arr[i];
                QString number = QString::number(work[i].get_number());
                QString time = QString::number(work[i].get_time());
                QString rate = QString::number(work[i].get_rate());
                ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
        }
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->listWidget->clear();
    for(ll i = 0; i < work.size(); i++)
    {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
    }
}
void MainWindow::on_pushButton_13_clicked()
{
        ui->listWidget->clear();
   QString key = ui->lineEdit_11->text();
    for(ll i = 0; i < work.size();i++)
    {
        if(work[i].get_name() == key or QString::number(work[i].get_number()) == key or QString::number(work[i].get_rate()) == key or QString::number(work[i].get_time()) == key)
        {
            QString number = QString::number(work[i].get_number());
            QString time = QString::number(work[i].get_time());
            QString rate = QString::number(work[i].get_rate());
            ui->listWidget->addItem(work[i].get_name() + " " + number + " " + time + " " + rate);
        }
    }
}
