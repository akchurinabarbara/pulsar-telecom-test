#include "LineSearcher.h"


//�����������
LineSearcher::LineSearcher(std::vector<std::string> stringLines, std::string filePath)
{
	_stringLines = stringLines;
	_filePath = filePath;
}

//����� � ����������� ����������� - ���������� ����������
std::vector<int> LineSearcher::Search()
{
	//������ ����������� �� ������ ������
	std::vector<int> result;
	result.resize(_stringLines.size());

	std::ifstream file(_filePath);
	std::string tmp;

	//��������� ������ �� ����� � ��������� �� � ������ ������� ����
	while(getline(file, tmp))
	{
		for (int i = 0; i < _stringLines.size(); i++)
		{
			if (_stringLines[i] == tmp)
			{
				result[i]++;
				break;
			}
		}
	}	

	return result;
}
