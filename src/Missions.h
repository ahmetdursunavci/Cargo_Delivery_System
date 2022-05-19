//
// Created by hp on 13.12.2020.
//

#ifndef ASSIGNMENT3_MISSIONS_H
#define ASSIGNMENT3_MISSIONS_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class Missions {
public:
    void Read_dests(string path);
    void Read_packages(string path);
    void Read_trucks(string path);
    void Read_missions(string path);
    void Writing(string path);
};


#endif //ASSIGNMENT3_MISSIONS_H
