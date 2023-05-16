#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>

//����� ��� ������ ���� � �����
class LineSearcher
{
private:
	std::vector <std::string> _stringLines; //������ ����
	std::string _filePath; //���� � �����

public:
	//�����������
	LineSearcher(std::vector <std::string> stringLines, std::string filePath);
	//����� � ����������� ����������� - ���������� ����������
	std::vector<int> Search();
};

