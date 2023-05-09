#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->factProgressBar->reset();
    ui->primesProgressBar->reset();

    factorialCalculation = new Factorial();
    factorialCalculation->moveToThread(&factThread);
    factThread.start();

    primesCalculation = new Primes();
    primesCalculation->moveToThread(&primesThread);
    primesThread.start();

    connect(&factThread, &QThread::finished, factorialCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startFactCalculation, factorialCalculation, &Factorial::startFactCalculation);
    connect(this, &MainWindow::cancelFactCalculation, factorialCalculation, &Factorial::cancelFactCalculation,
            Qt::DirectConnection);
    connect(this, &MainWindow::pauseFactCalculation, factorialCalculation, &Factorial::pauseFactCalculation,
            Qt::DirectConnection);
    connect(factorialCalculation, &Factorial::factCalculationResult, this, &MainWindow::on_factResultReady);
    connect(factorialCalculation, &Factorial::progressValueChanged, ui->factProgressBar, &QProgressBar::setValue);


    connect(&primesThread, &QThread::finished, primesCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startPrimesCalculation, primesCalculation, &Primes::startPrimesCalculation);


}

MainWindow::~MainWindow() {
    on_factCancelButton_clicked();
    delete ui;
    factThread.quit();
    factThread.wait();

    primesThread.quit();
    primesThread.wait();
}


void MainWindow::on_factCalculateButton_clicked() {
    QSpinBox *factInput = ui->factInput;
    int value = factInput->value();
    emit startFactCalculation(value);
    ui->factOutput->clear();
    ui->factPauseButton->setEnabled(true);
    ui->factCancelButton->setEnabled(true);

}

void MainWindow::on_primesCalculateButton_clicked() {
    QSpinBox *primesInput = ui->primesInput;
    int value = primesInput->value();
    emit startPrimesCalculation(value);
    ui->primesOutput->clear();
    ui->primesPauseButton->setEnabled(true);
    ui->primesCancelButton->setEnabled(true);

}

void MainWindow::on_factResultReady(QString result) {
    ui->factOutput->insertPlainText(result);
    ui->factPauseButton->setEnabled(false);
    ui->factCancelButton->setEnabled(false);
}

void MainWindow::on_factCancelButton_clicked() {
    emit cancelFactCalculation();
    ui->factPauseButton->setEnabled(false);
    ui->factCancelButton->setEnabled(false);
    ui->factPauseButton->setText("Pozastavit");
}


void MainWindow::on_factPauseButton_clicked() {
    QPushButton *pauseButton = ui->factPauseButton;
    if (pauseButton->text() == "Pokračovat") {
        pauseButton->setText("Pozastavit");
    } else {
        pauseButton->setText("Pokračovat");
    }
    emit pauseFactCalculation();
}

