
#include "../src/cache.h"
#include <iostream>
#include <string>

void callbackFunction(){
  std::cout << "Entry evicted!" << std::endl;
}

int main(){
  using namespace std;

  _LRU_CACHE::LRUCache<int, string> cache(5);
  
  cache.set(90, "one");
  cache.set(14, "two");
  cache.set(27, "three");
  cache.set(33, "four");
  cache.set(14, "five");
  cache.set(35, "six");
  cache.set(65, "seven");
  
  // peek()
  if( cache.peek(4) != nullptr )
    cout << "Key 4: " << *cache.peek(4) << endl;
  else
    cout << "Key 4: " << "not found" << endl;
  cout << "-------------------------" << endl;

  // size()
  cout << "Size of cache: " << cache.size() << endl;
  cout << "-------------------------" << endl;

  cache.print_cache();
  cout << "-------------------------" << endl;

  cache.set(37, "eight");

  cache.print_cache();
  cout << "-------------------------" << endl;

  // reset()
  cache.reset();
  cout << "Size of cache: " << cache.size() << endl;

  return EXIT_SUCCESS;
}