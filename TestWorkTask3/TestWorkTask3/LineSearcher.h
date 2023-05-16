#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>

//Класс для поиска слов в файле
class LineSearcher
{
private:
	std::vector <std::string> _stringLines; //Список слов
	std::string _filePath; //Путь к файлу

public:
	//Конструктор
	LineSearcher(std::vector <std::string> stringLines, std::string filePath);
	//Поиск и возвращение результатов - количества совпадений
	std::vector<int> Search();
};

