#include <iostream>
#include "BTree.h"
#include <fstream>
#include <chrono>

using namespace std;
/*
BTree<int> b(10);
int arr[10];
*/
/*
void trial(int index){
    int number = arr[index];
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    cout << b.search(number);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << "Time for " << number << " is: " << duration << "microseconds" << "\n";
}*/

//Example Program Impementing B Tree
int main() {
    BNode<int> * aa;
    BTree<int> b(5); //Declaring the tree that uses ints and with minimum degree(minimun number of childs) of 5
   for(int i = 1; i < 50; ++i) b.insert(i); //Inserting some elements
    b.traverse();//Traversing the tree in ascending order
    cout << "\n";
    b.remove(46); //Removing an element
    b.traverseInverse(); //Traversing the tree on descending order
    cout << "\n";
    aa = b.search(10); //Searching the tree for the element. If it is found, it returns a pointer to the node; if not it returns NULL
    if(aa) cout << "The number has been found\n";
    cout << b.heightSearch(9) << "\n"; //Returns an int showing the height of the node. -1 if there is no node with the value
    cout << b.depthSearch(9) << "\n"; // Returns an int showing the depth of the node. -1 if there is no node with the value
    cout << b.levelSearch(9) << "\n"; // Returns an int showing the level of the node. -1 if there is no node with the value
    return 0;


    /*
    ifstream myfile;
    ifstream otherFile;
    int a;
    myfile.open("numbers.txt");
    for(int i = 0; i < 100000; ++i){
        myfile >> a;
        b.insert(a);
    }
    otherFile.open("searches.txt");
    for(int i = 0; i < 10; ++i){
        otherFile >> arr[i];
        trial(i);
    }*/

}