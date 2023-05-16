// TestWorkTask1and2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Weight.h"
#include "Parity.h"


int main()
{
    unsigned x = 98;

    std::cout << "Task 1\n";
    std::cout << weight1(x)<<"\n";
    std::cout << weight2(x) << "\n";
    std::cout << weight3(x) << "\n";
    std::cout << weight4(x) << "\n";
    std::cout << weight5(x) << "\n";

    std::cout << "\nTask 2\n";
    std::cout << parity1(x) << "\n";
    std::cout << parity2(x) << "\n";
    std::cout << parity3(x) << "\n";
    std::cout << parity4(x) << "\n";
    std::cout << parity5(x) << "\n";
}

