#include "StarMap.h"
#include "Star.h"
using namespace std;
#include <sstream>
#include <cmath>
#include <iostream>

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}

StarMap::StarMap(std::istream& stream) {
    k = new kd();
    int count = 1;
    for (string s;getline(stream, s, '\n');) {
        Star newStar;
        istringstream str(s);
        string temp;
        int num = 0;
        while (getline(str, temp, '\t')) {
            if (num == 0) newStar.x = stof(temp);
            if (num == 1) newStar.y = stof(temp);
            if (num == 2) newStar.z = stof(temp);
            num++;
        }
        newStar.id = count;
        k->insert(newStar);
        count++;
    }
}
StarMap::~StarMap() {
    delete k;
}

vector<Star> StarMap::find(size_t n, float x, float y, float z) {
    Star ship;
    ship.x = x;
    ship.y = y;
    ship.z = z;
    priority_queue<Entry> queue;
    k->closest(n, ship, &queue);
    return k->cleaned(&queue, n);
}