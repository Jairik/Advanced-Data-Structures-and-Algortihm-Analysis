#include <iostream>
#include <vector>
#include <string>
#include "Map.h"

using namespace std;

/* ----------------------------- Main File - Map Demo ----------------------------- 
   Author: JJ McCauley
   Creation Date: 4/23/24
   Last Update: 4/23/24
   Description: Aims to test the functionality of the set.
   User Interface: Terminal-based
   -------------------------------------------------------------------------------- */

    int main() {
        cout << "-------------Map-------------" << endl;
        Map<int, string> map; //Making a new map
        
        //Checking if map is empty
        cout << "Map is empty: ";
        if(map.isEmpty()) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false " << endl << endl;
        }

        //Inserting
        cout << "Inserting..." << endl;
        map.insert(5, "John");
        map.insert(2, "Sam");
        map.insert(17, "Jack");
        map.insert(23, "Jordan");
        cout << map << endl << endl;

        //Erasing elements
        cout << "Erasing John, too many J names" << endl;
        map.erase(5);
        cout << map << endl << endl;

        //Replacing with insert & set
        cout << "Replacing Jill and Jordan" << endl;
        map.set(23, "James");
        map.insert(19, "JJ aka the Superior Segfaulter");
        cout << map << endl << endl;

        //Getting elements
        //cout << "Key 19: " << map.get(19);

        //Making a new map
        Map<int, string> map2;
        map2 = map;
        cout << "New map assigned to current map" << endl;
        
        /*Testing the == and != operators
        cout << "The two maps are equal: ";
        if(map == map2) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
        cout << "The two maps are not equal" << endl;
        if(map != map2) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false" << endl << endl;
        } */

        //Find function
        cout << "Key 19 is in the first map: ";
        if(map.find(19)) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false" << endl << endl;
        }

        /*Clear function
        cout << "Erasing the second map" << endl;
        map2.clear();
        cout << map2 << endl; */

    }