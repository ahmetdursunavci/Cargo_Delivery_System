#include "iostream"
#include "Missions.h"
#include "Stack.h"
#include "Queue.h"
#include "Transportation.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;
//this struct is my transportation linkedlist. İt executes cargo transportation
struct transportation{
    Packages packages;
    transportation *prev;
    transportation *next;
};
transportation *_head_t=NULL;

void insert(Packages packages) {
    //I created packages objects after that I insert them at the end of the my linkedlist
    transportation *new_packages=new transportation();
    new_packages->packages=packages;
    new_packages->next=NULL;
    new_packages->prev=NULL;
    if(_head_t==NULL) {
        _head_t=new_packages;
    }
    else {
        transportation *temp=_head_t;
        while(temp->next!=NULL) {
            temp=temp->next;
        }
        temp->next=new_packages;
        temp->next->prev=temp;
    }
}

vector<Packages> remove_for_center(string a) {
    //this method takes string which is indeces of packages which are taken from middle city.
    //after that I split my string with " "
    vector<Packages> vector;
    string array[(a.length() + 1) / 2];

    char commandarray[a.length()];

    strcpy(commandarray, a.c_str());

    char split[] = " ";

    char *str = strtok(commandarray, " ");

    int i = 0;
    while (str) {

        array[i] = str;

        str = strtok(NULL, split);

        i++;
    }
    for (int i = 0; i < (a.length() + 1) / 2; i++) {
        int j = 0;
        Packages package;
        transportation *temp = _head_t->next;
        //cout<<array[i];
        while (temp != NULL) {
            if (j == stoi(array[i])) {
                break;
            }
            temp = temp->next;
            j++;
        }
        package = temp->packages;
        //firstly I add them into the vector because if I remove one of them, their indeces change. So firstly I stored them
        // after that I sorted the indeces and remove
        // I sorted them, because such as my indeces be 0 2 4, if I remove 0 then 2 will be 1 , 4 will be 3. they go on like that
        vector.push_back(package);
    }
    int n = sizeof(array) / sizeof(array[0]);
    sort(array, array + n);
    int number=0;
    for (int i = 0; i < (a.length() + 1) / 2; i++) {
        int j = 0;
        transportation *temp = _head_t->next;
        while (temp != NULL) {
            if (j == (stoi(array[i])-number)) {
                number++;
                break;
            }
            j++;
            temp = temp->next;
        }
        if(temp->next==NULL) {
            temp->prev->next=NULL;
            free(temp);
        }
        else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
        }
    }
    return vector;
}
// this struct is store my cities and their stack and queue
struct Cities{
    string cities_name;
    Stack<Packages> stack;
    Queue<Truck> queue;

};
vector<Cities> cities;


void Missions::Read_dests(string path) {
    //I stored cities
    fstream file(path);
    string command;
    if (!file) {
        printf("file does not exist");
    } else {
        while (file.good()) {
            getline(file, command);
            Cities cities1;
            cities1.cities_name=command;
            cities.push_back(cities1);
        }
    }

}
void Missions::Read_packages(string path) {
    // I stored packages
    fstream file(path);
    string command;
    if (!file) {
        printf("file does not exist");
    } else {
        while (file.good()) {
            getline(file, command);
            string array[4];

            char commandarray[command.length()];

            strcpy(commandarray, command.c_str());

            char split[] = " ";

            char *str = strtok(commandarray, " ");

            int i = 0;
            while (str) {

                array[i] = str;

                str = strtok(NULL, split);

                i++;
            }
            // I created Package object here, then I found the city and stored its stack
            Packages package;
            package.name = array[0];

            for (auto i = cities.begin(); i != cities.end(); ++i) {
                if (i->cities_name == array[1]) {
                    i->stack.push(package);
                }
            }
        }
    }
}

void Missions::Read_trucks(string path) {
    //I stored trucks
    fstream file(path);
    string command;
    if (!file) {
        printf("file does not exist");
    } else {
        while (file.good()) {
            getline(file, command);
            string array[4];

            char commandarray[command.length()];

            strcpy(commandarray, command.c_str());

            char split[] = " ";

            char *str = strtok(commandarray, " ");

            int i = 0;
            while (str) {

                array[i] = str;

                str = strtok(NULL, split);

                i++;
            }
            // I created Truck object here, then I found the city and stored its queue
            Truck truck;
            truck.name = array[0];
            for (auto i = cities.begin(); i != cities.end(); ++i) {
                if (i->cities_name == array[1]) {
                    i->queue.enqueue(truck);
                }
            }
        }
    }
}

void Missions::Read_missions(string path)  {
    fstream file(path);
    string command;
    if (!file) {
        printf("file does not exist");
    } else {
        while (file.good()) {
           // firstly I split the commands with "-" charecter, then I store them into the vector
           // my last element which is in vector is middle city's indices of packages
           // I store the last element other vector by spliting them wtih "," charecter
            transportation station;
            getline(file, command);
            vector<string> my_vector;
            char commandarray[command.length()];

            strcpy(commandarray, command.c_str());

            char split[] = "-";

            char *str = strtok(commandarray, "-");

            while (str) {

                my_vector.push_back(str);

                str = strtok(NULL, split);
            }
            auto i=my_vector.begin();
            for(;i!=my_vector.end();++i) {};
            vector<string> my_vector2;
            i--;
            char commandarray2[i->length()];

            strcpy(commandarray2, i->c_str());

            char split2[] = ",";

            char *str2 = strtok(commandarray2, ",");

            while (str2) {

                my_vector2.push_back(str2);

                str2 = strtok(NULL, split2);
            }
            // iteretion1 is my first city
            auto iteration1 = my_vector.begin();
            for(auto j = cities.begin() ; j!=cities.end() ; ++j) {
                if(j->cities_name==*iteration1) {
                    //I found the city then I created Truck object and store it
                    Truck truck;
                    j->queue.getFront(truck);
                    Packages packagess;
                    packagess.name=truck.name;
                    insert(packagess);
                    j->queue.dequeue();
                    iteration1+=3;
                    //a equals number which I need to take them from first city
                    int a =stoi(*iteration1);
                    // I got the packages from first city and store them into my transportation linkedlist
                    while(a>0) {
                        Packages packages;
                        j->stack.getTop(packages);
                        insert(packages); // it is my transportation linkedlist method
                        //after the insert operation, I remove them from first city's stack
                        j->stack.pop();
                        a--;
                    }
                    break;
                }

            }
            auto iteration2 = my_vector.begin();
            //iteration2 equals my middle city's name
            iteration2+=1;

            for(auto j = cities.begin() ; j!=cities.end() ; ++j) {
                if(j->cities_name==*iteration2) {
                    iteration2+=3;

                    int a =stoi(*iteration2);
                    //I got the packages from second city and remove from stack
                    while(a>0) {
                        Packages packages;
                        j->stack.getTop(packages);
                        insert(packages);
                        j->stack.pop();
                        a--;
                    }
                    string b="";
                    for(auto iteration3 =my_vector2.begin();iteration3!=my_vector2.end();++iteration3) {
                        //b equals my commands last element without "," charecter
                        b=b+*iteration3+" ";
                    }
                    //I got the packages from transportation linkedlist for middle city then store them into vector
                    //after that I push them into the middle cities packages
                    vector<Packages> vector_packages=remove_for_center(b);
                    for(auto i=vector_packages.begin();i!=vector_packages.end();++i) {
                        Packages packagess=*i;
                        j->stack.push(packagess);
                    }
                    break;
                }

            }
            auto iteration4=my_vector.begin();
            //iteration4 equals my last city's name
            iteration4+=2;
            for(auto j = cities.begin(); j!=cities.end() ; ++j) {
                if(j->cities_name==*iteration4) {
                    //I got the trcuk object from my transportation linkedlist ,then store it into the last city's queue
                    // After that remove it to avoid memory leak
                    Truck truck;
                    truck.name=_head_t->packages.name;
                    _head_t->next->prev=NULL;
                    transportation *temp =_head_t;
                    j->queue.enqueue(truck);
                    _head_t=_head_t->next;
                    free(temp);
                    //then I take the packages and store, after that remove
                    while(_head_t!=NULL) {
                        if(_head_t->next==NULL) {
                            transportation *temp=_head_t;
                            Packages package;
                            package=temp->packages;
                            j->stack.push(package);
                            free(temp);
                            _head_t=NULL;
                            break;
                        }
                        transportation *temp=_head_t;
                        _head_t->next->prev=NULL;
                        _head_t=_head_t->next;
                        Packages package;
                        package=temp->packages;
                        j->stack.push(package);
                        free(temp);
                    }

                }
            }
        }
    }

}

void Missions::Writing(string path) {
    ofstream outfile;
    outfile.open(path, ios_base::app);

    for(auto i = cities.begin() ; i!=cities.end() ; ++i) {
	if(i->cities_name!="") {
        outfile<<i->cities_name<<endl<<"Packages:"<<endl;
        while (!(i->stack.isEmpty())) {
            Packages packages;
            i->stack.getTop(packages);
            i->stack.pop();
            outfile<<packages.name<<endl;
        }
       outfile<<"Trucks:"<<endl;
        while (!(i->queue.isEmpty())) {
            Truck truck;
            i->queue.getFront(truck);
            i->queue.dequeue();
            outfile<<truck.name<<endl;
        }
        outfile<<"-------------"<<endl;
    }
}
}