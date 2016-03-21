
#include "../src/cache.h"
#include <iostream>
#include <string>

void callbackFunction(){
  std::cout << "Entry evicted!" << std::endl;
}

int main(){
  _LRU_CACHE::LRUCache<int, std::string> cache(10, callbackFunction);
  return EXIT_SUCCESS;
}