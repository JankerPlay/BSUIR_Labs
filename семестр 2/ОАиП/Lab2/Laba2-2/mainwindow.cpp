#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
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


void MainWindow::on_pushButton_2_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выберите файл", "C:/Users/kira1/Desktop/файлы" , "*.txt");
    QFile file (path);
    QString str;
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream inn(&path);
        str = file.readAll();
    }
    ui->textEdit->setText(str);
}


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit->toPlainText();
    int rows = 1 ;
    int collums = 0;
    QString mas;
    bool check = 1;
    for (int i = 0; i < str.length(); i++)
       {
           if (str[i] == '\n')
           {
               rows++;
               collums = 0;
           }
           else
           {
               collums++;
           }
           if (str[i] == '(' or str[i] == '[' or str[i] == '{')
           {
               mas += str[i];
           }
           if (mas.isEmpty() and (str[i] == ')' or str[i] == ']' or str[i] == '}'))
           {
               check = 0;
               break;
           }
           if (str[i] == ')' or str[i] == ']' or str[i] == '}')
           {
               char temp;
               if (str[i] == ')')
                   temp = '(';
               else if (str[i] == ']')
                   temp = '[';
               else if (str[i] == '}')
                   temp = '{';
               bool checker = 0;
               for (int j = 0; j < mas.length(); j++)
               {
                   if (mas[j] == temp)
                   {
                       checker = 1;
                       mas.erase(mas.begin() + j, mas.begin() + j + 1);
                       break;
                   }
               }
               if (!checker)
               {
                   check = 0;
                   break;
               }
           }
       }
    if (!mas.isEmpty())
    {
        check = false;
    }
       if (!check)
       {
           QMessageBox::warning(this,"Ошибка","Строка: " +QString::number(rows)+ " Столбец: "+QString::number(collums));
       }
       else
       {
           QMessageBox::information(this,")","Все ок");
       }
       mas.clear();
}

