// Ŭnicode please
#include <string>
#include "string_hash.h"

namespace qb {;
unsigned int RSHash::Hash(const std::string &str)
{
	unsigned int b    = 378551;
	unsigned int a    = 63689;
	unsigned int hash = 0;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash = hash * a + str[i];
		a    = a * b;
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int JSHash::Hash(const std::string &str)
{
	unsigned int hash = 1315423911;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash ^= ((hash << 5) + str[i] + (hash >> 2));
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int PJWHash::Hash(const std::string& str)
{
	unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
	unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
	unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash              = 0;
	unsigned int test              = 0;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash = (hash << OneEighth) + str[i];
		if((test = hash & HighBits)  != 0) {
			hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash::Hash(const std::string& str)
{
	unsigned int hash = 0;
	unsigned int x    = 0;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash = (hash << 4) + str[i];
		if((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}

	return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
unsigned int BKDRHash::Hash(const std::string& str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash = (hash * seed) + str[i];
	}

	return (hash & 0x7FFFFFFF);
}

// SDBM Hash Function
unsigned int SDBMHash::Hash(const std::string& str)
{
	unsigned int hash = 0;
	for(std::size_t i = 0; i < str.length(); i++) {
		hash = str[i] + (hash << 6) + (hash << 16) - hash;
	}

	return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash::Hash(const std::string& str)
{
	unsigned int hash = 5381;
	for(std::size_t i = 0; i < str.length(); i++) {
		hash = ((hash << 5) + hash) + str[i];
	}

	return (hash & 0x7FFFFFFF);
}

// DEK Hash Function
unsigned int DEKHash::Hash(const std::string& str)
{
	unsigned int hash = static_cast<unsigned int>(str.length());

	for(std::size_t i = 0; i < str.length(); i++) {
		hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
	}

	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash::Hash(const std::string& str)
{
	unsigned int hash = 0;

	for(std::size_t i = 0; i < str.length(); i++) {
		hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] ^ (hash >> 3)) :
			(~((hash << 11) ^ str[i] ^ (hash >> 5)));
	}

	return (hash & 0x7FFFFFFF);
}



}