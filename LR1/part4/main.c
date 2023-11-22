#include <stdio.h>
#include <pthread.h>
#include <math.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

unsigned long catalan(unsigned int n) {
    if (n <= 1) return 1;
    unsigned long res = 0;
    for (int i = 0; i < n; i++)
        res += catalan(i) * catalan(n - i - 1);
    return res;
}

void* compute_catalan(void* arg) {
    int n = *((int*)arg);
    for (int i = 0; i < n; i++) {
        printf("%lu ", catalan(i));
    }
    printf("\n");
    return NULL;
}

void* compute_primes(void* arg) {
    int n = *((int*)arg);
    int count = 0;
    for (int i = 2; count < n; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n");
    return NULL;
}

int main() {
    const int N = 10;
    pthread_t threads[2];
    int thread_args[2] = {N, N};

    pthread_create(&threads[0], NULL, compute_catalan, (void*)&thread_args[0]);
    pthread_create(&threads[1], NULL, compute_primes, (void*)&thread_args[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
