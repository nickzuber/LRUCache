/**
 * The MIT License (MIT)

 * Copyright (c) 2016 Nick Zuber
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _LRU_CACHE 
#define _LRU_CACHE 

#include <map>
#include "dataObject.h"
#include <iostream> /* @TESTING */
#include <string> /* @TESTING */

namespace _LRU_CACHE {
  template <typename _Key, 
            typename _Data>
    class LRUCache
    {

      public:
        typedef _Key                                    key_type;
        typedef _Data                                   data_type;
        typedef std::unique_ptr<_Key>                   key_ptr;
        typedef std::unique_ptr<_Data>                  data_ptr;
        typedef Data_Object<_Data>                      data_object;
        typedef std::unique_ptr<Data_Object<_Data>>     data_object_ptr;
        
        /**
         *  @brief  Default constructor creates empty cache.
         */
        LRUCache( void )
          : _size( 0 ) ,
          _intern_keymap( new std::map< key_type , data_object_ptr > ) ,
          _dispose_func( NULL ) ,
          _head( NULL ) ,
          _tail( NULL )
          { };
        
        /**
         *  @brief  Single parameter constructor sets max size.
         *  @param  _M_s  An input for max size
         */
        LRUCache( const size_t& _M_s )
          : _size( _M_s ) ,
          _intern_keymap( new std::map< key_type , data_object_ptr > ) ,
          _dispose_func( NULL ) ,
          _head( NULL ) ,
          _tail( NULL )
          { };
        
        /**
         *  @brief  Double parameter constructor sets max size and dispose callback function.
         *  @param  _M_s  An input for max size
         *  @param  _F_p  A callback function
         */
        LRUCache( const size_t& _M_s , void ( *_F_p ) ( void ) )
          : _size( _M_s ) , 
          _intern_keymap( new std::map< key_type , data_object_ptr > ) , 
          _dispose_func( _F_p ) ,
          _head( NULL ) ,
          _tail( NULL )
          { };

        void
          set( const key_type& _K_t , const data_type& _D_t )
          {
            // Create new element with input data
            data_object _Do_t( _D_t );

            // Check if tail is set.. if not configure routine
              // Set head
              // Set tail

            // Check if cache is full.. if so call del() and continue

            // Update new entry as newest element
              // A[head]->newer = new entry
              // head = new entry.KEY

            // Insert new element into internal map
            this->_intern_keymap.get()->insert( std::make_pair( _K_t , data_object_ptr( new data_object( _Do_t ) ) ) );
            // @TEST  return key value
            std::cout << *this->_intern_keymap.get()->at(_K_t)->get_data() << std::endl;
          }

        data_type
          get( const key_type& _K_t ) const;

        data_type
          peek( const key_type& _D_t ) const;

        void
          del( const key_type& _K_t );

        void
          reset( void );

        size_t
          size( void ) const;

      private:
        size_t _size;
        std::unique_ptr< std::map< key_type, data_object_ptr > > _intern_keymap;
        void ( *_dispose_func ) ( void );
        key_ptr _head;
        key_ptr _tail;

    };
};

#endif /* _LRU_CACHE */