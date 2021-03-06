// sha256.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "picosha2.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct blockheader {
	char payload[16];
	unsigned int nonce;
	unsigned int timestamp;
};

// https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
std::vector<unsigned char> HexToBytes(const std::string& hex) {
	std::vector<unsigned char> bytes;

	for (unsigned int i = 0; i < hex.length(); i += 2) {
		std::string byteString = hex.substr(i, 2);
		unsigned char byte = (unsigned char)strtol(byteString.c_str(), NULL, 16);
		bytes.push_back(byte);
	}

	return bytes;
}

// https://stackoverflow.com/questions/14050452/how-to-convert-byte-array-to-hex-string-in-visual-c
template<typename TInputIter>
std::string make_hex_string(TInputIter first, TInputIter last)
{
	std::ostringstream ss;
	ss << std::hex << std::setfill('0');

	while (first != last)
	{
		ss << std::setw(2) << static_cast<int>(*first++);
		
	}
	return ss.str();
}

int main(int argc, const char * argv[]) {
	std::string bytesStr = "f064b8b61422a3456cb273a474a1fb0cabb04200a6a82a9426bd01f56c97fbf8c4ef58634fd5cf21af29e7db3406de4f886fe71408696789f853af9932a84b79";
	//std::string bytesStr = "f0";
	std::vector<unsigned char> bytes = HexToBytes(bytesStr);
	bytes.insert(bytes.begin(), 4, 0);
	std::cout << make_hex_string(bytes.cbegin(), bytes.cend()) << std::endl;
	//std::cout << hexStr((char*)&bytes, bytesStr.length() / 2) << std::endl;

	unsigned char hashed[picosha2::k_digest_size];

	unsigned int* ptr;
	ptr = (unsigned int*) &bytes[0];

	for (unsigned int j = 0; j < 255 * 255 * 255 * 255; j++) {
		(*ptr) = j;
		picosha2::hash256(bytes.begin(), bytes.end(), hashed, hashed + picosha2::k_digest_size);
		if (hashed[picosha2::k_digest_size - 1] == 0xff && hashed[picosha2::k_digest_size - 2] == 0xff) {
			std::cout << make_hex_string(bytes.cbegin(), bytes.cend()) << std::endl;
			std::cout << make_hex_string(hashed, hashed + picosha2::k_digest_size) << std::endl;
			//break;
		}
	}
	std::cout << make_hex_string(bytes.cbegin(), bytes.cend()) << std::endl;
	std::cout << make_hex_string(hashed, hashed + picosha2::k_digest_size) << std::endl;


	blockheader block;
	strncpy_s(block.payload, "Hello, World!xx\0", 16);
	block.timestamp = 1519640946;
	block.nonce = 43040045;

	std::string hash_hex_str;

	picosha2::hash256_hex_string((unsigned char *)&block, (unsigned char *)&block + sizeof(block), hash_hex_str);
	std::cout << hash_hex_str << std::endl;

	return 0;
}