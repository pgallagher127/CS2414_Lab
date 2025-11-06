#include <iostream>
#include <string>
using namespace std;

// node class definition given do not modify

class Node{
    private:
        char info;
        Node* left;
        Node* right;
    public:
        Node (char val, Node* l = NULL, Node* r = NULL){
            info = val;
            left = l;
            right = r;
        }
        Node* getLeft() const { return left; }
        Node* getRight() const { return right; }
        char   getInfo() const { return info; }

        void setRight(Node* r) {
            this->right = r;
        }

        void setLeft(Node* l) {
            this->left = l;
        }
};

class BinaryTree{
    private:
        Node* root;
    public:
        BinaryTree(){ 
            string input;
            cin >> input;
            int node_count = 0; //track the number of nodes created
            // start with the root
            root = new Node(input[0], new Node(input[2*0+1]), new Node(input[2*0+2])); // left -> 2i+1, right -> 2i+2
            node_count += 3; // three nodes created root, left and right.

            for (int i =1; node_count < input.length(); ++i){
                Node* temp = search(input[i], root);
                temp->setLeft(new Node(input[2*i+1]));
                temp->setRight(new Node(input[2*i+2]));
                node_count += 2; // two nodes created left and right.
            }
        }

        ~BinaryTree(){
            
        }

        Node* search (char a, Node* current){
            if (current->getInfo() == a) {
                return current;
            }
            else if (current->getInfo() == 'N') {
                return NULL;
            }
            else if (current->getLeft() == NULL && current->getRight() == NULL) {
                return NULL;
            }
            else {
                Node* res1 = search(a, current->getLeft());
                Node* res2 = search(a, current->getRight());
                if (res1 != NULL) {
                    return res1;
                }
                else if (res2 != NULL) {
                    return res2;
                }
                else {
                    return NULL;
                }
            }

        }

        int height(){
            Node* current = root;
            int count = 1;
            while(current->getLeft() != NULL) {
                count++;
                current = current->getLeft();
            }
            return count;
        }

        void postfixExpression(Node* node){
            if (node->getInfo() == 'N') {
            }
            else if (node->getRight() == NULL && node->getLeft() == NULL){
                cout << node->getInfo() << " ";
            }
            else if (node->getLeft() == NULL) {
                postfixExpression(node->getRight());
                cout << node->getInfo() << " ";
            }
            else if (node->getRight() == NULL){
                postfixExpression(node->getLeft());
                cout << node->getInfo() << " ";
            }
            else{
                postfixExpression(node->getLeft());
                postfixExpression(node->getRight());
                cout << node->getInfo() << " ";
            }
            
        }

        Node* getRoot(){
            return root;
        }

};

int main(){
    BinaryTree tree;
    int height = tree.height();
    cout << "Height of tree: " << tree.height() << endl;
    tree.postfixExpression(tree.getRoot());
    return 0;
}