#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    factResultTextField = findChild<QPlainTextEdit *>("factOutput");
//    factResultTextField->moveToThread(&factThread);

    factorialCalculation = new Factorial();
    factorialCalculation->moveToThread(&factThread);
    factThread.start();

    connect(this, &MainWindow::startFactCalculation, factorialCalculation, &Factorial::startFactCalculation);
    connect(factorialCalculation, SIGNAL(factCalculationResult(QString)), this, SLOT(on_factResultReady(QString)));


}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_factCalculateButton_clicked() {
    QSpinBox *factInput = findChild<QSpinBox *>("factInput"); // získání pointeru na QSpinBox s názvem "spinBox"
    int value = factInput->value();
    emit startFactCalculation(value);
    factResultTextField->clear();

}

void MainWindow::on_factResultReady(QString result) {
    factResultTextField->insertPlainText(result);
}

