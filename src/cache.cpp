/**
 * 
 * 
 * 
 */

#include "cache.h"

  template <typename _Key , typename _Data>
    void
      LRUCache<_Key, _Data>::set( _Data data )
      {
        this->_intern_keymap->get();
      }
