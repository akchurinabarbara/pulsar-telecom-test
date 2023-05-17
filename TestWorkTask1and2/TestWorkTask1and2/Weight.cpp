#include "Weight.h"
#include <bitset>
//Задание 1
//реализация функций

//Cпособ 1 (перевод из 10чной системы счисления в 2чную вручную делением (why not?))
int weight1(unsigned x) 
{
	unsigned count = 0; //Количетсво единичных бит
	unsigned quotient = x; // частное от деления на 2

	while (0 != quotient)
	{
		if (1 == quotient % 2) 
		{
			count++;
		}

		quotient /= 2;
	}

	return count;
}

//Cпособ 2 (Побитовое смещение и наложение на маску)
int weight2(unsigned x)
{
	//Size of возвращает в байтах, а нужно значение в битах
	unsigned byteSize = sizeof(unsigned) * 8; //Размер типа данных

	unsigned count = 0; //Количетсво единичных бит
	
	for (int d = byteSize - 1; d >= 0; d--) 
	{
		if ((1 << d) & x) count++;
	}

	return count;
}

//Cпособ 3 (Встроенный класс bitset)
int weight3(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //Размер типа данных

	std::bitset<byteSize> bs = x; //Последовательность битов

	return bs.count(); //Количетсво единичных бит
}

//Способ 4 (Побитовое сравнение числа и его значения на 1 меньше (потмоу что интересно было разобраться))
int weight4(unsigned x)
{
	unsigned count = 0;
	unsigned value = x;

	while (value) 
	{
		count++;
		value &= (value - 1);
	}

	return count;
}

//Способ 5 (Сумма всех цифр в двоичном числе)
int weight5(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //Размер типа данных

	std::bitset<byteSize> bs = x; //Последовательность битов

	unsigned count = 0;

	for (int i = 0; i < byteSize; i++) 
	{
		count += bs.test(i);
	}

	return count;
}
