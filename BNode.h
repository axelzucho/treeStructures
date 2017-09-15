#ifndef BNODE_
#define BNODE_

#include <iostream>

using namespace std;

template<class T>
class BNode
{



public:
    int numberOfKeys;
    T *keys;
    BNode<T> **children;
    int minDegree;
    bool leaf;
    int height;
    int depth;
    int level;
    BNode(int minDegree, bool leaf)
    {
        this->minDegree = minDegree;
        this->leaf = leaf;
        keys = new T[2 * minDegree - 1];
        children = new BNode *[2 * minDegree];
        numberOfKeys = 0;
        height = 0;
        depth = 0;
        level = 1;
    }
    BNode(int minDegree, bool leaf, int height, int depth)
    {
        this->minDegree = minDegree;
        this->leaf = leaf;
        keys = new T[2 * minDegree - 1];
        children = new BNode *[2 * minDegree];
        numberOfKeys = 0;
        this->height = height;
        this->depth = depth;
        level = depth+1;
    }
    ~BNode()
    {

    }
    int findKey(T k)
    {
        int i = 0;
        while(i < numberOfKeys && keys[i] < k)
        {
            ++i;
        }
        return i;
    }
    void splitChild(int i, BNode<T> *childToSplit)
    {
        BNode<T> *newChild = new BNode<T>(childToSplit->minDegree, childToSplit->leaf,childToSplit->height, childToSplit->depth);
        newChild->numberOfKeys = minDegree - 1;
        for(int j = 0; j < minDegree - 1; j++)
            newChild->keys[j] = childToSplit->keys[j + minDegree];
        if(!childToSplit->leaf)
        {
            for(int j = 0; j <= minDegree-1; ++j)
                newChild->children[j] = childToSplit->children[j + minDegree];
        }
        childToSplit->numberOfKeys = minDegree - 1;

        for(int j = numberOfKeys; j >= i+1; --j)
            children[j + 1] = children[j];
        children[i+1] = newChild;
        for(int j = numberOfKeys; j >= i + 1; --j)
            keys[j] = keys[j-1];
        ++numberOfKeys;
        keys[i] = childToSplit->keys[minDegree - 1];

    }
    bool insertNonFull(int add)
    {
        int index = numberOfKeys -1;
        if(leaf)
        {
            while(index >= 0 && keys[index] > add)
            {
                keys[index+1] = keys[index];
                index--;
            }
            keys[index+1] = add;
            numberOfKeys += 1;
        }
        else
        {
            while(index >= 0 && keys[index] > add) index--;

            if(children[index+1]->insertNonFull(add))
            {
                splitChild(index+1,children[index+1]);
            }
        }

        if(numberOfKeys > 2*minDegree - 2) return true;
        return false;


    }
    BNode* search(T number)
    {
        int i = 0;
        while(number > keys[i] && i < numberOfKeys) ++i;
        if (keys[i] == number) return this;
        if(leaf) return NULL;
        return children[i]->search(number);
    }
    void traverse()
    {
        for(int i = 0; i < numberOfKeys; ++i)
        {
            if(!leaf && children[i] != NULL) children[i]->traverse();
            cout << keys[i] << " ";
        }
        if(!leaf) children[numberOfKeys]->traverse();
    }
    void traverseInverse()
    {
        for(int i = numberOfKeys; i > 0; --i)
        {
            if(!leaf && children[i] != NULL) children[i]->traverseInverse();
            cout << keys[i-1] << " ";
        }
        if(!leaf) children[0]->traverseInverse();
    }
    void traverseDepth()
    {
        ++depth;
        ++level;
        for(int i = 0; i < numberOfKeys; ++i)
            if(!leaf && children[i] != NULL) children[i]->traverseDepth();
        if(!leaf) children[numberOfKeys]->traverseDepth();
    }
    int getPred(int index){
        BNode* current = children[index];
        while(!current->leaf) current = current->children[current->numberOfKeys];
        return current->keys[current->numberOfKeys-1];
    }
    int getSucc(int index){
        BNode* current = children[index+1];
        while(!current->leaf) current = current->children[0];
        return current->keys[0];
    }

    void removeLeaf(int index){
        for(int i = index; i <numberOfKeys-1; ++i) keys[i] = keys[i+1];
        --numberOfKeys;
    }

    void merge(int index){
        BNode *child = children[index];
        BNode *sibiling = children[index+1];
        child->keys[minDegree-1] = keys[index];
        for(int i = 0; i < sibiling->numberOfKeys; ++i) child->keys[i+minDegree] = sibiling->keys[i];

        if(!child->leaf)
            for(int i = 0; i <= sibiling->numberOfKeys; ++i)
                child->children[i+minDegree] = sibiling->children[i];

        for(int i = index+1; i < numberOfKeys; ++i)
            keys[i-1] = keys[i];

        for(int i = index+2; i <= numberOfKeys; ++i)
            children[i-1] = children[i];

        child->numberOfKeys += sibiling->numberOfKeys+1;
        --numberOfKeys;

        delete(sibiling);
    }

    void removeNonLeaf(int index){
        int removing = keys[index];

        if(children[index]->numberOfKeys >= minDegree){
            int predecesor = getPred(index);
            keys[index] = predecesor;
            children[index]->remove(predecesor);
        }
        else if(children[index+1]->numberOfKeys > minDegree){
            int succesor = getSucc(index);
            keys[index] = succesor;
            children[index+1]->remove(succesor);
        }
        else{
            merge(index);
            children[index]->remove(removing);
        }
    }

    bool remove(T k){
        int i = 0;
        while(k > keys[i] && i < numberOfKeys) ++i;
        if(i < numberOfKeys && keys[i] == k){
            if(leaf) removeLeaf(i);
            else removeNonLeaf(i);
        }
        else{
            if(leaf) return false;
            bool flag = (i == numberOfKeys)? true:false;
            if(children[i]->numberOfKeys < minDegree)
                fill(i);
            if(flag && i > numberOfKeys)
                children[i-1]->remove(k);
            else children[i]->remove(k);
        }
        return false;
    }

    void fill(int index){
        if(index!= 0 && children[index-1]->numberOfKeys >= minDegree)
            borrowFromPrev(index);
        else if (index!= numberOfKeys && children[index+1]->numberOfKeys >= minDegree)
            borrowFromNext(index);
        else{
            if(index != numberOfKeys) merge(index);
            else merge(index-1);
        }
    }

    void borrowFromPrev(int index){
        BNode *child = children[index];
        BNode *sibling = children[index-1];

        for (int i=child->numberOfKeys-1; i>=0; --i)
            child->keys[i+1] = child->keys[i];

        if (!child->leaf)
        {
            for(int i=child->numberOfKeys; i>=0; --i)
                child->children[i+1] = child->children[i];
        }

        child->keys[0] = keys[index-1];

        if (!child->leaf)
            child->children[0] = sibling->children[sibling->numberOfKeys];

        keys[index-1] = sibling->keys[sibling->numberOfKeys-1];

        child->numberOfKeys += 1;
        sibling->numberOfKeys -= 1;

    }

    void borrowFromNext(int index)
    {

        BNode *child = children[index];
        BNode *sibling = children[index+1];

        child->keys[(child->numberOfKeys)] = keys[index];

        if (!(child->leaf))
            child->children[(child->numberOfKeys)+1] = sibling->children[0];

        keys[index] = sibling->keys[0];

        for (int i=1; i<sibling->numberOfKeys; ++i)
            sibling->keys[i-1] = sibling->keys[i];

        // Moving the child pointers one step behind
        if (!sibling->leaf)
        {
            for(int i=1; i<=sibling->numberOfKeys; ++i)
                sibling->children[i-1] = sibling->children[i];
        }

        child->numberOfKeys += 1;
        sibling->numberOfKeys -= 1;

    }
    int depthSearch(T k, int count){
        int i = 0;
        while(k > keys[i] && i < numberOfKeys) ++i;
        if (keys[i] == k) return count;
        if(leaf) return -1;
        return children[i]->depthSearch(k, count +1);
    }

    //friend class BTree<T>;
};

#endif