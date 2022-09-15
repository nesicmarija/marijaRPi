#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    wiringPiSetup ();
    fd = wiringPiI2CSetup(PCF8591);
    mytimer=new QTimer(this);
    //connect(mytimer,SIGNAL(timeout()),this,SLOT(function()));
    //mytimer ->start(1000);

}

Dialog::~Dialog()
{
    delete ui;
}
double Dialog::function()
{
    double distance;

    wiringPiI2CReadReg8(fd, PCF8591 + 2) ; // dummy
    adc = wiringPiI2CReadReg8(fd, PCF8591 + 2) ;
    //ui->lcdADC->display(adc);
    volt=((double)adc*3.5)/256;
    ui->lcdVolt->display(volt);
    distance=29.988*pow(volt,-1.173);
    ui->lcdDistance->display(distance);
    return distance;
}

void Dialog::on_pushButton_clicked()
{
    double distance;
    distance = function();
    guessed_distance = ui->spinBox->value();
    set_miss = ui->spinBox_2->value();
    if(guessed_distance > distance)
    {
        miss = (1 - (distance/guessed_distance))*100;
    }
    else
    {
        miss = (1 - (guessed_distance/distance))*100;
    }
    if(miss < set_miss)
    {
        ui->label_7->setText("<font background-color = 'green'>Pogodak! :)");
        ui->label_7->setStyleSheet("QLabel {background-color: green; color: black");
    }
    else
    {
        ui->label_7->setText("Promasaj :(");
        ui->label_7->setStyleSheet("QLabel {background-color: red; color: black");
    }
    //ui->lcdNumber_2->display(guessed_distance);
    ui->lcdNumber->display(miss);
}
