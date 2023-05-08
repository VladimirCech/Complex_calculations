#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    factResultTextField = ui->factOutput;
    ui->factProgressBar->reset();
    ui->primeProgressBar->reset();

    factorialCalculation = new Factorial();
    factorialCalculation->moveToThread(&factThread);
    factThread.start();

    connect(&factThread, &QThread::finished, factorialCalculation, &QObject::deleteLater);
    connect(this, &MainWindow::startFactCalculation, factorialCalculation, &Factorial::startFactCalculation);
    connect(this, &MainWindow::cancelFactCalculation, factorialCalculation, &Factorial::cancelFactCalculation,
            Qt::DirectConnection);
    connect(this, &MainWindow::pauseFactCalculation, factorialCalculation, &Factorial::pauseFactCalculation,
            Qt::DirectConnection);
    connect(factorialCalculation, &Factorial::factCalculationResult, this, &MainWindow::on_factResultReady);
    connect(factorialCalculation, &Factorial::progressValueChanged, ui->factProgressBar, &QProgressBar::setValue);


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
    ui->factPauseButton->setEnabled(true);
    ui->factCancelButton->setEnabled(true);

}

void MainWindow::on_factResultReady(QString result) {
    factResultTextField->insertPlainText(result);
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

