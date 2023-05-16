#include "Parity.h"
#include "Weight.h"
#include <iostream>
#include <bitset>
// Задание 2
//реализация функций

//Cпособ 1 (Просто вызов функции weight и определение четности ее значения)
int parity1(unsigned x)
{
	int weight = weight3(x);
	return weight % 2;
}


//Cпособ 2 (Через исключающее или последовательно по всем битам числа)
int parity2(unsigned x)
{
	//Size of возвращает в байтах, а нужно значение в битах
	unsigned byteSize = sizeof(unsigned) * 8; //Размер типа данных

	unsigned parity = ((1 << 0) & x); //начальное значение - значение 0 бита

	for (int d = 1; d < byteSize; d++)
	{
		parity ^= ((1 << d) & x) ? 1 : 0;
	}

	return parity;
}


//Cпособ 3 (Через исключающее или и деление пополам)
int parity3(unsigned x)
{
	// рекурсивное деление числа на два равных
	// делим пополам и берем их исключающее или до тех пор, пока не останется только 1 бит

	x = (x & 0x0000FFFF) ^ (x >> 16);
	x = (x & 0x000000FF) ^ (x >> 8);
	x = (x & 0x0000000F) ^ (x >> 4);
	x = (x & 0x00000003) ^ (x >> 2);
	x = (x & 0x00000001) ^ (x >> 1);

	// вернуть 1, если установлен последний бит; в противном случае вернуть 0
	return x & 1;
}

//Cпособ 4 (Через исключающее или но с использованием bitset)
int parity4(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //Размер типа данных

	std::bitset<byteSize> bs = x; //Последовательность битов

	unsigned parity = bs.test(0);
	
	for (int i = 1; i < byteSize; i++)
	{
		parity ^= bs.test(i);
	}
	
	return parity;
}


//Способ 5 (Абсолютно ирациональное определение четности числа через рекурсию (просто потому что могу))
int checkParity(unsigned x) 
{
	if (x < 2) 
	{
		return (x % 2 != 0);
	}
	return (checkParity(x - 2));
}

int parity5(unsigned x)
{
	int weight = weight3(x);

	return checkParity(weight);
}
