// Actividad 5.2 Programación paralela y concurrente (Version secuencial)
// David Langarica Hernandez | A01708936
// Sebastian Flores Lemus | A01709229

#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;
using namespace std::chrono;

bool is_prime(int n) {
    if (n < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    high_resolution_clock::time_point start = high_resolution_clock::now();

    long long sum = 0;
    for (int i = 2; i < 5000000; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(end - start);

    cout << "Suma de primos secuencial: " << sum << endl;
    cout << "Tiempo secuencial: " << time_span.count() << " segundos." << endl;

    return 0;
}
