#include "primes.h"
#include <vector>
#include <QTimer>
#include <QEventLoop>


void Primes::startPrimesCalculation(unsigned long long number) {
    QString result = "";
    cancelFlag = false;
    pauseFlag = false;

    bool *numbers = new bool[number];
    std::fill_n(numbers, number, true);

    for (unsigned long long p = 2; p < number; p++) {
        int progress = (double) p / number * 100;
        emit progressValueChanged(progress);

        if (cancelFlag) break;

        while (pauseFlag) {
            QEventLoop loop;
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();
        }

        if (!numbers[p])
            continue;

//        std::cout << p << " ";
        result.append(QString::number(p));
        result.append(" ");

        if (p * p >= number)
            continue;

        for (unsigned long long i = p * p; i <= number; i += p) {
            numbers[i] = false;
        }

    }


    emit primesCalculationResult(result);

    delete[] numbers;

}

void Primes::cancelPrimesCalculation() {
    cancelFlag = true;
}

void Primes::pausePrimesCalculation() {
    pauseFlag = !pauseFlag;

}
