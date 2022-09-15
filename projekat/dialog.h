#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <QDialog>
#include <QTimer>
#include <math.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    double function();
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QTimer *mytimer;
    const char PCF8591 = 0x48; // adresa
    int fd, adc;
    double volt;

    //double distance;
    double miss;

    double guessed_distance;
    double set_miss;
};
#endif // DIALOG_H
