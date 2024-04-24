#include <iostream>
#include <vector>
#include "Multiset.h"
using namespace std;

/* ----------------------------- Main File - Multiset Demo ----------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/23/24
   Description: Aims to test the functionality of the multiset.
   User Interface: Terminal-based
   -------------------------------------------------------------------------------- */

int main() {
   cout << endl << endl << "-----------Multisets-----------" << endl;
   Multiset<int> multiSet; //Making the multiSet
    
   //Testing if the multiSet is empty
   bool multiSetIsEmpty = multiSet.isEmpty(); 
   if(multiSetIsEmpty) {
      cout << "Multiset is made and empty" << endl << endl;
   }

   //Inserting elements into a multiSet
   cout << "Inserting elements into multiSet (5, 4, 4, 3, 3, 2, 2, 1, 1, 1)" << endl;
   for(int i = 10; i > 0; i--) {
      multiSet.insert(i/2);
   }
   if(multiSet.find(1)) {
      cout << multiSet << endl; //Printing the multiSet
   }
   cout << "Multiset Count of 1: " << multiSet.count(1) << endl;
   cout << "Multiset Count of 2: " << multiSet.count(2) << endl;
   cout << "Multiset Count of 3: " << multiSet.count(3) << endl;
   cout << "Multiset Count of 4: " << multiSet.count(4) << endl;
   cout << "Multiset Count of 5: " << multiSet.count(5) << endl << endl;


   //Erasing and inserting
   multiSet.insert(1);
   multiSet.insert(5);
   multiSet.insert(12);
   cout << multiSet << endl << endl;
   multiSet.erase(2);
   multiSet.erase(15);
   cout << multiSet << endl << endl;

   //Making a new multiSet
   Multiset<int> multiSet2 = multiSet;
   cout << "New multiSet using assignment: " << multiSet2 << endl;
   Multiset<int> multiSet3 = new Multiset<int>(set2);
   cout << "New multiSet using copy constructor: " << multiSet3 << endl;

   //Logical operators
   if(set == multiSet2) {
      cout << "The multiSets are equal" << endl;
   }
   multiSet2.erase(2);
   if(set != multiSet2) {
      cout << "Erased 2, multiSets are now not equal" << endl;
   }
   if(set > multiSet2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set < multiSet2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set > multiSet2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set < multiSet2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set >= multiSet2) {
      cout << "___ is a subset of ___" << endl;
   }
   if(set <= multiSet2) {
      cout << "___ is a subset of ___" << endl;
   }
   
   //+, *, - operators
   Multiset<int> multiSetIntersection = multiSet * set2;
   cout << "Intersection of the two multiSets: " << multiSetIntersection << endl;
   Multiset<int> multiSetUnion = multiSet + set2;
   cout << "Union of the two multiSets: " << multiSetUnion << endl;
   Multiset<int> multiSetDifference = multiSet - set2;
   cout << "Difference of the two multiSets: " << multiSetDifference << endl; 

   //Clear function
   cout << "Clearing multiSet2" << endl;
   multiSet2.clear();
   cout << "Multiset2: " << multiSet2 << endl;

   //toVector, toArray, getSize functions
   vector<int> multiSetV;
   int *multiSetA;
   multiSet.toVector(multiSetV); //NOTE_TO_SELF: These will work after I fix it
   multiSet.toArray(multiSetA);
   int multiSetSize = multiSet.getSize();
   cout << "Vector: {";
   for(int i = 0; i < multiSetSize; i++) {
      if(i+1 != multiSetSize) { 
         cout << multiSetV[i] << ", ";
      }
      else { //then it is the last element in the vector
         cout << multiSetV[i] << "}" << endl;
      }
   }
   cout << "Array: {";
   for(int i = 0; i < multiSetSize; i++) {
      if(i+1 != multiSetSize) { 
         cout << multiSetA[i] << ", ";
      }
      else { //then it is the last element in the vector
         cout << multiSetA[i] << "}" << endl;
      }
   }
}