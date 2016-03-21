
#include "../src/cache.h"
#include <iostream>
#include <string>

void callbackFunction(){
  std::cout << "Entry evicted!" << std::endl;
}

int main(){
  _LRU_CACHE::LRUCache<int, std::string> cache(10);

  int key = 21;
  std::string val = "some value";

  cache.set(key, val);

  return EXIT_SUCCESS;
}