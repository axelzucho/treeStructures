#include <iostream>
#include "RBTree.h"

//Example program implementing RB Tree
int main() {
    RBTree<int> rb;
    NodeRB<int> * a;
    for(int i = 0; i < 10; ++i) rb.insert(i); //Inserting some elements
    rb.remove(2);
    rb.remove(4); //Deleting some elements
    rb.traverse(); //Traverses through the RB tree on ascending order
    cout << "\n";
    rb.search(3,a); //Searches the tree for "3" and gives the pointer the location of the node.
    if(a) cout << "Found\n";
    rb.traverseInverse(); //Traverses the RB tree on descending order
    cout << "\n";
    cout << rb.heightSearch(9) << "\n"; //Returns an int showing the height of the node. -1 if there is no node with the value
    cout << rb.depthSearch(9) << "\n"; // Returns an int showing the depth of the node. -1 if there is no node with the value
    cout << rb.levelSearch(9) << "\n"; // Returns an int showing the level of the node. -1 if there is no node with the value
    return 0;
}