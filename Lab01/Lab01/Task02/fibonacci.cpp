#include <iostream>
#include <sys/time.h>
using namespace std;

int main() {
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    // Declaring a start and end variable of type struct timeval, which is
    // defined in sys/time.h
    struct timeval start, end;

    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm << " + ";

    //measure the execution time of the following loop
    gettimeofday(&start, nullptr); // fetching current time prior to execution of the loop

    for (int i = 1; i <= n-2; ++i) {
        nextTerm = firstTerm + secondTerm;
        cout << nextTerm << " + ";
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }

    gettimeofday(&end, nullptr); // fetching current time after the loop has completed execution

    // Calculating execution time
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double executionTime = seconds + (microseconds * 1e-6);

    cout << "\nExecution time: " << executionTime << " seconds" << endl;
    return 0;
}
