#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include <QThread>
#include <QString>
#include "factorial.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
    QThread factThread;
    QThread primeThread;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    Factorial *factorialCalculation;
    QPlainTextEdit *factResultTextField = ui->factOutput;
    QPushButton *factPauseButton = ui->factPauseButton;
    QPushButton *factContinueButton = ui->factCancelButton;

signals:
    void startFactCalculation(int value);

private slots:

    void on_factCalculateButton_clicked();
    void on_factResultReady(QString result);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
