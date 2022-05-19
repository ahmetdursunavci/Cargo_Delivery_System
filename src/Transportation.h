//
// Created by hp on 13.12.2020.
//

#ifndef ASSIGNMENT3_TRANSPORTATION_H
#define ASSIGNMENT3_TRANSPORTATION_H
#include <iostream>
using namespace std;
//I created Truck and Package class to store my trucks and packages in the stack and queue
class Packages{
public:
    string name;

};
class Truck : public Packages{
public:
    string name;
    int power;

};
#endif //ASSIGNMENT3_TRANSPORTATION_H
