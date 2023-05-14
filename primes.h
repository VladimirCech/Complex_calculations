#ifndef PRIMES_H
#define PRIMES_H

#include <QObject>
#include <QString>
#include <iostream>

class Primes : public QObject {
Q_OBJECT
public:
    void startPrimesCalculation(unsigned long long number);
    bool cancelFlag;
    bool pauseFlag;

public slots:

    void cancelPrimesCalculation();
    void pausePrimesCalculation();

signals:
    void primesCalculationResult(QString result);
    void progressValueChanged(int progress);
};

#endif // PRIMES_H
