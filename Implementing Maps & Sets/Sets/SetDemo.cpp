#include <iostream>
#include <vector>
#include "Set.h"

using namespace std;

/* ----------------------------- Main File - Set Demo ----------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/23/24
   Description: Aims to test the functionality of the set.
   User Interface: Terminal-based
   -------------------------------------------------------------------------------- */

int main() {

   cout << "-------------Set-------------" << endl << endl;
   Set<int> set; //Making the set
    
   //Testing if the set is empty
   bool setIsEmpty = set.isEmpty(); 
   if(setIsEmpty) {
      cout << "Set is made and empty" << endl << endl;
   }

   //Inserting elements into a set
   cout << "Inserting elements into set (0-7)" << endl;
   for(int i = 0; i < 7; i++) {
      set.insert(i);
   }
   if(set.find(1)) {
      cout << set << endl << endl; //Printing the set
   }

   //Erasing and inserting
   set.insert(1); //duplicate
   set.insert(5); //duplicate
   set.insert(12);
   cout << set << endl << endl;
   set.erase(2);
   set.erase(15);
   cout << set << endl << endl;

   //Making a new set (segfaulting?)
   Set<int> set2 = set;
   cout << "New set made" << endl << endl;

   /*Logical operators 
   if(set == set2) {
      cout << "The sets are equal" << endl;
   } 
   //set2.erase(2);
   if(set != set2) {
      cout << "Erased 2, sets are now not equal" << endl;
   }
   if(set > set2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set < set2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set > set2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set < set2) {
      cout << "___ is a strict subset of ___" << endl;
   }
   if(set >= set2) {
      cout << "___ is a subset of ___" << endl;
   }
   if(set <= set2) {
      cout << "___ is a subset of ___" << endl;
   } 
   
   //+, *, - operators
   Set<int> setIntersection = set * set2;
   cout << "Intersection of the two sets: " << setIntersection << endl;
   Set<int> setUnion = set + set2;
   cout << "Union of the two sets: " << setUnion << endl;
   Set<int> setDifference = set - set2;
   cout << "Difference of the two sets: " << setDifference << endl; 

   //Clear function
   cout << "Clearing set2" << endl;
   set2.clear();
   cout << "Multiset2: " << set2 << endl; */

   //toVector, toArray, getSize functions
   vector<int> setV;
   int *setA;
   set.toVector(setV); //NOTE_TO_SELF: These will work after I fix it
   set.toArray(setA);
   int setSize = set.getSize();
   cout << "Vector: {";
   for(int i = 0; i < setSize; i++) {
      if(i+1 != setSize) { 
         cout << setV[i] << ", ";
      }
      else { //then it is the last element in the vector
         cout << setV[i] << "}" << endl;
      }
   }
   //Unexpected output
   cout << "Array: {";
   for(int i = 0; i < setSize; i++) {
      if(i+1 != setSize) { 
         cout << setA[i] << ", ";
      }
      else { //then it is the last element in the vector
         cout << setA[i] << "}" << endl;
      }
   }

   //Initiating segfault...

   }