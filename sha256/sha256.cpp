// sha256.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "picosha2.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

using namespace std;

struct blockheader {
	char payload[16];
	unsigned int nonce;
	unsigned int timestamp;
};

int main(int argc, const char * argv[]) {
	blockheader block;
	strncpy_s(block.payload, "Hello, World!xx\0", 16);
	block.timestamp = 1519640946;
	block.nonce = 43040045;

	std::string hash_hex_str;

	picosha2::hash256_hex_string((unsigned char *)&block, (unsigned char *)&block + sizeof(block), hash_hex_str);
	std::cout << hash_hex_str << std::endl;

	return 0;
}