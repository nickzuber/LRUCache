/**
 * 
 * 
 * 
 */

#ifndef _LRU_CACHE 
#define _LRU_CACHE 

#include <map>
#include <memory>

namespace _LRU_CACHE {
  template <typename _Data, 
            typename _Key>
    class LRUCache
    {
      /// Define variable aliases and declare public members
	    public:
        typedef _Data                 data_type;
        typedef _Key                  key_type;
        typedef unique_ptr<_Data>     data_pointer;
        
        LRUCache()
          : _size( NULL ) , _intern_keymap( new std::map< data_type > )
          { };

        LRUCache( size_t max_size )
          : _size( max_size ) , _intern_keymap( new std::map< data_type > )
          { };

		    void
          put( data_type data );
        
        data_type
          get( key_type key );
        
        data_type
          peek( key_type data );

        size_t
          size();

	    private:
        /// Declare private members
        extern size_t _size;
        extern unique_ptr< std::map > _intern_keymap;

    };
};

#endif /* _LRU_CACHE */