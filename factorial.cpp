#include "factorial.h"
#include <iostream>

using namespace std;
#define size 100000000

int Factorial::fact(int x, int *ar, int ar_size) {
    int c = 0;
    for (int i = 0; i < ar_size; i++) {
        if (cancelFlag) break;
        int p = ar[i] * x + c;
        ar[i] = p % 10;
        c = p / 10;
    }

    while (c) {
        if (cancelFlag) break;
        ar[ar_size] = c % 10;
        c = c / 10;
        ar_size++;
    }
    return ar_size;
}

void Factorial::startFactCalculation(int number) {
    QString result;
    cancelFlag = false;
    pauseFlag = false;
    int *ar = new int[size];
    ar[0] = 1;
    int ar_size = 1;

    for (int x = 2; x <= number; x++) {
        if (cancelFlag) break;
        ar_size = fact(x, ar, ar_size);
        while (pauseFlag) {
            QEventLoop loop;
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();

        }
        int progress = (double)x / number * 100;
        emit progressValueChanged(progress);
    }

    for (int i = ar_size - 1; i >= 0; i--) {
        if (cancelFlag) break;
        cout << ar[i];
        result.append(QString::number(ar[i]));
    }

    emit factCalculationResult(result);
    cout << endl;


    delete[] ar;
}

void Factorial::cancelFactCalculation() {
    cancelFlag = true;
}

void Factorial::pauseFactCalculation() {
    pauseFlag = !pauseFlag;

}