/** \file  Memory.h
 *  \brief Provide memory routines that terminate on failure
 */

#include "Memory.h"

#include <cstdlib>
#include <cstring>
#include <cerrno>

#include "Error.h"

void* Memory::xmalloc(std::size_t size) noexcept
{
  /* Ensure we're going to allocate some memory.  */
  if (size == 0)
  {
    size = 1;
  }

  void* result = std::malloc(size);
  if (result == nullptr)
  {
    ERR_CRITICAL_FMT("Unable to allocate memory: %s\n", std::strerror(errno));
  }

  return result;
}

void* Memory::xcalloc(std::size_t nelem, std::size_t elsize) noexcept
{
  /* Ensure we're going to allocate some memory.  */
  if (elsize == 0 || nelem == 0)
  {
    /* Memory we allocate shouldn't be used - so just set it to the smallest
     * amount possible.  */
    elsize = 1;
    nelem = 1;
  }

  void* result = std::calloc(nelem, elsize);
  if (result == nullptr)
  {
    ERR_CRITICAL_FMT("Unable to allocate memory: %s\n", std::strerror(errno));
  }

  return result;
}

void* Memory::xrealloc(void* ptr, std::size_t size) noexcept
{
  /* Ensure we're going to allocate some memory.  */
  if (size == 0)
  {
    size = 1;
  }

  void* result = std::realloc(ptr, size);

  if (result == nullptr)
  {
    /* On failure realloc doesn't free the previously allocated memory.  */
    std::free(ptr);
    ERR_CRITICAL_FMT("Unable to re-allocate memory: %s\n", std::strerror(errno));
  }

  return result;
}

void Memory::xfree(void* ptr) noexcept
{
  std::free(ptr);
}

