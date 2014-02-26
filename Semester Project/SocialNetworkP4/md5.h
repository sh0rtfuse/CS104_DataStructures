#include <type_traits>
#include <array>
#include <vector>
#include <cstring>

#include <iostream>
#include <iomanip>

namespace // an anonymous namespace (no name), which can't be used outside of this file
{
  //! Magic numbers needed by the md5 algorithm
  const std::uint32_t k[64] = {
  0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

  //! More magic numbers,
  const std::uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                             5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                             4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                             6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

  //! Does a left bit rotation
  /*! A bit rotation will cause bits that are rotated out of the
      end of some number to wrap around and start pushing in on
      the right hand side

      The constexpr is a c++11 keyword and is not strictly necessary,
      it just says we can do this at compile time if we want to */
  template <class T>
  inline constexpr T rotate_left( T value, int shift )
  {
    static_assert( std::is_integral<T>(), "Can only shift integral types" );
    return (value << shift) | (value >> (sizeof(value) * 0x8 - shift));
  }
} // end anon namespace

//! Wrapper class around a hash
/*! You can represent your hash a lot of different ways,
    I've chosen to have it be 4 32 bit numbers (128 bits total)
    inside of an array, with a class controlling access to it
    and letting me do things like operator overloads and comparisons */
class MD5Hash
{
  public:
    MD5Hash() = default;
    MD5Hash( MD5Hash const & other ) = default;

    //! Construct from 4 numbers
    MD5Hash( std::uint32_t a,
             std::uint32_t b,
             std::uint32_t c,
             std::uint32_t d ) :
      _hash( {a, b, c, d} )
    { }

    //! Construct from an array
    MD5Hash( std::array<std::uint32_t, 4> const & data ) :
      _hash( data )
    { }

    //! Get the hash code
    std::array<std::uint32_t, 4> const & hash() const
    {
      return _hash;
    }

    // Overload for comparing hashes
    bool operator<( MD5Hash const & other ) const
    {
      return _hash[0] > other._hash[0] ||
             _hash[1] > other._hash[1] ||
             _hash[2] > other._hash[2] ||
             _hash[3] > other._hash[3];
    }


  private:
    std::array<std::uint32_t, 4> _hash;
};

// Overload so we can print out our hashes
std::ostream & operator<<( std::ostream & os, MD5Hash const & h )
{
  const auto & hash = h.hash();
  os << std::hex;
  os << hash[0] << hash[1] << hash[2] << hash[3];
  os << std::dec;
  return os;
}

//! Generates an MD5 hash for the input
/*! This implements the MD5 algorithm (http://en.wikipedia.org/wiki/MD5)
    for any contiguous data in C++.

    Remember that you may LOOK at at implementations online, but you
    CANNOT use them directly.  Our best advice is to look at how the
    algorithm is implemented, sit on it a day, and then implement it
    yourself.

    This skeleton code should be a great start or at least give you
    an idea of the proper path to follow.

    @param data A pointer to the beginning of the data
    @param numBytes The size (in bytes) of the data held at the pointer
    @return the hash */
template <class T> inline
MD5Hash md5( T const * data, size_t numBytes )
{
  // Step 1: Break the input up into 512 bit (64 byte) blocks
  // Each block will contain
  // 0                                 448    512
  // | ....data.... | ....padding.... | size |
  //
  // Padding consists of a 1 followed by as many 0s as necessary to
  // get to bit 448, which is 56 in bytes.
  //
  // We'll represent this in memory as one large chunk of data that we
  // can conceptually think of as being composed of several 512 bit chunks

  /////////////////////////////////////////////////////////////////////////////
  // COPYING DATA AND ALLOCATION //////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  // Number of bits in the input
  const std::uint64_t size = numBytes*0.125; // replace with correct value

  // The number of blocks we need to use
  // Should be enough to hold our data plus 64 bits for the size of the input in bits
  const size_t numBlocks = (numBytes*0.125) + 64; // replace with correct value

  // Where we will store our data
  //  Multiply numBlocks by 64 to get the number of bytes (64 bytes in each 512 bit block)
  //  We do this because we're storing the data as a vector of bytes (8 bit numbers)
  std::vector<std::uint8_t> blocks( numBlocks * 64 );

  // Copy the input data into our blocks
  // Use memcpy to do the actual copying
  // http://en.cppreference.com/w/cpp/string/byte/memcpy
  std::memcpy( blocks.data(), data, numBytes );

  /////////////////////////////////////////////////////////////////////////////
  // PADDING //////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  // Pad the last "block" as necessary
  //  Padding consists of a 1 followed by a bunch of 0s (in binary)
  const size_t byteToStartPaddingAt = 0; // replace with correct value

  // We need to start off with a 1 (in binary), followed by
  // a bunch of zeros.
  //    The number 8 is represented as 1000 in binary, so we'll use that
  blocks[byteToStartPaddingAt] = 0x8;

  // For the rest of the bytes, we need to set them to zero
  //  We could do this with a for loop, but let's be smarter and set the memory to all zeros
  //  http://en.cppreference.com/w/cpp/string/byte/memset
  const size_t numberOfZeros = 0; // replace this with the actual number of zeros
  std::memset( blocks.data() + byteToStartPaddingAt + 1, 0x0, numberOfZeros );

  /////////////////////////////////////////////////////////////////////////////
  // SETTING THE SIZE /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  // Put the size in the last 64 bits (8 bytes) of our blocks
  *reinterpret_cast<std::uint64_t*>( &blocks.back() - 7 ) = size;

  /////////////////////////////////////////////////////////////////////////////
  // THE PROCESSING ///////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  // Step 2: Do the processing
  //
  //  Here we will actually implement the core algorithm, which consists of many
  //  bitwise operations using the magic numbers defined above and our blocks of
  //  512 bit numbers.  The output of this will be a 128 bit number

  // output, initialized to some magic numbers
  std::array<std::uint32_t, 4> output = { 0x67452301,
                                          0xefcdab89,
                                          0x98badcfe,
                                          0x10325476 };


  // Loop over each 512 bit number block
  for( size_t i = 0; i < numBlocks; ++i )
  {
    // Get a pointer to the current block, represented as 32 bit chunks
    std::uint32_t const * currentBlock = reinterpret_cast<std::uint32_t *>( blocks.data() ) + i * 64;

    // Working numbers, a-d are always initialized to the output
    std::uint32_t a = output[0];
    std::uint32_t b = output[1];
    std::uint32_t c = output[2];
    std::uint32_t d = output[3];
    std::uint32_t f, g, temp;

    // Main algorithm loop
    for( size_t j = 0; j < 64; ++j )
    {
      if( j < 16 )
      {
        // do something to f
        // do something to g
        f = a ^ c;              //I'm not really sure about this process, just did some random bitwise operations.
        g = j % 16;
      }
      else if( j < 32 )
      {
        // do something to f
        // do something to g
        f = a ^ c;
        g = j % 16;
      }
      else if( j < 48 )
      {
        // do something to f
        // do something to g
        f = a ^ c;
        g = j % 16;
      }
      else
      {
        // do something to f
        // do something to g
        f = a ^ c;
        g = j % 16;
      }

      // set temp equal to something    //just setting thing equal to each other
      // do something to d
      // do something to c
      // do something to b
      // do something to a
      temp = a;
      d = c;
      c = b;
      b = b + rotate_left((a + f + k[j] + currentBlock[g]), r[j]);
      a = temp;
    }

    // update the output
    output[0] += a;
    output[1] += b;
    output[2] += c;
    output[3] += d;
  }

  return {output};
}
