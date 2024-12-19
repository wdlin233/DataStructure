#include "hashtable.h"

Node::~Node() {
    // do nothing
}

bool Node::operator!=(const char *str) {
    if(str==NULL)
        return true;
    if(this->p.first.compare(str) == -1) // pair<string, int>
        return true;
    return false;
}

bool Node::operator!=(const string &str) {
    // it can't be NULL
    if(this->p.first.compare(str) == -1)
        return true;
    return false;
}

bool Node::operator==(const char *str) {
    if(str==NULL)
        return false;
    if(this->p.first.compare(str) == 0)
        return true;
    return false;
}

bool Node::operator==(const string &str) {
    if(this->p.first.compare(str)==0)
        return true;
    return false;
}

bool Node::operator!=(Node &n) {
    if(this->p.first.compare(n.p.first)==-1)
        return true;
    return false;
}

bool Node::operator==(Node &n) {
    if(this->p.first.compare(n.p.first)==0)
        return true;
    return false;
}

// get char from string
char Node::operator[](const int index) {
    if(index>=0 && index<length())
        return this->p.first[index];
    else
        return this->p.first[0];
    
}

int Node::length() { //return length of the string
    return p.first.length();
}

int &Node::second() {
    return p.second;
}

const pair<string, int>* Node::get_pair() const {
    return &p;
}

HashTable::HashTable() {
    elem=new Node[300000]();
    size=300000;
}

HashTable::~HashTable() {
    delete[] elem;
}

int HashTable::hash(Node &index) {
    int hash = 0;
    for (int i = 0; i < index.length(); i++) {
        hash += index[i] * (i + 1);
    }
    return hash % size;
}

bool HashTable::search(Node &index, int &pos, int &times) {
    int value = hash(index);  
    times=0;
    while (value <= this->size && 
           elem[value].get_pair()->first.compare("#") !=0 && 
           elem[value].get_pair()->first.compare(index.get_pair()->first) != 0
        )
    {
        value += 1; //baoli
        times += 1;
        if(value == size)
            value = 0;
    }
    pos = value;
    if(elem[pos].get_pair()->first.compare(index.get_pair()->first) == 0)
    {
        return true;
    }
    return false;
}

int HashTable::insert(Node &index) {   
    int pos = 0, times = 0;
    if(search(index,pos,times))
    {
        elem[pos].second()++;
        return 2; // exist
    }
    else
        elem[pos]=index;
    return 1;
}

// or you can use this:
// int HashTable::insert(const char * str) {
//     //Node *tmp=new Node(str);
//     Node tmp(str);
//     int pos = 0, times = 0;
//     if(search(tmp,pos,times))
//     {
//         elem[pos].second()++;
//         return 2;
//     }
//     else
//         elem[pos]=tmp;
//     //delete tmp;
//     return 1;
// }

int HashTable::insert(const char * str) {
    Node *tmp=new Node(str);
    //Node tmp(str);
    int pos = 0, times = 0;
    if(search(*tmp,pos,times))
    {
        elem[pos].second()++;
        delete tmp; // which is important
        return 2;
    } else {
        elem[pos] = *tmp;
        delete tmp;
    }
    return 1;
}

// another way to implement insert
// int HashTable::insert(const char *str) {
//     Node tmp(str);
//     int result = insert(tmp);
//     return result;
// }

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Node::Node() {
    p = make_pair(string("#"), 1);
}

Node::Node(const char *str) {
    p = make_pair(string(str), 1);
}

Node::Node(const string &str) {
    p = make_pair(str, 1);
}

int HashTable::get_size() const {
    return size;
}

const pair<string, int>* HashTable::get_pair(int index) {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}

const pair<string, int>* HashTable::get_pair(int index) const {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}