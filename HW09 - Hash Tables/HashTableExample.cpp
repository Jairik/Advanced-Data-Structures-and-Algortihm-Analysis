#include <cstdlib>
#include <ctime>
#include <iostream>

#include "HashTable.h"

/*-----------------------------------------------------------------------------
  Author: JJ McCauley (original file provided by Dr. Spickler)
  Creation Date: 5/10/24
  Description: Demo to showcase the new HashTable
  Notes: Added a re-hashing of size 7 to mimic the expected output.
-----------------------------------------------------------------------------*/

using namespace std;

int hf(int &val) { return val; }

int main() {
  srand(time(0));

  HashTable<int> table(10, hf);

  table.insert(437543);
  table.insert(3284);
  table.insert(234);
  table.insert(11111);
  table.insert(1103);

  table.print();
  cout << endl;
  cout << table.find(3284) << endl;
  cout << table.find(123456) << endl;
  cout << table.find(1103) << endl;

  table.remove(1103);
  cout << table.find(1103) << endl;
  cout << endl;

  cout << table.find(22) << endl;
  cout << endl;

  table.print();
  cout << endl;

  table.rehash(17);
  table.print();
  cout << endl;

  cout << table.find(3284) << endl;
  cout << table.find(123456) << endl;
  cout << table.find(1103) << endl;

  /*----------------------------------
    Added to mimic expected output 
    ----------------------------------*/
  cout << endl;
  table.rehash(7);
  table.print();
  cout << endl;

  return 0;
}
