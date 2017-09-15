#ifndef BTREE_
#define BTREE_

#include "BNode.h"

template<class T>


class BTree{
private:
    BNode<T> *root;
    int minDegree;
public:
    BTree<T>(int t){
        root = NULL;
        minDegree = t;
    }
    void traverse(){
        if(root != NULL) root->traverse();
    }
    void traverseInverse(){
        if(root != NULL) root->traverseInverse();
    }
    BNode<T> *search(T k){
        return (root == NULL) ? NULL : root->search(k);
    }
    void insert(T add){
        if(root == NULL){
            root = new BNode<T>(minDegree, true);
            root->keys[0] = add;
            root->numberOfKeys = 1;
        }
        else{
            if(root->insertNonFull(add))
            {
                root->traverseDepth();
                BNode<T> *newChild = new BNode<T>(minDegree, root->leaf, root->height, root->depth);
                newChild->numberOfKeys = minDegree - 1;
                BNode<T> *newParent = new BNode<T>(minDegree, root->leaf, root->height+1, 0);
                newParent->numberOfKeys = 1;


                for(int j = 0; j < minDegree - 1; j++)
                    newChild->keys[j] = root->keys[j + minDegree];
                if(!root->leaf)
                {
                    for(int j = 0; j <= minDegree - 1; ++j)
                        newChild->children[j] = root->children[j + minDegree];
                }
                root->numberOfKeys = root->minDegree - 1;
                newParent->keys[0] = root->keys[root->minDegree-1];
                newParent->children[0] =root;
                newParent->children[1] = newChild;
                root = newParent;
                root->leaf = false;
            }
        }
    }

    bool remove(T k){
        if(root == NULL) return false;

        root->remove(k);

        if(root->numberOfKeys == 0){
            BNode<int> *el = root;
            if(root->leaf) root = NULL;
            else root = root->children[0];
            delete el;
        }
    }

    int heightSearch(T d){
        BNode<int> * a;
        if(root != NULL) {
            a=  (root->search(d));
            if(a != NULL) return a->height;
        }
        return -1;
    }

    int depthSearch(T d){
        return (root == NULL) ? NULL : root->depthSearch(d, 0);
    }
    int levelSearch(T d){
        return (root == NULL) ? NULL : root->depthSearch(d, 1);
    }

};




#endif