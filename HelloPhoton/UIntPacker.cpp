#include "UIntPacker.h"

UIntPacker::UIntPacker()
{

}

UIntPacker::~UIntPacker()
{

}

unsigned char UIntPacker::pack(unsigned char value, unsigned int bitCount)
{
	char data = 0;
	data = (data << bitCount) | value;
	return data;
}

unsigned int UIntPacker::unpack(unsigned char data, unsigned int bitCount)
{
	unsigned int value = data & ((1 << bitCount) - 1);
	data = data >> bitCount;
	return value;
}
