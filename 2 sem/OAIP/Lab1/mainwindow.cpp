#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Дата" << "Следующий" << "Предыдущий" << "Высокосный?" << "Неделя" << "Разница");
}

MainWindow::~MainWindow()
{
    delete ui;
}

class Date
{
public:
    bool is_leap(int y)
    {
        return y % 4 == 0 and y % 100 != 0 or y % 400 == 0;
    }
    bool is_leaps()
    {
        return year % 4 == 0 and year % 100 != 0 or year % 400 == 0;
    }
    int max_day(int m, int y)
    {
        switch(m)
        {
        case 2:
            return 28 + is_leap(y);
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
        return 31;
        }
    }
        void NextDay()
        {
        if(day < max_day(month, year))
        ++day;
        else
        {
        day = 1;
        if(month < 12)
        ++month;
        else
        {
        month = 1;
        ++year;
        }
        }
        }
        void PreviousDay()
        {
            if(day>1)
                day--;
            else if (!(day>1) and month > 1)
            {
                month--;
                day= max_day(month,year);
            }
            else
            {
                month = 12;
                year--;
                day = max_day(month,year);
            }
        }
        short WeekNumber()
        {
            int d = day, m = month, y = year, x = 0;
            int i;
            int days = 0;
            for(i = 1; i < m; i++)
            {
                days+=max_day(i,y);
            }
            days+=d;
            if(days % 7 !=0)
            {
                days/=7;
                days++;
            }
            else
                days /=7;
            return days;
        }
        int Duration(Date date)
        {
            int dayx = day;
            int monthx = month;
            int yearx = year;
            int kol = 0;
            for(int i = yearx; i != date.year;)
            {
                if(i < date.year)
                {
                    kol+=365;
                    if(is_leap(i))
                            kol++;
                    i++;
                }
                else
                {
                    kol+=365;
                    if (is_leap(i))
                        kol++;
                    i--;
                }
            }
            while((dayx!=date.day) or (monthx != date.month))
            {
             kol++;
             if(monthx < date.month)
             {
                 date.PreviousDay();
             }
             else if(monthx > date.month)
             {
                 date.NextDay();
             }
             else
             {
                 if (dayx < date.day)
                 {
                     date.PreviousDay();
                 }
                 else if(dayx > date.day)
                 {
                     date.NextDay();
                 }
             }
            }
            return kol;
        }
        int DaysTillYourBirtday(Date date)
        {
            SYSTEMTIME t;
            GetLocalTime(&t);
            int dayx = t.wDay;
            int monthx = t.wMonth;
            int yearx = t.wYear;
            int kol = 0;
            for(int i = yearx; i != date.year;)
            {
                if(i < date.year)
                {
                    kol+=365;
                    if(is_leap(i))
                            kol++;
                    i++;
                }
                else
                {
                    kol+=365;
                    if (is_leap(i))
                        kol++;
                    i--;
                }
            }
            while((dayx!=date.day) or (monthx != date.month))
            {
             kol++;
             if(monthx < date.month)
             {
                 date.PreviousDay();
             }
             else if(monthx > date.month)
             {
                 date.NextDay();
             }
             else
             {
                 if (dayx < date.day)
                 {
                     date.PreviousDay();
                 }
                 else if(dayx > date.day)
                 {
                     date.NextDay();
                 }
             }
            }
            return kol;
        }
    private:
    int day;
    int month;
    int year;
public:
    void vvod(QString str)
    {
        std::string strr = str.toStdString();
        day = (strr[0] - 48)*10 + strr[1]-48;
        month = (strr[3]-48)*10+strr[4]-48;
        year = (strr[6]-48)*1000+(strr[7]-48)*100+(strr[8]-48)*10+strr[9]-48;
    }
    QString vivod()
    {
                  std::stringstream ss;
                  if(day<10)
                      ss<< "0";
                  ss << day << ".";
                  if(month<10)
                      ss<<"0";
                  ss << month << ".";
                  if(year<10)
                      ss<<"000";
                          else if(year<100)
                          ss<<"00";
                  else if(year<1000)
                   ss << "0";
                    ss << year;
                  std::string temp = ss.str();
         QString str = QString::fromStdString(temp);
         return str;
    }
};
int i = 0;
int j = 0;
   QString path;
   bool check = true;
void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    i = 0;
    j = 0;
    if(check)
   path = QFileDialog::getOpenFileName(this, "Выберите файл", "C:/Users/kira1/OneDrive/Рабочий стол/qt", "*.txt");
      QFile file (path);
   if(file.open(QIODevice::ReadOnly |QIODevice::Text))
      {
       Date a;
       Date b;
          while(!file.atEnd())
          {
            QTableWidgetItem *tblq;
              ui->tableWidget->insertRow(ui->tableWidget->rowCount());
              b = a;
              QString str = file.readLine();
              a.vvod(str);
            j = 0;
              tblq = new QTableWidgetItem(QString(a.vivod()));
              ui->tableWidget->setItem(i,j,tblq);
              if(i!=0)
              {
                  j = 5;
                  tblq = new QTableWidgetItem(QString::number(a.Duration(b)));
                ui->tableWidget->setItem(i,j,tblq);
              }
              j = 1;
              a.NextDay();
              tblq = new QTableWidgetItem(QString(a.vivod()));
              ui->tableWidget->setItem(i,j,tblq);
              j = 2;
              a.PreviousDay();
              a.PreviousDay();
              tblq = new QTableWidgetItem(QString(a.vivod()));
              ui->tableWidget->setItem(i,j,tblq);
              j = 3;
              a.NextDay();
              QString yes = "Да";
              QString no = "Нет";
                if(!a.is_leaps())
              {
                  tblq = new QTableWidgetItem(QString(no));
              }
              else
              {
                  tblq = new QTableWidgetItem(QString(yes));
              }
                ui->tableWidget->setItem(i,j,tblq);
                j = 4;
                int kol = a.WeekNumber();
                tblq = new QTableWidgetItem(QString::number(kol));
                ui->tableWidget->setItem(i,j,tblq);
              i++;

        }
   }
   check = true;
}
void MainWindow::on_pushButton_2_clicked()
{
SYSTEMTIME t;
GetLocalTime(&t);
    Date a;
    QString date = ui->lineEdit->text();
    a.vvod(date);
    int i = a.DaysTillYourBirtday(a);
if(date.isEmpty())
{
     QMessageBox::information(this, "ВАДИМ", "Введите дату в формате dd.mm.yyyy");
}
else
{
    QMessageBox::information(this, "ВАДИМ", QString::number(i));
}
}
void MainWindow::on_pushButton_3_clicked()
{
    QString str=ui->lineEdit->text();
    QFile file(path);
    if(file.open(QIODevice::Append))
    {
    QTextStream out(&file);
    out << str << "\n";
    }
        check=false;
    MainWindow::on_pushButton_clicked();
}
