#include "Parity.h"
#include "Weight.h"
#include <iostream>
#include <bitset>
// ������� 2
//���������� �������

//C����� 1 (������ ����� ������� weight � ����������� �������� �� ��������)
int parity1(unsigned x)
{
	int weight = weight3(x);
	return weight % 2;
}


//C����� 2 (����� ����������� ��� ��������������� �� ���� ����� �����)
int parity2(unsigned x)
{
	//Size of ���������� � ������, � ����� �������� � �����
	unsigned byteSize = sizeof(unsigned) * 8; //������ ���� ������

	unsigned parity = ((1 << 0) & x); //��������� �������� - �������� 0 ����

	for (int d = 1; d < byteSize; d++)
	{
		parity ^= ((1 << d) & x) ? 1 : 0;
	}

	return parity;
}


//C����� 3 (����� ����������� ��� � ������� �������)
int parity3(unsigned x)
{
	// ����������� ������� ����� �� ��� ������
	// ����� ������� � ����� �� ����������� ��� �� ��� ���, ���� �� ��������� ������ 1 ���

	x = (x & 0x0000FFFF) ^ (x >> 16);
	x = (x & 0x000000FF) ^ (x >> 8);
	x = (x & 0x0000000F) ^ (x >> 4);
	x = (x & 0x00000003) ^ (x >> 2);
	x = (x & 0x00000001) ^ (x >> 1);

	// ������� 1, ���� ���������� ��������� ���; � ��������� ������ ������� 0
	return x & 1;
}

//C����� 4 (����� ����������� ��� �� � �������������� bitset)
int parity4(unsigned x)
{
	unsigned const byteSize = sizeof(unsigned) * 8; //������ ���� ������

	std::bitset<byteSize> bs = x; //������������������ �����

	unsigned parity = bs.test(0);
	
	for (int i = 1; i < byteSize; i++)
	{
		parity ^= bs.test(i);
	}
	
	return parity;
}


//������ 5 (��������� ������������� ����������� �������� ����� ����� �������� (������ ������ ��� ����))
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
