#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include <QThread>
#include <QString>
#include "factorial.h"
#include "primes.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
    QThread factThread;
    QThread primesThread;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    Factorial *factorialCalculation;
    Primes *primesCalculation;

signals:
    void startFactCalculation(int value);
    void startPrimesCalculation(int value);
    void cancelFactCalculation();
    void cancelPrimesCalculation();
    void pauseFactCalculation();
    void pausePrimesCalculation();

private slots:

    void on_factCalculateButton_clicked();
    void on_primesCalculateButton_clicked();
    void on_factCancelButton_clicked();
    void on_primesCancelButton_clicked();
    void on_factPauseButton_clicked();
    void on_primesPauseButton_clicked();
    void on_factResultReady(QString result);
    void on_primesResultReady(QString result);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
