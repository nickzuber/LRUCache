/**
 * The MIT License (MIT)
 * 
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

#ifndef _DATA_OBJECT
#define _DATA_OBJECT

#include <utility>
#include <memory>

namespace _LRU_CACHE {
  template <typename _Data ,
            typename _Key>
    class Data_Object
    {

      public:
        // We use raw pointers here because they're already encased in a smart pointer in LRU_CACHE
        typedef _Data                 data_type;
        typedef _Data*                data_ptr;
        typedef Data_Object*          self_ptr;
        typedef _Key                  key_type;
        typedef _Key*                 key_ptr;

        /**
         *  @brief  Default constructor creates empty object.
         */
        Data_Object( void )
          : _data( nullptr ) ,
          _older( nullptr ) ,
          _newer( nullptr )
          { };

        /**
         *  @brief  Single parameter constructor sets internal data.
         *  @param  _D_t  An input for internal data
         */
        Data_Object( data_type _D_t )
          : _data( data_ptr( new data_type( _D_t ) ) ) ,
          _older( nullptr ) ,
          _newer( nullptr )
          { };

        void
          set_data( const data_type& _D_t )
          {
            this->_data = data_ptr( new data_type( _D_t ) );
          }

        void
          set_newer( const key_ptr& _K_p )
          {
            this->_newer = key_ptr( _K_p );
          }

        void
          set_older( const key_ptr& _K_p )
          {
            this->_older = key_ptr( _K_p );
          }

        data_ptr
          get_data( void ) const
          {
            return this->_data;
          }

        key_ptr
          get_newer( void ) const
          {
            return this->_newer;
          }

        key_ptr
          get_older( void ) const
          {
            return this->_older;
          }

      private:
        data_ptr _data;
        key_ptr _older;
        key_ptr _newer;
    };
};

#endif /* _DATA_OBJECT */
