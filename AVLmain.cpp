#include <iostream>
#include "BST.h"


#include <fstream>
#include <chrono>

using namespace std;
//Example program implementing 2-3 Tree
int main() {
    AVL<int> a; //Declaring an instance of the AVL Tree
    Nodo<int> * s;
    for(int i = 0; i < 30; ++i) a.insertar(i); //Inserting some values
    a.ascendentemente(); //Traversing the tree on ascending order.
    a.elimina(20);
    cout << "\n";
    a.descendentemente(); //Traversing the tree on descending order.
    cout << "\n";
    a.buscar(20,&s); //Searches the node value 20 and brings the node to the second parameter
    if(!s) cout << "The number was not found\n";
    cout << a.altura(0) << "\n"; //Returns an int showing the height of the node. -1 if there is no node with the value
    cout << a.nivel(0) << "\n"; // Returns an int showing the level of the node. -1 if there is no node with the value
    cout << a.profundidad(0) << "\n"; // Returns an int showing the depth of the node. -1 if there is no node with the value

}

/*
AVL<int> b;
int arr[10];
Nodo<int>* c;

void trial(int index){
    int number = arr[index];
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    cout << b.buscar(number,&c);
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
        b.insertar(a);
    }
    otherFile.open("searches.txt");
    for (int i = 0; i < 10; ++i) {
        otherFile >> arr[i];
        trial(i);
    }
}*/
