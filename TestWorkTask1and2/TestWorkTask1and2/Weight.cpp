#include "Weight.h"
#include <bitset>
//������� 1
//���������� �������

//C����� 1 (������� �� 10���� ������� ��������� � 2���� ������� �������� (why not?))
int weight1(unsigned x) 
{
	unsigned count = 0; //���������� ��������� ���
	unsigned quotient = x; // ������� �� ������� �� 2

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

//C����� 2 (��������� �������� � ��������� �� �����)
int weight2(unsigned x)
{
	//Size of ���������� � ������, � ����� �������� � �����
	unsigned byteSize = sizeof(unsigned) * 8; //������ ���� ������

	unsigned count = 0; //���������� ��������� ���
	
	for (int d = byteSize - 1; d >= 0; d--) 
	{
		if ((1 << d) & x) count++;
	}

	return count;
}

//C����� 3 (���������� ����� bitset)
int weight3(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //������ ���� ������

	std::bitset<byteSize> bs = x; //������������������ �����

	return bs.count(); //���������� ��������� ���
}

//������ 4 (��������� ��������� ����� � ��� �������� �� 1 ������ (������ ��� ��������� ���� �����������))
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

//������ 5 (����� ���� ���� � �������� �����)
int weight5(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //������ ���� ������

	std::bitset<byteSize> bs = x; //������������������ �����

	unsigned count = 0;

	for (int i = 0; i < byteSize; i++) 
	{
		count += bs.test(i);
	}

	return count;
}
