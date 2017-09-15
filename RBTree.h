
#ifndef RBTREE
#define RBTREE
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class NodeRB{
public:
    T t;
    NodeRB<T> * leftChild;
    NodeRB<T> * rightChild;
    NodeRB<T> * father;
    bool isBlack;


    NodeRB<T>(T t){
        this->t = t;
        leftChild = nullptr;
        rightChild = nullptr;
        father = nullptr;
        isBlack = true;
    }
};

template <class T>
class RBTree{
public:

    NodeRB<T> * root;
    NodeRB<T> * check;

    RBTree(){
        check = new NodeRB<T>(-1);
        root = check;
    }

    void leftRotate(NodeRB<T>*& n){
        NodeRB<T> * y = n->rightChild;
        n->rightChild = y->leftChild;
        if(y->leftChild){
            y->leftChild->father = n;
            y->father = n->father;
        }
        if(n->father == check) root = y;
        else if(n->father->leftChild == n) n->father->leftChild = y;
        else n->father->rightChild = y;
        y->leftChild = n;
        n->father = y;
    }

    void rightRotate(NodeRB<T>*& n){
        NodeRB<T> * y = n->leftChild;
        n->leftChild = y->rightChild;
        if(y->rightChild){
            y->rightChild->father = n;
            y->father = n->father;
        }
        if(n->father == check) root = y;
        else if(n->father->leftChild == n) n->father->leftChild = y;
        else n->father->rightChild = y;
        y->rightChild = n;
        n->father = y;
    }

    void insert(int data){
        NodeRB<T> * z = new NodeRB<T>(data);
        NodeRB<T> * y = check;
        NodeRB<T> * x = root;
        while (x!= check) {
            y = x;
            if(z->t < x->t) x=x->leftChild;
            else x=x->rightChild;
        }
        z->father = y;

        if(root == check) root = z;
        else if(z->t < y->t) y->leftChild = z;
        else y->rightChild = z;
        z->rightChild = check;
        z->leftChild = check;
        z->isBlack = false;
        insertFixup(z);
    }

    void insertFixup(NodeRB<T>*& z){
        while (!z->father->isBlack) {
            if(z->father == z->father->father->leftChild){
                NodeRB<T>* y = z->father->father->rightChild;
                if(!y->isBlack){
                    z->father->isBlack = true;
                    y->isBlack = true;
                    z->father->father->isBlack = false;
                    z = z->father->father;
                }
                else{
                    if(z == z->father->rightChild){
                        z = z->father;
                        leftRotate(z);
                    }
                    z->father->isBlack = true;
                    z->father->father->isBlack = false;
                    rightRotate(z);
                }
            }
            else{
                NodeRB<T>* y = z->father->father->leftChild;
                if(!y->isBlack){
                    z->father->isBlack = true;
                    y->isBlack = true;
                    z->father->father->isBlack = false;
                    z = z->father->father;
                }
                else{
                    if(z == z->father->leftChild){
                        z = z->father;
                        rightRotate(z);
                    }
                    z->father->isBlack = true;
                    z->father->father->isBlack = false;
                    leftRotate(z);
                }
            }
        }
        root->isBlack = true;
    }

    void transplant(NodeRB<T>*& u, NodeRB<T>*& v){
        if(!u->father) return;
        if(u->father == check) root = v;

        else if (u == u->father->leftChild ){
            u->father->leftChild = v;
        }
        else u->father->rightChild = v;
        if(v)v->father = u->father;
    }

    void remove(int data){
        NodeRB<T> * x;
        NodeRB<T> * y;
        NodeRB<T> * z;
        search(data, z);
        y = z;
        if(!y) return;
        bool yOriginalIsBlack = y->isBlack;
        if(z->leftChild == check){
            x = z->rightChild;
            transplant(z, z->rightChild);
        }
        else if(z->rightChild == check){
            x = z->leftChild;
            transplant(z, z->leftChild);
        }
        else{
            NodeRB<T> * y = min(z->rightChild);
            yOriginalIsBlack = y->isBlack;
            x = y->rightChild;
            if(y->father == z) x->father = y;
            else{
                transplant(y, y->rightChild);
                y->rightChild = z->rightChild;
                y->rightChild->father = y;
            }
            transplant(z, y);
            y->leftChild = z->leftChild;
            y->leftChild->father = y;
            y->isBlack = z->isBlack;
        }
        if(yOriginalIsBlack == true) deleteFixup(x);
    }

    void deleteFixup(NodeRB<T>*& x){
        while (x != root && x->isBlack) {
            if(x==x->father->leftChild){
                NodeRB<T> * w = x->father->rightChild;
                if(!w->isBlack){
                    w->isBlack = true;
                    x->father->isBlack = false;
                    leftRotate(x->father);
                    w = x->father->rightChild;
                }
                if(w->leftChild->isBlack && w->rightChild->isBlack){
                    w->isBlack = false;
                    x = x->father;
                }
                else{
                    if(w->rightChild->isBlack){
                        w->leftChild->isBlack = true;
                        w->isBlack = false;
                        rightRotate(w);
                        w = x->father->rightChild;
                    }
                    w->isBlack = x->father->isBlack;
                    x->father->isBlack = true;
                    if(w->rightChild) w->rightChild->isBlack = true;
                    leftRotate(x->father);
                    x = root;
                }

            }
            else{
                NodeRB<T> * w = x->father->leftChild;
                if(!w->isBlack){
                    w->isBlack = true;
                    x->father->isBlack = false;
                    rightRotate(x->father);
                    w = x->father->leftChild;
                }
                if(w->rightChild->isBlack && w->leftChild->isBlack){
                    w->isBlack = false;
                    x = x->father;
                }
                else{
                    if(w->leftChild->isBlack){
                        w->rightChild->isBlack = true;
                        w->isBlack = false;
                        leftRotate(w);
                        w = x->father->leftChild;
                    }
                    w->isBlack = x->father->isBlack;
                    x->father->isBlack = true;
                    w->leftChild->isBlack = true;
                    rightRotate(x->father);
                    x = root;
                }
            }
        }
        x->isBlack = true;
    }
    bool search(T data, NodeRB<T>*& lugar){
        lugar = searchRec(data, root);
        return lugar;
    }

    NodeRB<T> * searchRec(T data, NodeRB<T> *& currentRoot){
        if(currentRoot == check) return nullptr;
        else if(data == currentRoot->t) return currentRoot;
        else if(data < currentRoot->t) return searchRec(data, currentRoot->leftChild);
        else return searchRec(data, currentRoot->rightChild);
    }

    NodeRB<T> * min(NodeRB<T>*& cRoot){
        while (cRoot->leftChild != check) {
            cRoot = cRoot->leftChild;
        }
        return cRoot;
    }

/*    void crear(string archivo){
        ifstream iFile (archivo);
        int n, num;
        iFile >> n;
        for (int i=0; i<n; i++) {
            iFile >> num;
            insert(num);
        }
    }*/

    void traverseRecursive(NodeRB<T> * n){
        if(n != check){
            traverseRecursive(n->leftChild);
            cout << n->t << " ";
            traverseRecursive(n->rightChild);
        }
    }
    void traverseInverseRecursive(NodeRB<T> * n){
        if(n != check){
            traverseInverseRecursive(n->rightChild);
            cout << n->t << " ";
            traverseInverseRecursive(n->leftChild);
        }
    }

    int heightSearch(T t){
        NodeRB<T> * found;
        search(t, found);
        if(found && found != check){
            NodeRB<T> * traversed = found;
            int height = 0;
            while (traversed->leftChild && traversed->leftChild != check) {
                traversed = traversed->leftChild;
                height++;
            }
            traversed = found;
            int height2 = 0;
            while (traversed->rightChild && traversed->rightChild != check) {
                traversed = traversed->rightChild;
                height2++;
            }
            return max(height, height2);
        }
    }
    int depthSearch(T t){
        NodeRB<T> * found;
        search(t, found);
        if(found && found != check){
            NodeRB<T> * traversed = found;
            int depth = 0;
            while (traversed->father && traversed->father != check) {
                traversed = traversed->father;
                depth++;
            }
            return depth;
        }
    }

    int levelSearch(T t){
        return heightSearch(t) + 1;
    }

    void traverse(){
            traverseRecursive(root);
    }
    void traverseInverse(){
        traverseInverseRecursive(root);
    }

};


#endif /* RedBlackTree_h */