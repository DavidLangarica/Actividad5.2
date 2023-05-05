// Actividad 5.2 Programación paralela y concurrente (Version paralelo)
// David Langarica Hernandez | A01708936
// Sebastian Flores Lemus | A01709229

#include <pthread.h>

#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

const int NUM_THREADS = 8;
const int UPPER_LIMIT = 5000000;

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

void* calculate_prime_sum(void* param) {
    long long* local_sum = new long long;
    *local_sum = 0;
    int thread_id = *((int*)param);

    int start = 2 + thread_id * (UPPER_LIMIT - 2) / NUM_THREADS;
    int end = 2 + (thread_id + 1) * (UPPER_LIMIT - 2) / NUM_THREADS;

    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            *local_sum += i;
        }
    }

    pthread_exit((void*)local_sum);
}

int main() {
    clock_t start = clock();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculate_prime_sum, (void*)&thread_ids[i]);
    }

    long long sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        void* partial_sum;
        pthread_join(threads[i], &partial_sum);
        sum += *((long long*)partial_sum);
        delete (long long*)partial_sum;
    }

    clock_t end = clock();
    double time_span = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    cout << "Suma de primos paralelo: " << sum << endl;
    cout << "Tiempo paralelo: " << time_span << " segundos." << endl;

    return 0;
}
