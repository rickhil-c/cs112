#include <iostream>

using namespace std;

bool isPrime(int n);
void printPrimes(int N, int lower);
void primeFactors(int n);

int main() {
    int k;
    cin >> k;
    primeFactors(k);
    return 0;
}

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void primeFactors(int n) {
    if (isPrime(n)) {
        cout << n << " ";
        return;
    }

    for (int i = 2; i * i <= n; i++) {
        int j = n / i; 
        if (i * j == n) {
            primeFactors(i);
            primeFactors(j);
            cout << endl;
            return;
        }
    }
        
}

void printPrimes(int N, int lower = 0) {
    int l = 0;

    for (int i = lower; l < N; i++) {

        if (isPrime(i)) {
            cout << i << endl;
            l++;
        }
    }
}