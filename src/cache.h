/**
 * 
 * 
 * 
 */

#ifndef _LRU_CACHE 
#define _LRU_CACHE 

#include <map>
#include <utility>
#include <memory>

namespace _LRU_CACHE {
  template <typename _Key, 
            typename _Data>
    class LRUCache
    {

      public:
        typedef _Key                       key_type;
        typedef _Data                      data_type;
        typedef std::unique_ptr<_Data>     data_pointer;
        
        LRUCache( void )
          : _size( 0 ) , _intern_keymap( new std::map< key_type , data_type > )
          { };
        
        LRUCache( size_t _M_s )
          : _size( _M_s ) , _intern_keymap( new std::map< key_type , data_type > )
          { };

		    void
          set( data_type data );
        
        data_type
          get( key_type key );
        
        data_type
          peek( key_type data );

        bool
          del( key_type key );

        void
          reset( void );

        size_t
          size();

      private:

        size_t _size;
        std::unique_ptr< std::map< key_type, data_type > > _intern_keymap;

    };
};

#endif /* _LRU_CACHE */