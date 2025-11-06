#include <iostream>
#include <string>
using namespace std;


struct Station {
    string name;
    Station* prev;
    Station* next;
    Station(const string& n) : name(n), prev(NULL), next(NULL) {}
};

class TrainRoute {
public:
    TrainRoute(int n);
    void print() const; // provided for convenience
    int distance(const string& from, const string& to) const;
    void add(const string& name, const string& prevName, const string& nextName);
    void remove(const string& name);

private:
    Station* head;
    Station* find(const string& name) const; // provided for convienience
};


TrainRoute::TrainRoute(int n) {
head = NULL;
string name[100], prevName[100], nextName[100];
Station* nodes[100];
// Step 1: read input and create all nodes
for (int i = 0; i < n; i++) {
cin >> name[i] >> prevName[i] >> nextName[i];
nodes[i] = new Station(name[i]);
}
// Step 2: connect prev/next pointers by matching names
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
if (prevName[i] == name[j]) nodes[i]->prev = nodes[j];
if (nextName[i] == name[j]) nodes[i]->next = nodes[j];
}
}
// Step 3: find head (the one whose prev == "NULL")
for (int i = 0; i < n; i++) {
if (prevName[i] == "NULL") {
head = nodes[i];
break;
}
}
}

Station* TrainRoute::find(const string& name) const {
    Station* curr = head;
    while (curr != NULL) {
        if (curr->name == name) return curr;
        curr = curr->next;
    }
    return NULL;
}

void TrainRoute::print() const { // do not modify
    Station* curr = head;
    while (curr != NULL) {
        cout << curr->name;
        if (curr->next != NULL) cout << " <-> ";
        curr = curr->next;
    }
    cout << endl;
}

int TrainRoute::distance(const string& from, const string& to) const {
    Station*curr = head;
    bool fromFound = false;
    bool toFound = false;
    while(!fromFound && !toFound) {
        if (curr->name == from){
            fromFound = true;
        }
        else if (curr->name == to) {
            toFound = true;
        }
    }
    int count = 0;
    if (!toFound) {
        while (!toFound){
            if(curr->name == to) {
                toFound = true;
                break;
            }
            count++;
            curr = curr->next;
        }

    }
    else if(!fromFound) {
        while (!fromFound){
            if(curr->name == from) {
                toFound = true;
                break;
            }
            count++;
            curr = curr->next;
        }

    }
    
    return count;
}

void TrainRoute::add(const string& name, const string& prevName, const string& nextName) {
    
    Station* prevtemp = find(prevName);
    Station* nexttemp = find(nextName);
    Station* newStation = new Station(name);
    newStation->prev = prevtemp;
    newStation->next = nexttemp;
    prevtemp->next = newStation;
    nexttemp->prev = newStation;
    
}

void TrainRoute::remove(const string& name) {
    Station * curr = head;
    while (curr->name != name) {
        curr = curr->next;
    }
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    delete curr;
}



int main() { // do not modify
    int n;
    cin >> n;
    TrainRoute route(n);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        char cmd;
        cin >> cmd;
        if (cmd == 'P') {
            route.print();
        } else if (cmd == 'D') {
            string a, b;
            cin >> a >> b;
            cout << route.distance(a, b) << endl;
        } else if (cmd == 'A') {
            string name, prev, next;
            cin >> name >> prev >> next;
            route.add(name, prev, next);
        } else if (cmd == 'R') {
            string name;
            cin >> name;
            route.remove(name);
        }
    }
}