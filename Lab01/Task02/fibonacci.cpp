#include <iostream>
using namespace std;

int main()
{
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm << " + ";

    // measure the execution time of the following loop
    for (int i = 1; i <= n - 2; ++i)
    {
        nextTerm = firstTerm + secondTerm;
        cout << nextTerm << " + ";
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }
    cout << endl;
    return 0;
}
