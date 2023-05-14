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

//    Factorial connect functions
    connect(&factThread, &QThread::finished, factorialCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startFactCalculation, factorialCalculation, &Factorial::startFactCalculation);
    connect(this, &MainWindow::cancelFactCalculation, factorialCalculation, &Factorial::cancelFactCalculation,
            Qt::DirectConnection);
    connect(this, &MainWindow::pauseFactCalculation, factorialCalculation, &Factorial::pauseFactCalculation,
            Qt::DirectConnection);
    connect(factorialCalculation, &Factorial::factCalculationResult, this, &MainWindow::on_factResultReady);
    connect(factorialCalculation, &Factorial::progressValueChanged, ui->factProgressBar, &QProgressBar::setValue);

//    Primes connect functions
    connect(&primesThread, &QThread::finished, primesCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startPrimesCalculation, primesCalculation, &Primes::startPrimesCalculation);
    connect(primesCalculation, &Primes::primesCalculationResult, this, &MainWindow::on_primesResultReady);
    connect(primesCalculation, &Primes::progressValueChanged, ui->primesProgressBar, &QProgressBar::setValue);
    connect(this, &MainWindow::cancelPrimesCalculation, primesCalculation, &Primes::cancelPrimesCalculation,
            Qt::DirectConnection);
    connect(this, &MainWindow::pausePrimesCalculation, primesCalculation, &Primes::pausePrimesCalculation,
            Qt::DirectConnection);


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

void MainWindow::on_primesResultReady(QString result) {
    ui->primesOutput->insertPlainText(result);
    ui->primesPauseButton->setEnabled(false);
    ui->primesCancelButton->setEnabled(false);
}

void MainWindow::on_factCancelButton_clicked() {
    emit cancelFactCalculation();
    ui->factPauseButton->setEnabled(false);
    ui->factCancelButton->setEnabled(false);
    ui->factPauseButton->setText("Pozastavit");
}

void MainWindow::on_primesCancelButton_clicked() {
    emit cancelPrimesCalculation();
    ui->primesPauseButton->setEnabled(false);
    ui->primesCancelButton->setEnabled(false);
    ui->primesPauseButton->setText("Pozastavit");
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

void MainWindow::on_primesPauseButton_clicked() {
    QPushButton *pauseButton = ui->primesPauseButton;
    if (pauseButton->text() == "Pokračovat") {
        pauseButton->setText("Pozastavit");
    } else {
        pauseButton->setText("Pokračovat");
    }
    emit pausePrimesCalculation();
}

