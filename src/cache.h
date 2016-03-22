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
#include <stdexcept>
#include <iostream>
#include "dataObject.h"

namespace _LRU_CACHE {
  template <typename _Key, 
            typename _Data>
    class LRUCache
    {

      public:
        typedef _Key                                          key_type;
        typedef _Data                                         data_type;
        typedef std::unique_ptr<_Key>                         key_ptr;
        typedef std::unique_ptr<_Data, _Key>                  data_ptr;
        typedef Data_Object<_Data, _Key>                      data_object;
        typedef std::unique_ptr<Data_Object<_Data, _Key>>     data_object_ptr;
        
        /**
         *  @brief  Default constructor creates empty cache.
         */
        LRUCache( void )
          : _max_size( 0 ) ,
          _intern_keymap( new std::map< key_type , data_object_ptr > ) ,
          _dispose_func( nullptr ) ,
          _head( nullptr ) ,
          _tail( nullptr )
          { };
        
        /**
         *  @brief  Single parameter constructor sets max size.
         *  @param  _M_s  An input for max size.
         */
        LRUCache( const size_t& _M_s )
          : _max_size( _M_s ) ,
          _intern_keymap( new std::map< key_type , data_object_ptr > ) ,
          _dispose_func( nullptr ) ,
          _head( nullptr ) ,
          _tail( nullptr )
          { };
        
        /**
         *  @brief  Double parameter constructor sets max size and dispose callback function.
         *  @param  _M_s  An input for max size.
         *  @param  _F_p  A callback function.
         */
        LRUCache( const size_t& _M_s , void ( *_F_p ) ( void ) )
          : _max_size( _M_s ) , 
          _intern_keymap( new std::map< key_type , data_object_ptr > ) , 
          _dispose_func( _F_p ) ,
          _head( nullptr ) ,
          _tail( nullptr )
          { };

        /**
         *  @brief  Sets cache at given key with given data.
         *  @param  _K_t  A key to insert into cache.
         *  @param  _D_t  Some data to occupy cache location.
         */
        void
          set( const key_type& _K_t , const data_type& _D_t )
          {
            // Purge if cache exceeds capacity
            if( this->_intern_keymap.get()->size() >= this->_max_size )
            {
              this->purge();
            }
            try{
              // Update item if already exists
              auto _exists = this->_intern_keymap.get()->find( _K_t );
              if( _exists != this->_intern_keymap.get()->end() )
              {
                _exists->second->set_data( _D_t );
              
                /// Update this as most recently accessed
                this->get( _K_t );
              }
              // Create new item if it doesn't already exist
              else
              {
                data_object _Do_t( _D_t );
                this->_intern_keymap.get()->insert( std::make_pair( _K_t , data_object_ptr( new data_object( _Do_t ) ) ) );
            
                // If tail isn't set, set it (first entry)
                if( this->_tail == nullptr && this->_head == nullptr )
                {
                  this->_head = key_ptr( new key_type( _K_t ) );
                  this->_tail = key_ptr( new key_type( _K_t ) );
                }
                // If tail is set, update head with new entry
                else if( this->_tail != nullptr && this->_head != nullptr )
                {
                  this->_intern_keymap.get()->at( _K_t )->set_older( new key_type( *this->_head.get() ) ); // nodeToAdd.older = this.head
                  this->_intern_keymap.get()->at( *this->_head.get() )->set_newer( new key_type( _K_t ) ); // this.head->newer = nodeToAdd
                  this->_head = key_ptr( new key_type( _K_t ) ); // this.head = nodeToAdd 
                }
              
                else
                {
                  throw std::logic_error("Unsynced _head and _tail variables in LRUCache.");
                }
              }
            }
            catch( const std::logic_error& e )
            {
              std::cerr << "ERROR: " << e.what() << std::endl;
            }
          };

        /**
         *  @brief  Returns cache item value at given key and updated most recently accessed item.
         *  @param  _K_t  A key to insert into cache.
         *  @return  Returns the item value at given key.
         */
        data_type*
          get( const key_type& _K_t ) const
          {
            return nullptr;
          };

        /**
         *  @brief  Returns a pointer to the value of a key without updating order of cache.
         *  @param  _K_t  A key to access.
         *  @return  Returns a pointer to the value of the given key or nullptr if not found.
         */
        data_type*
          peek( const key_type& _K_t ) const
          {
            return this->_intern_keymap.get()->find( _K_t ) != this->_intern_keymap.get()->end()
              ? this->_intern_keymap.get()->at( _K_t )->get_data()
              : nullptr;
          };

        /** @test
         *  @brief  Prints the _internal_map to the console.
         *
         *  This function is not intended to stick around for production. It's here
         *  to serve as a purpose of testing the LRU cache during development.
         */
        void
          print_cache( void )
          {
            auto element = this->_intern_keymap.get()->find( *this->_tail.get() );
            while( element != this->_intern_keymap.get()->end() )
            {
              std::cout << "key: " << element->first << " | val: " << *element->second->get_data();
              std::cout << " | older: " << (element->second->get_older() == nullptr ? 0 : *element->second->get_older());
              std::cout << " | newer: " << (element->second->get_newer() == nullptr ? 0 : *element->second->get_newer());
              std::cout << std::endl;
              if( element->second->get_newer() == nullptr )
              {
                break;
              }
              else
              {
                element = this->_intern_keymap.get()->find( *(element->second->get_newer()) );
              }
            }
          };

        /**
         *  @brief  Empties the cache and resets private memebers.
         */
        void
          reset( void )
          {
            this->_max_size = 0;
            this->_intern_keymap.get()->clear();
            this->_dispose_func = nullptr;
            this->_head = nullptr;
            this->_tail = nullptr;
          };

        /**
         *  @brief  Returns the amount of entries within the cache.
         *  @return  Returns the amount of size of internal map.
         */
        size_t
          size( void ) const
          {
            return this->_intern_keymap.get()->size();
          };

      private:
        size_t _max_size;
        std::unique_ptr< std::map< key_type, data_object_ptr > > _intern_keymap;
        void ( *_dispose_func ) ( void );
        key_ptr _head;
        key_ptr _tail;

        /**
         *  @brief  Evicts tail item and updates tail.
         */
        void
          purge( void )
          {
            key_ptr _N_t ( this->_intern_keymap.get()->at( *this->_tail.get() )->get_newer() );
            this->_intern_keymap.get()->erase( *this->_tail );
            this->_tail = key_ptr ( new key_type( *_N_t.get() ) );
            this->_intern_keymap.get()->at( *this->_tail.get() )->set_older( nullptr );
          }

    };
};

#endif /* _LRU_CACHE */