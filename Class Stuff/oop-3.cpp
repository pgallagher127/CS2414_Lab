#include <iostream>
using namespace std;

class someInfo {
    public:
        int* data;
        someInfo ();
        someInfo(int value);
        someInfo (const someInfo& other);
        ~someInfo ();
};

someInfo::someInfo() {
    data = NULL;
}

someInfo::~someInfo() {
    cout << "Destruction of " << *data << endl;
    delete data;
}

someInfo::someInfo (const someInfo& other) {
    data = new int(*(other.data));
}

someInfo::someInfo(int value) {
    data = new int(value);
}

int main() {
    someInfo info1(42);

    someInfo* info2 = new someInfo(100);

    someInfo info3 = info1;

    cout << "info1 data: " << *(info1.data) << endl;
    cout << "info2 data: " << *((*info2).data) << endl;
    cout << "info3 data: " << *(info3.data) << endl;

    delete info2;

    return 0;
}