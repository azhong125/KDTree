#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
using namespace std;
#include <vector>
#include "Star.h"
#include <queue>
#include <cmath>
#include <stack>

struct Entry {
    float distance;
    Star star;

    bool operator < (const Entry& other) const {
        return this->distance < other.distance;
    }
};

class kd {
    Star star;
    kd* left;
    kd* right;
    //priority_queue<Entry> *queue;

public:
    int direction;
    //1 = x
    //2 = y
    //0 = z
    kd();
    ~kd();
    void insert(Star star);
    void closest(int n, Star ship, priority_queue<Entry> *queue);
    vector<Star> cleaned(priority_queue<Entry> *queue, int n);
  //  void merge(Entry en, int n);

};



#endif
