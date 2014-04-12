// Ŭnicode please
#pragma once

//http://blog.daum.net/aswip/4538253
//문자열 해쉬함수 모음 (String Hash Function) 
namespace qb {;
struct RSHash {
	static unsigned int Hash(const std::string &str);
};

struct JSHash {
	static unsigned int Hash(const std::string &str);
};

// P. J. Weinberger Hash Function
struct PJWHash {
	static unsigned int Hash(const std::string &str);
};

struct ELFHash {
	static unsigned int Hash(const std::string &str);
};


struct BKDRHash {
	static unsigned int Hash(const std::string &str);
};

struct SDBMHash {
	static unsigned int Hash(const std::string &str);
};

struct DJBHash {
	static unsigned int Hash(const std::string &str);
};

struct DEKHash {
	static unsigned int Hash(const std::string &str);
};

struct APHash {
	static unsigned int Hash(const std::string &str);
};
}