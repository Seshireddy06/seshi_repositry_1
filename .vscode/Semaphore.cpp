#include <iostream>
#include <pthread.h>
using namespace std;

int bank_balance = 1000;
pthread_mutex_t lock;

struct ThreadData {
    int thread_id;
    int amount;
};

void* withdraw(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int thread_id = data->thread_id;
    int amount = data->amount;

    pthread_mutex_lock(&lock);

    cout << "Thread " << thread_id << " attempting to withdraw ₹" << amount << endl;

    if (bank_balance >= amount) {
        bank_balance -= amount;
        cout << "Thread " << thread_id << ": Withdrawal successful. Balance = ₹" << bank_balance << endl;
    } else {
        cout << "Thread " << thread_id << ": Insufficient funds. Balance = ₹" << bank_balance << endl;
    }

    pthread_mutex_unlock(&lock);
    pthread_exit(nullptr);
}

int main() {
    pthread_t threads[3];
    ThreadData thread_data[3] = {
        {1, 500},
        {2, 500},
        {3, 500}
    };

    pthread_mutex_init(&lock, nullptr);

    for (int i = 0; i < 3; ++i) {
        pthread_create(&threads[i], nullptr, withdraw, &thread_data[i]);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
