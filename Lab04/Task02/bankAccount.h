/* bankAccount.h simulates a simple bank account
 *
 * Joel Adams, Calvin College, Fall 2013.
 */
#include <pthread.h>


// Shared Variables
double bankAccountBalance = 0;
pthread_mutex_t lock;

// add amount to bankAccountBalance
void deposit(double amount) {
   pthread_mutex_lock(&lock);
   bankAccountBalance += amount;
   pthread_mutex_unlock(&lock);
}

// subtract amount from bankAccountBalance
void withdraw(double amount) {
   pthread_mutex_lock(&lock);
   bankAccountBalance -= amount;
   pthread_mutex_unlock(&lock);
}

void init() {
   pthread_mutex_init(&lock, NULL);
}

void cleanup() {
   pthread_mutex_destroy(&lock);
}

