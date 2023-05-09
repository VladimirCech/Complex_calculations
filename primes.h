#ifndef PRIMES_H
#define PRIMES_H

#include <QObject>

class Primes : public QObject {
Q_OBJECT
public:
    void startPrimesCalculation(int number);
};

#endif // PRIMES_H
