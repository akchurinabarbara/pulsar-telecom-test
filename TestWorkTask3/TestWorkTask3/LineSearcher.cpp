#include "LineSearcher.h"


//Конструктор
LineSearcher::LineSearcher(std::vector<std::string> stringLines, std::string filePath)
{
	_stringLines = stringLines;
	_filePath = filePath;
}

//Поиск и возвращение результатов - количества совпадений
std::vector<int> LineSearcher::Search()
{
	//вектор результатов по каждой строке
	std::vector<int> result;
	result.resize(_stringLines.size());

	std::ifstream file(_filePath);
	std::string tmp;

	//Получение строки из файла и сравнение ее с писком искомых слов
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
