#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    factorialCalculation = new Factorial();
    factorialCalculation->moveToThread(&factThread);
    factThread.start();

    connect(&factThread, &QThread::finished, factorialCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startFactCalculation, factorialCalculation, &Factorial::startFactCalculation);
    connect(factorialCalculation, &Factorial::factCalculationResult, this, &MainWindow::on_factResultReady);

}

MainWindow::~MainWindow() {
    delete ui;
    factThread.quit();
    factThread.wait();
}


void MainWindow::on_factCalculateButton_clicked() {
    QSpinBox *factInput = ui->factInput;
    int value = factInput->value();
    emit startFactCalculation(value);
    factResultTextField->clear();

}

void MainWindow::on_factResultReady(QString result) {
    factResultTextField->insertPlainText(result);
}

