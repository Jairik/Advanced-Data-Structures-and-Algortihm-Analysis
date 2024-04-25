#include <iostream>
#include <vector>
#include <string>
#include "Multimap.h"
using namespace std;

/* ----------------------------- Main File - Multimap Demo ------------------------ 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/23/24
   Description: Aims to test the functionality of the multiset.
   User Interface: Terminal-based
   -------------------------------------------------------------------------------- */

    int main() {
        cout << "-------------Multimap-------------" << endl;
        Multimap<int, string> mMap; //Making a new map
        
        //Checking if map is empty
        cout << "Multimap is empty: ";
        if(mMap.isEmpty()) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false " << endl << endl;
        }

        //Inserting
        cout << "Inserting..." << endl;
        mMap.insert(5, "John");
        mMap.insert(2, "Sam");
        mMap.insert(17, "Jack");
        mMap.insert(23, "Jordan");
        cout << mMap << endl << endl;

        //Erasing elements
        cout << "Erasing John, too many J names" << endl;
        mMap.erase(5);
        cout << mMap << endl << endl;

        //Replacing with insert & set
        cout << "Replacing Jill and Jordan" << endl;
        mMap.set(23, "James");
        mMap.insert(19, "JJ aka the Superior Segfaulter");
        cout << mMap << endl << endl;

        //Getting elements & printing the vector
        cout << "Key 19: "; 
        vector<string> v = mMap.get(19);
        for(int i = 0; i < v.size(); i++) {
            cout << v[i];
            if(i != v.size()-1) {
                cout << ", ";
            }
        }

        //Making a new multimap
        Multimap<int, string> mMap2;
        mMap2 = mMap;
        cout << "New multimap assigned to current multimap" << endl;
        
        /* Testing the == and != operators
        cout << "The two multimaps are equal: ";
        if(mMap == mMap2) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
        cout << "The two multimaps are not equal" << endl;
        if(mMap != mMap2) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false" << endl << endl;
        } */

        //Find function
        cout << "Key 19 is in the first map: ";
        if(mMap.find(19)) {
            cout << "true" << endl << endl;
        }
        else {
            cout << "false" << endl << endl;
        }
    }