#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <math.h>
#include"LineSearcher.h"

//Задание 3. Многопоточный поиск строк в файлах 

//struct index файла и вектор результата
struct SearchResult 
{
	std::string FilePath;
	std::vector <int> Result;

	SearchResult(std::string filePath, std::vector <int> result) 
	{
		FilePath = filePath;
		Result = result;
	}
};

 //Основное тело потока
std::vector <SearchResult> SearchThread(std::vector<std::string> stringLines, std::vector <std::string> filesPaths)
{
	std::vector <SearchResult> result;

	//Поиск по файлам, обрабатываемых в потоке
	for (std::string filePath : filesPaths)
	{
		LineSearcher* ls = new LineSearcher(stringLines, filePath);
		result.push_back(SearchResult(filePath, ls->Search()));
	}

	return result;
}

int main()
{
	//Cписки слов и файлов можно редактировать и дополнять
	//Список слов
	std::vector<std::string> stringLines
	{
		"dd d",
		"eee"
	};

	//Список файлов
	std::vector<std::string> files
	{
		"testFiles/file1.txt",
		"testFiles/file2.txt",
		"testFiles/file3.txt",
		"testFiles/file4.txt",
	};

	//определение количества потоков, поддерживаемое железом компьютера
	unsigned maxThreads = std::thread::hardware_concurrency();

	std::vector<SearchResult> results;
	std::vector<std::future<std::vector <SearchResult>>> returns;

	//Определить количество файлов на поток, чтобы обработать в одном потоке несколько файлов, в зависимости от ограничений процессора по количеству потоков 
	int threadFileCount = std::ceil((float)files.size() / maxThreads);

	//Вектор обрабатываемых в потоке файлов
	std::vector<std::string> treadFiles;
	//Начальный индекс
	int fileIndex = 0;


	//Генерировать потоки, пока не обработаются все файлы
	while (fileIndex < files.size())
	{
		treadFiles.clear();

		//Правая граница копирования элементов вектора искомых строк 
		int nextIndex = fileIndex + threadFileCount;
		//Если она больше границ самого вектора - ограничить границами
		if (nextIndex > files.size())
		{
			nextIndex = files.size();
		}

		//Выделить вектор обрабатываемых в текущем потоке файлов
		treadFiles.insert(treadFiles.begin(), files.begin() + fileIndex, files.begin() + nextIndex);

		//Увеличить индекс для обработки следующей пачки файлов
		fileIndex = nextIndex;

		//Создать поток обработки файлов и получить результаты по готовности
		returns.push_back(std::async(&SearchThread, stringLines, treadFiles));
	}


	//Получение результатов от потоков
	for (std::future<std::vector <SearchResult>>& ret : returns)
	{
		std::vector <SearchResult> joinResults = ret.get();

		results.insert(results.end(), joinResults.begin(), joinResults.end());
	}


	//Вывод результатов
	printf("|-------------------------------------------------------------------|\n");
	printf("|     NameLine     |          NameFile        |    Quantity Line    |\n");
	printf("|-------------------------------------------------------------------|\n");

	for (int i = 0; i < results.size(); i++)
	{
		for (int j = 0; j < results[i].Result.size(); j++)
		{
			printf("| %16s | %24s | %20u|\n", stringLines[j].c_str(), results[i].FilePath.c_str(), results[i].Result[j]);
		}
	}

	printf("|-------------------------------------------------------------------|\n");
}