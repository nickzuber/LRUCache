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
  template <typename _Data>
    class Data_Object
    {

      public:
        typedef _Data                 data_type;
        typedef _Data*                data_ptr;
        typedef Data_Object*          self_ptr;

        /**
         *  @brief  Default constructor creates empty object.
         */
        Data_Object( void )
          : _data( NULL ) ,
          _older( NULL ) ,
          _newer( NULL )
          { };

        /**
         *  @brief  Single parameter constructor sets internal data.
         *  @param  _D_t  An input for internal data
         */
        Data_Object( data_type _D_t )
          : _data( data_ptr( new data_type( _D_t ) ) ) ,
          _older( NULL ) ,
          _newer( NULL )
          { };

        void
          set_data( const data_type& _D_t )
          {
            this->_data = data_ptr( new data_type( _D_t ) );
          }

        void
          set_newer( const data_type& _D_t )
          {
            this->_newer = self_ptr( new Data_Object( _S_p ) );
          }

        void
          set_older( const self_ptr& _S_p )
          {
            this->_older = self_ptr( new Data_Object( _S_p ) );
          }

        data_ptr
          get_data( void ) const
          {
            return this->_data;
          }

      private:
        data_ptr _data;
        self_ptr _older; /* May not need */
        self_ptr _newer;
    };
};

#endif /* _DATA_OBJECT */
