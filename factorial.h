#ifndef FACTORIAL_H
#define FACTORIAL_H


#include <QThread>
#include <QStringBuilder>

class Factorial : public QObject {
Q_OBJECT

signals:
    void factCalculationResult(QString result);

public slots:
//    void factCalculationResult(int number);

public:
    void factorial(int n);
    int fact(int x, int* ar, int ar_size);
    void startFactCalculation(int number);

};

#endif // FACTORIAL_H
