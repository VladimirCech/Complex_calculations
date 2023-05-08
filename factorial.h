#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <QThread>
#include <QEventLoop>
#include <QTimer>

class Factorial : public QObject {
Q_OBJECT

signals:
    void factCalculationResult(QString result);
    int progressValueChanged(int progress);

public slots:
    void cancelFactCalculation();
    void pauseFactCalculation();

public:
    int fact(int x, int* ar, int ar_size);
    void startFactCalculation(int number);
    bool cancelFlag;
    bool pauseFlag;

private:

};

#endif // FACTORIAL_H
