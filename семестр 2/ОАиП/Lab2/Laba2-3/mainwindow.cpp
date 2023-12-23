#include "mainwindow.h"
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
void MainWindow::on_pushButton_clicked()
{
     string infix;
     string A = (ui->lineEdit->text()).toStdString();
     string B = (ui->lineEdit_2->text()).toStdString();
     string C = (ui->lineEdit_3->text()).toStdString();
     string D = (ui->lineEdit_4->text()).toStdString();
     string E = (ui->lineEdit_5->text()).toStdString();
     switch (ui->comboBox->currentIndex())
     {
         case 0:
         {
             infix = string(A + "/" + "(" + B + "-" + C + ")" + "*" + "(" + D + "+" + E + ")");
             break;
         }
         case 1:
         {
             infix = string("("+A+"+"+B+")"+"*"+"("+C+"-"+D+")"+"/"+E);
             break;
         }
         case 2:
         {
             infix = string (A+ "-" + "(" + B + "+" + C +"*"+D+")"+"/"+E);
             break;
         }
         case 3:
         {
            infix = string (A + "/" + B + "-" + "(" +"(" + C + "+" + D + ")" + "*" + E + ")");
             break;
         }
        case 4:
         {
            infix = string (A + "*" + "(" + B + "-" + C + "+" + D + ")/" + E);
            break;
         }
         case 5:
         {
         infix = string ( "(" + A + "+" + B + ")" + "*" + "(" + C + "-" + D + ")" + "/" + E);
         break;
         }
         case 6:
         {
             infix = string (A + "*" + "(" + B + "-" + C + ")" + "/" + "(" + D + "+" + E + ")");
             break;
         }
         case 7:
         {
             infix = string (A + "/" + "(" + B + "*" + "(" + C + "+" + D + ")" + ")" + "-" + E);
            break;
        }
        case 8:
         {
            infix = string("(" + A + "+(" + B + "/" + C + "-" + D + ")"  +")" + "*" + E);
            break;
         }
     case 9:
     {
         infix = string (A + "*(" + B + "+" + C + ")/(" + D + "-" + E + ")");
         break;
     }
     case 10:
     {
         infix = string (A + "-(" + B + "/" + C + "*(" + D + "+" + E + "))");
         break;
     }
     case 11:
     {
         infix = string ("(" + A + "-" + B + ")/(" + C + "+" + D + ")*" +E);
         break;
     }
     case 12:
     {
         infix = string(A + "/(" + B + "+" + C + "-" + D + "*" + E + ")");
         break;
     }
     case 13:
     {
         infix = string(A + "*(" + B + "-" + C + ")/(" + D + "+" + E + ")");
         break;
     }
     case 14:
     {
         infix = string("(" + A + "+" + B + "*" + C + ")/(" + D + "-" + E + ")");
         break;
     }
     }
     postfix *post = new postfix();
     ui->label_8->setText(QString::fromStdString(post->getPost(infix)));
     ui->label_9->setText(QString::number(post->result(infix),'g'));
}
void MainWindow::on_pushButton_2_clicked()
{
    postfix *post = new postfix();
      ui->label_11->setText(QString::number(post->result(ui->lineEdit_6->text().toStdString()),'g'));
}
