#include <iostream>
#include "2_3Tree.h"

#include <fstream>
#include <chrono>

using namespace std;

//Example program implementing 2-3 Tree
int main() {
    BNode<int> * ex; //Declaring an instance of a node
    BTree<int> a; //Declaring the tree that uses ints.
    for(int i = 0; i < 10; ++i) a.insert(i); //Inserting some values
    a.traverse(); //Traversing the tree on ascending order.
    a.remove(5); //Removing an element
    cout << "\n";
    a.traverseInverse(); //Traversing on descending order
    cout << "\n";
    ex = a.search(5); //Searching the tree for the element. If it is found, it returns a pointer to the node; if not it returns NULL
    if(!ex) cout << "The number is not in the tree\n";
    cout << a.heightSearch(9) << "\n"; //Returns an int showing the height of the node. -1 if there is no node with the value
    cout << a.depthSearch(9) << "\n"; // Returns an int showing the depth of the node. -1 if there is no node with the value
    cout << a.levelSearch(9) << "\n"; // Returns an int showing the level of the node. -1 if there is no node with the value
}

/*
BTree<int> b;
int arr[10];


void trial(int index){
    int number = arr[index];
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    cout << b.search(number);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << "Time for " << number << " is: " << duration << "microseconds" << "\n";
}


int main() {

    ifstream myfile;
    ifstream otherFile;
    int a;
    myfile.open("numbers.txt");
    for (int i = 0; i < 100000; ++i) {
        myfile >> a;
        b.insert(a);
    }
    otherFile.open("searches.txt");
    for (int i = 0; i < 10; ++i) {
        otherFile >> arr[i];
        trial(i);
    }
}*/
