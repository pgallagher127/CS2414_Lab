#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class DT>
class NestedBST {
    public:
        DT value; // value of the node
        vector<int> keys; // vector of keys associated with this value
        int dimension; // dimension of this node
        NestedBST* left; // pointer to left child
        NestedBST* right; // pointer to right child
        NestedBST* innerTree; // pointer to nested BST (next dimension)
        // ----- Constructors -----
        NestedBST(); // default constructor
        NestedBST(DT val, int dim); // parameterized constructor
        // ----- Core Operations -----
        void insert(int key, const vector<DT>& values, int depth); // insert or update a key-value tuple
        bool find(const vector<DT>& pattern, vector<DT>& record, int depth); // find keys matching a pattern with wildcards
        void display(int indent = 0); // print tree structure for verification
        int getCandidates(int depth);
};
template <class DT>
NestedBST<DT>::NestedBST() {
    value = NULL;
    dimension = 0;
    left = NULL;
    right = NULL;
    innerTree = NULL;
}
template <class DT>
NestedBST<DT>::NestedBST(DT val, int dim) {
    value = val;
    dimension = dim;
    left = NULL;
    right = NULL;
    innerTree = NULL;
}
template <class DT>
void NestedBST<DT>::insert(int key, const vector<DT>& values, int depth) {
    if (value == NULL) {
        value = values[depth];
    }
    if (values[depth] == value){
        if (depth == values.size()-1) {
            if (keys.empty()) {
                keys.push_back(key);
                cout << "Inserted key=";
            }
            else if (keys[0] == key) {
                cout << "Unchanged key=";
            }
            else{
                keys[0] = key;
                cout << "Updated key=";
            }
            cout << key << " for (";
            for(int i = 0; i < values.size()-1; i++) {
                    cout << values[i] << ",";
            }
            cout << values[values.size()-1] << ")" << endl;
        }
        else{
            if (innerTree == NULL) {
                innerTree = new NestedBST<int>(values[depth+1], dimension+1);
            }
            innerTree->insert(key, values, depth+1);
        }
    }
    else if (values[depth] < value) {
        if (left == NULL) {
            left = new NestedBST<int>(values[depth], dimension);
        }
        left->insert(key, values, depth);
    }
    else {
        if (right == NULL) {
            right = new NestedBST<int>(values[depth], dimension);
        }
        right->insert(key, values, depth);
    }

}

template <class DT>
bool NestedBST<DT>::find(const vector<DT>& pattern, vector<DT>& record, int depth) {
    bool left_output = false;
    bool right_output = false;
    bool inner_output = false;
    if (depth == pattern.size() - 1) {
        if (pattern[depth] == -999999) {
            vector<int> temp_rec = record;
            record.push_back(value);
            cout << "key=" << keys[0] << " for (";
            for(int i = 0; i < record.size()-1; i++) {
                    cout << record[i] << ",";
            }
            cout << record[record.size()-1] << ")" << endl;
            if (left != NULL) {
                left_output = left->find(pattern, temp_rec, depth);
            }
            if (right != NULL) {
                right_output = right->find(pattern, temp_rec, depth);
            }
            return true;
        }
        else if (pattern[depth] == value) {
            record.push_back(value);
            cout << "key=" << keys[0] << " for (";
            for(int i = 0; i < record.size()-1; i++) {
                    cout << record[i] << ",";
            }
            cout << record[record.size()-1] << ")" << endl;
            return true;
        }
        else if (pattern[depth] < value) {
            if (left != NULL) {
                left_output = left->find(pattern, record, depth);
            }
        }
        else if (pattern[depth] > value) {
            if (right != NULL) {
                right_output = right->find(pattern, record, depth);
            }
        }
    }
    else if (pattern[depth] == -999999) {
        vector<int> innervector = record;
        innervector.push_back(value);
        inner_output = innerTree->find(pattern, innervector, depth+1);
        if (left != NULL) {
            left_output = left->find(pattern, record, depth);
        }
        if (right != NULL) {
            right_output = right->find(pattern, record, depth);
        }
    }
    else if (pattern[depth] == value) {
        vector<int> innervector = record;
        innervector.push_back(value);
        inner_output = innerTree->find(pattern, innervector, depth+1);
    }
    else if (pattern[depth] < value) {
        if (left != NULL) {
            left_output = left->find(pattern, record, depth);
        }
    }
    else if (pattern[depth] > value) {
        if (right != NULL) {
            right_output = right->find(pattern, record, depth);
        }    
    }
    return left_output || right_output || inner_output;
}

template <class DT>
void NestedBST<DT>::display(int indent) {
    if (value == NULL) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        cout << "    ";
    }
    if (innerTree != NULL){ 
        cout << "[dim " << dimension << "] value=" << value;
        cout << "  (candidates=" << getCandidates(0) << ")" << endl;
        for (int i = 0; i < dimension; i++) {
            cout << "    ";
        }
        cout << "  -> dim " << dimension+1 << endl;
        innerTree->display(indent+1);
    }
    else {
        cout << "[dim " << dimension << "] value=" << value;
        cout << "  key=" << keys[0] << endl;
    }
    if (left != NULL) {
        left->display(indent);
    }
    if (right != NULL) {
        right->display(indent);
    }

}

template <class DT>
int NestedBST<DT>::getCandidates(int depth) {
    if (innerTree == NULL){
        if (left != NULL && right != NULL) {
            return left->getCandidates(depth) + right->getCandidates(depth) + 1;
        }
        else if (left != NULL) {
            return left->getCandidates(depth) + 1;
        }
        else if (right != NULL) {
            return right->getCandidates(depth) + 1;
        }
        else {
            return 1;
        }
    }
    else {
        if(depth == 0) {
            return innerTree->getCandidates(depth+1);
        }
        else if (left != NULL && right != NULL) {
            return left->getCandidates(depth) + right->getCandidates(depth) + innerTree->getCandidates(depth+1);
        }
        else if (left != NULL) {
            return left->getCandidates(depth) + innerTree->getCandidates(depth+1);
        }
        else if (right != NULL){
            return right->getCandidates(depth) + innerTree->getCandidates(depth+1);
        }
        else {
            return innerTree->getCandidates(depth+1);
        }
    }
}

int main() { 
 
    int numDimensions;   // number of value dimensions 
    cin >> numDimensions; 
 
    // Create the root tree (dimension 0) 
    NestedBST<int>* root = new NestedBST<int>(); 
    root->dimension = 0; 
 
    int numCommands; 
    cin >> numCommands; 
 
    char command; 
    for (int i = 0; i < numCommands; i++) { 
        cin >> command; 
        switch (command) { 
            case 'I': { // Insert 
                int key; 
                cin >> key; 
                vector<int> values(numDimensions); 
                for (int d = 0; d < numDimensions; d++) { 
                    cin >> values[d]; 
                }
                root->insert(key, values, 0);
                break; 
            } 
 
            case 'F': {
                vector<int> pattern(numDimensions);
                string token;
                for (int d = 0; d < numDimensions; d++) {
                    cin >> token;
                    if (token == "*") pattern[d] = -999999;
                    else pattern[d] = stoi(token);
                }
                vector<int> record;
                bool isFound = root->find(pattern, record, 0);
                if (!isFound) {
                    cout << "EMPTY" << endl;
                }
                break;
            } 
 
            case 'D': { // Display 
                cout << "NestedBST Structure:" << endl; 
                root->display(0); 
                cout << endl;
                break; 
            } 
 
            default: 
                cout << "Unknown command: " << command << endl; 
                break; 
        } 
    } 
    // Clean up 
    delete root; 
    return 0; 
}