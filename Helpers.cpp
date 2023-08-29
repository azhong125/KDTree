#include "Helpers.h"


kd::kd() {
    star.id = 0;
    left = NULL;
    right = NULL;
}

kd::~kd() {
    delete left;
    delete right;
}

void kd::insert(Star newStar) {
    if (star.id == 0) {
        star = newStar;
        direction = newStar.id % 3;
    } else {
        if (direction == 0) {
            //split by z
            if (newStar.z < star.z) {
                if (left == NULL) left = new kd();
                left->insert(newStar);
            } else {
                if (right == NULL) right = new kd();
                right->insert(newStar);
            }
        } else if (direction == 1) {
            //divide by x
            if (newStar.x < star.x) {
                if (left == NULL) left = new kd();
                left->insert(newStar);
            } else {
                if (right == NULL) right = new kd();
                right->insert(newStar);
            }
        } else if (direction == 2) {
            //divide by y
            if (newStar.y < star.y) {
                if(left == NULL) left = new kd();
                left->insert(newStar);
            } else {
                if (right == NULL) right = new kd();
                right->insert(newStar);
            }
        }
    }
}

float distanceTo(Star star, Star star2) {
    float xD = star.x - star2.x;
    float yD = star.y - star2.y;
    float zD = star.z - star2.z;
    return sqrt(xD * xD + yD * yD + zD * zD);
}

void kd::closest(int n, Star ship, priority_queue<Entry> *queue) {
    //priority_queue<Entry> queue;
    //push current star onto queue
    Entry en;
    en.star = star;
    en.distance = distanceTo(star, ship);

    queue->push(en);
    if((int) queue->size() > n) {
        queue->pop();
    }

    //stop if it is a leaf
    if (left != NULL || right != NULL) {
        if (direction == 0) {
            if (ship.z < star.z) {
                //traverse left
                if (left != NULL) {
                    left->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.z - ship.z) || (int) queue->size() < n) {
                    if (right != NULL) {
                        right->closest(n, ship, queue);
                    }
                }

            } else {
                //traverse right
                if (right != NULL) {
                    right->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.z - ship.z) || (int) queue->size() < n) {
                    if (left != NULL) {
                        left->closest(n, ship, queue);
                    }
                }

            }
        } else if (direction == 1) {
            if (ship.x < star.x) {
                //traverse left
                if (left != NULL) {
                    left->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.x - ship.x) || (int) queue->size() < n) {
                    if (right != NULL) {
                        right->closest(n, ship, queue);
                    }
                }

            } else {
                //traverse right
                if (right != NULL) {
                    right->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.x - ship.x)|| (int) queue->size() < n) {
                    if (left != NULL) {
                        left->closest(n, ship, queue);
                    }
                }

            }
        } else {
            if (ship.y < star.y) {
                //traverse left
                if (left != NULL) {
                    left->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.y - ship.y)|| (int) queue->size() < n) {
                    if (right != NULL) {
                        right->closest(n, ship, queue);
                    }
                }

            } else {
                //traverse right
                if (right != NULL) {
                    right->closest(n, ship, queue);
                }
                if (queue->top().distance > fabs(star.y - ship.y)|| (int) queue->size() < n) {
                    if (left != NULL) {
                        left->closest(n, ship, queue);
                    }
                }

            }
        }
    }
}

vector<Star> kd::cleaned(priority_queue<Entry> *queue, int n) {
    vector<Star> final;
    for (int i = 0; i < (int) n; ++i) {
        Entry en = queue->top();
        final.push_back(en.star);
        queue->pop();
    }

    for (int i = 0; i < (int) n / 2; ++i) {
        swap(final[i], final[n - i - 1]);
    }
    return final;
}