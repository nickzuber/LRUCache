
#include "../src/cache.h"
#include <iostream>
#include <string>
using namespace std;

void callbackFunction(){
  std::cout << "Entry evicted!" << std::endl;
}

int main(){

  _LRU_CACHE::LRUCache<int, string> cache(5);
  
  cache.set(1, "one");
  cache.set(2, "two");
  cache.set(3, "three");
  cache.set(4, "four");
  cache.set(5, "five");
  cache.set(6, "six");
  cache.set(7, "seven");

  cache.print_cache();
  cout << "-------------------------" << endl;

  cache.set(4, "new four");

  //cache.set(5, "new one");

  cache.print_cache();
  cout << "-------------------------" << endl;

  // reset()
  cache.reset();
  cout << "Size of cache: " << cache.size() << endl;


  return EXIT_SUCCESS;
}