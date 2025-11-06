#include <iostream>

using namespace std;


int main() {
    int i = 1, sum = 0;
    do {
        sum = sum + i;
        i = i + 1;
        cout << "One iteration" << endl;
    } while (i <= 1);
    return 0;
}