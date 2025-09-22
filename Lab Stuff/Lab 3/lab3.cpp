#include <iostream>
using namespace std;

int alienBunnyBoom (int months) {
    if (months > 2) {
        return alienBunnyBoom(months-1) + alienBunnyBoom(months-2);
    }
    else if (months == 2) {
        return 1;
    }
    else {
        return 1;
    }
}
    
int superPowerChain(int numHeroes) {
    if (numHeroes > 1) {
        return superPowerChain(numHeroes-1) * numHeroes;
    }
    else {
        return 1;
    }
}


int main() {
    int numHeroes, numMonths;
    cin >> numHeroes >> numMonths;
    cout << "Total Power Of Heroes: " << superPowerChain(numHeroes) << endl;
    cout << "Total Number Of Bunny Pairs: " << alienBunnyBoom(numMonths) << endl;
    return 0;
}