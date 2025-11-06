#include <iostream>
using namespace std;

// Debug, forgot to initialize head wth a timeValueNode
// Struggle with cout for matrix 
// Improper shifting o sparse Rows

class timeValueNode { // node in a singly-linked list of time/value pairs
    public:
        int value; // numeric value stored at this cell
        int timeFrame; // integer timeframe when 'value' becomes effective
        timeValueNode* _next; // next node in ascending time order
        
        //contructors and destructors
        timeValueNode(int val, int tFrame); // constructor
        ~timeValueNode(); // destructor
        void display(); // display the entire list
        friend ostream& operator<<(ostream& os, const timeValueNode& node); // overload << operator for easy printing
        int size(); // return the number of nodes in the list
        void remove(int tFrame); // remove node with given timeFrame
        int find(int tFrame); // find value at given timeFrame
        int findexact(int tFrame);
        void update(int val, int tFrame);
        void addAtEnd(int val, int tFrame); // add a new node at the end of the list
        // other helper functions as needed
};


timeValueNode::timeValueNode(int val, int tFrame) {
    value = val;
    timeFrame = tFrame;
    _next = NULL;
}

timeValueNode::~timeValueNode(){
    if (value != NULL) {
        delete _next;
    }
}

void timeValueNode::display() {
    cout << this << endl;
}

ostream &operator<<(ostream &os, const timeValueNode &node){
    os << "(" << node.value << ", " << node.timeFrame << ") ";
    timeValueNode *curr = node._next;
    while (curr->value != NULL){
        os << "(" << curr->value << ", " << curr->timeFrame << ") ";
        curr = curr->_next;
    }
    return os;
}

int timeValueNode::size() {
    if (value == NULL) {
        return 0;
    }
    else {
        int count = 1;
        timeValueNode* temp_next = _next;
        while (temp_next->value != NULL) {
            count++;
            temp_next = temp_next->_next;
        }
        return count;
    }
}

void timeValueNode::remove(int tFrame) {
    if (timeFrame == tFrame) {
        value = _next->value;
        timeFrame = _next->timeFrame;
        timeValueNode* temp = _next;
        _next = temp->_next;
    }
    else{
        if (_next != NULL) {
            _next->remove(tFrame);
        }
    }
}

int timeValueNode::findexact(int tFrame) {
    if (tFrame == timeFrame) {
        return value;
    }
    else if(value == NULL) {
        return 0;
    }
    else {
        return _next->findexact(tFrame);
    }
}

int timeValueNode::find(int tFrame) {
    if (_next->value == NULL) {
        if (tFrame >= timeFrame) {
            return value;
        }
        else {
            return 0;
        }
    }
    else{
        if (tFrame < _next->timeFrame) {
            if (tFrame < timeFrame) {
                return 0;
            }
            return value;
        }
        else {
            return _next->find(tFrame);
        }
    }
}

void timeValueNode::update(int val, int tFrame){
    if (timeFrame == tFrame) {
        value = val;
    }
    else{
        if (_next != NULL) {
            _next->update(val, tFrame);
        }
    }
}

void timeValueNode::addAtEnd(int val, int tFrame) {
    if (value == NULL) {
        timeValueNode*newNode = new timeValueNode(value, timeFrame);
        newNode->_next = _next;
        _next = newNode; 
        value = val;
        timeFrame = tFrame;
    }
    else {
        _next->addAtEnd(val, tFrame);
    }
}

class sparseRow { // represents a row in a sparse matrix
    public:
        int rowIndex; // index of the row
        int colIndex; // index of the column
        timeValueNode* head; // head of the linked list of time/value pairs
        sparseRow(); // default constructor set rowIndex and colIndex to -1 and head to NULL
        sparseRow (int rIndex, int cIndex); // constructor set rowIndex and colIndex to given values and head to NULL
        ~sparseRow(); // destructor to clean up the linked list
        void display(); // display the row information and its time/value pairs
        // overload << operator for easy printing - print row index, col index, and all time/value pairs in the linked list
        friend ostream& operator<<(ostream& os, const sparseRow& row);
        int size(); // return the number of time/value pairs in the linked list
        // other helper functions as needed
};

sparseRow::sparseRow() {
    rowIndex = -1;
    colIndex = -1;
    head = new timeValueNode(NULL, NULL);
}

sparseRow::sparseRow(int rIndex, int cIndex) {
    rowIndex = rIndex;
    colIndex = cIndex;
    head = new timeValueNode(NULL, NULL);
}

sparseRow::~sparseRow(){
    delete head;
}

void sparseRow::display() {
    cout << this << endl;
}

ostream &operator<<(ostream &os, const sparseRow &row)
{
    os << "Row: " << row.rowIndex << ", Col: " << row.colIndex << " -> " << *(row.head) << endl;
    return os;
}

int sparseRow::size() {
    return head->size();
}

class TemporalSparseMatrix {
    public:
        // Matrix dimensions
        int rows; // total number of rows in the matrix
        int cols; // total number of columns in the matrix
        // Capacity & usage
        int MAX_NONZERO; // maximum number of non-zero entries allowed
        int currNZ; // number of slots currently in use (0..maxNZ)
        // Storage for sparse entries
        sparseRow* entries; // array of sparseRow entries
        // Optional bookkeeping fields (students decide how to use them)
        int highestTimeSeen; // max timeframe observed so far (can be -1 initially)
        TemporalSparseMatrix(int numRows, int numCols, int maxNZ); // constructor
        ~TemporalSparseMatrix(); //
        // insert a value at given row, column, and timeframe if found in the entries array, update the linked list at that entry,
        // if not found, create a new sparseRow entry if there is capacity and insert the time/value pair in the linked list also
        // increment currNZ if a new sparseRow is created
        void insert(int rIndex, int cIndex, int val, int tFrame);
        // remove the value at given row, column, and timeframe if found in the entries array,
        // if the linked list at that entry becomes empty after removal, remove the sparseRow entry also
        // decrement currNZ if a sparseRow is removed and shift the remaining entries up one to fill the gap
        // if not found, do nothing
        void remove(int rIndex, int cIndex, int tFrame);
        // find the value at given row, column, and timeframe if found in the entries array,
        // otherwise return 0
        int find(int rIndex, int cIndex, int tFrame); // find the value at given row, column, and timeframe
        void display(); // display the entire matrix
        int size(); // return the number of non-zero entries in the matrix
        friend ostream& operator<<(ostream& os, const TemporalSparseMatrix& matrix); // overload << operator for easy printing
        // other helper functions as needed
};

TemporalSparseMatrix::TemporalSparseMatrix(int numRows, int numCols, int maxNZ) {
    rows = numRows;
    cols = numCols;
    MAX_NONZERO = maxNZ;
    entries = new sparseRow[MAX_NONZERO];
    currNZ = 0;
}

TemporalSparseMatrix::~TemporalSparseMatrix(){
    delete []entries;
}

void TemporalSparseMatrix::insert(int rIndex, int cIndex, int val, int tFrame) {
    bool done = false;
    for (int i = 0; i < currNZ; i++) {
        if (entries[i].rowIndex == rIndex && entries[i].colIndex == cIndex) {
            if (entries[i].head->findexact(tFrame) != 0) {   
                entries[i].head->update(val, tFrame);
                done = true;
                break;
            }
            else{
                entries[i].head->addAtEnd(val, tFrame);
                done = true;
                break;
            }
        }
    }
    if (!done && currNZ < MAX_NONZERO) {
        entries[currNZ].rowIndex = rIndex;
        entries[currNZ].colIndex = cIndex;
        entries[currNZ].head->addAtEnd(val, tFrame);
        currNZ++;
    }
}

void TemporalSparseMatrix::remove(int rIndex, int cIndex, int tFrame){
    for (int i = 0; i < currNZ; i++) {
        if (entries[i].rowIndex == rIndex && entries[i].colIndex == cIndex) {
            entries[i].head->remove(tFrame);
            if (entries[i].head->size() < 1) {
                if (i != currNZ-1) {
                    for (int j = i; j < currNZ-1; j++) {
                        entries[j] = entries[j+1];
                    }
                }
                currNZ--;
                entries[currNZ].rowIndex = -1;
                entries[currNZ].colIndex = -1;
                entries[currNZ].head = new timeValueNode(NULL, NULL);
            }
            break;
        }
    }
}

int TemporalSparseMatrix::find(int rIndex, int cIndex, int tFrame){
    for (int i = 0; i < currNZ; i++) {
        if (entries[i].rowIndex == rIndex && entries[i].colIndex == cIndex) {
            return entries[i].head->find(tFrame);
        }
    }
    return 0;
}

void TemporalSparseMatrix::display() {
    for (int i = 0; i < currNZ; i++) {
        cout << entries[i];
    }
}

int TemporalSparseMatrix::size(){
    return currNZ;
}

ostream& operator<<(ostream& os, const TemporalSparseMatrix& matrix){
    
    return os;
}


int main () {
    int numRows, numCols, maxNZ;
    cin >> numRows >> numCols >> maxNZ;
    TemporalSparseMatrix tsm(numRows, numCols, maxNZ);
    int numCommands; // number of commands to process
    char command; // command type
    cin >> numCommands;
    // Process each command and this is a suggested format, students can modify as needed; not guaranteed to be correct.
    // Your responsibility
    for (int i = 0; i < numCommands; i++) {
        cin >> command;
        switch (command) {
            case 'I': { // Insert
            int rIndex, cIndex, val, tFrame;
            cin >> rIndex >> cIndex >> val >> tFrame;
            tsm.insert(rIndex, cIndex, val, tFrame);
            cout << "Inserted value " << val << " at (" << rIndex << ", " << cIndex << ") for timeframe " << tFrame << endl;
            break;
            }
            case 'R': { // Remove
            int rIndex, cIndex, tFrame;
            cin >> rIndex >> cIndex >> tFrame;
            tsm.remove(rIndex, cIndex, tFrame);
            cout << "Removed value at (" << rIndex << ", " << cIndex << ") for timeframe " << tFrame << endl;
            break;
            }
            case 'F': { // Find
            int rIndex, cIndex, tFrame;
            cin >> rIndex >> cIndex >> tFrame;
            int foundValue = tsm.find(rIndex, cIndex, tFrame);
            cout << "Found value at (" << rIndex << ", " << cIndex << ") for timeframe " << tFrame << ": " << foundValue << endl;
            break;
            }
            case 'D': { // Display
            cout << "Temporal Sparse Matrix:" << endl;
            tsm.display();
            break;
            }
            case 'S': { // Size
            int currentSize = tsm.size();
            cout << "Current number of non-zero entries: " << currentSize << endl;
            break;
            }
            default:
            cout << "Unknown command: " << command << endl;
            break;
        }
    }
    // make sure you clean up and free any allocated memory
    return 0;
}

