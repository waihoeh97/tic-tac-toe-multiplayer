#ifndef UINTPACKER_H
#define UINTPACKER_H

#include <iostream>
#include <Windows.h>

class UIntPacker
{
public:
	UIntPacker();
	~UIntPacker();

	unsigned char pack(unsigned char value, unsigned int bitCount);
	unsigned int unpack(unsigned char data, unsigned int bitCount);
};

#endif // !UINTPACKER_H
