 /*
 * Copyright (c) 2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         mem_block_cache.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: memory block cache used by the non-recursive matcher.
  */

#ifndef BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP
#define BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP

#include <new>
#include <boost/atomic/atomic.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

struct mem_block_cache
{
   boost::atomic<void*> cache[BOOST_REGEX_MAX_CACHE_BLOCKS];

   mem_block_cache() {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       cache[i].store(NULL);
     }

   }
   ~mem_block_cache()
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       if (cache[i].load()) ::operator delete(cache[i].load());
     }
   }
   void* get()
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       void* p = cache[i].load();
       if (p != NULL) {
         if (cache[i].compare_exchange_strong(p, NULL)) return p;
       }
     }
     return ::operator new(BOOST_REGEX_BLOCKSIZE);
   }
   void put(void* ptr)
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       void* p = cache[i].load();
       if (p == NULL) {
         if (cache[i].compare_exchange_strong(p, ptr)) return;
       }
     }
     ::operator delete(ptr);
   }
};

extern mem_block_cache block_cache;

}
} // namespace boost

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif

