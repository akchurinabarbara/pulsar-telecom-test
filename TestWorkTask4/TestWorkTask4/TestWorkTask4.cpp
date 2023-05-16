#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <filesystem> 
#include <fstream> 

namespace fs = std::filesystem;

//Задание 4. 16-битная контрольная сумма

    //полином x16 + x15 + x12 + x10 + x7 + x6 + x5 + x3 + x2 + 1 
    //равен 1001010011101101 = 0x94ED

//Вычисление 16битной суммы для файла 
//Табличный (быстрый) расчет стандартного (ARC) CRC-16
unsigned short Crc16(unsigned char* pcBlock, unsigned short len, unsigned short CRCTable[256])
{
    //начальное значение
    unsigned short crc = 0x0000;

    while (len--)
        crc = (crc >> 8) ^ CRCTable[(crc & 0xFF) ^ *pcBlock++];

    return crc;
}

//Расчет Modbus CRC-16
unsigned short ModRTU_CRC(unsigned char* pcBlock, unsigned short len)
{
    //начальное значение
    unsigned short crc = 0x0000;

    for (int pos = 0; pos < len; pos++) {
        crc ^= pcBlock[pos];

        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0x94ED; //Полином
            }
            else
                crc >>= 1;
        }
    }
    // Помните, что младший и старший байты поменяны местами
    return crc;
}

int main()
{
    //Имя директории, файлы которой будут обрабатываться (лежит в папке исходников)
    std::string dirName = "testFiles";

    //генерация таблицы 
    unsigned short CRCTable[256];

    for (int x = 0; x < 0x100; x++) {
        unsigned short _crc = x;
        for (int y = 0; y < 8; y++) {
            _crc = (_crc & (1 << 15)) ? ((_crc << 1) ^ 0x94ED) : (_crc << 1);
        }
        CRCTable[x] = _crc;
    }

    //Вектор имен файлов
    std::vector<std::string> fileNames;
    fs::path tempP;

    for (auto& p : fs::directory_iterator(dirName))
    {
        //Получить путь содержимого каталога
        tempP = (fs::path)p;

        //Проверить, что это не подкаталог и положить в вектор путей
        if (!fs::is_directory(tempP)) 
        {
            fileNames.push_back(tempP.generic_string());
        }
    }

    //Сортировка по алфавиту
    std::sort(fileNames.begin(), fileNames.end());

    //Подсчет CRC-16 для каждого файла
    for (std::string fileName : fileNames) 
    {
        std::ifstream infile(fileName, std::ios_base::binary);

        //Получаем размер файла
        // если курсор в начале файла, перемещаем курсор в конец файла.
        infile.seekg(0, std::ios::end);
        // функция выдаст конечное положнние курсора относительно начала файла в байтах.
        int sizef = infile.tellg();
        // возвращаем курсор в начало файла.
        infile.seekg(0, std::ios::beg);

        std::vector<unsigned char> buffer;
        buffer.resize(sizef+1);

        //Чтение из файла в буффер
        while (!infile.eof()) 
        {
            buffer.push_back(infile.get());
        }

        infile.close();

        //Подсчет 16-ти битной контрольной суммы 2-мя способами
        unsigned short resCRC16 = Crc16(&buffer[0], buffer.size(), CRCTable);
        unsigned short resModrtuCRC = ModRTU_CRC(&buffer[0], buffer.size());

        //Вывод результата
        std::cout << fileName << ": (ARC) CRC-16 = " << resCRC16  << "; Modbus = " << resModrtuCRC <<";\n";
    }
}
