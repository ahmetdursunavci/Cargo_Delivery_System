#include <iostream>
#include "Stack.h"
using namespace std;
#include "Transportation.h"
#include "Missions.h"



int main(int argc, char *argv[]) {
    Missions missions;
    missions.Read_dests(argv[1]);
    missions.Read_packages(argv[2]);
    missions.Read_trucks(argv[3]);
    missions.Read_missions(argv[4]);
    missions.Writing(argv[5]);


}

