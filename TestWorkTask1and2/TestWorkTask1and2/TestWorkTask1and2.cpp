// TestWorkTask1and2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Weight.h"
#include "Parity.h"


int main()
{
    unsigned x = 98;

    std::cout << "Task 1\n";
    std::cout << "method 1: " << weight1(x) << "\n";
    std::cout << "method 2: " << weight2(x) << "\n";
    std::cout << "method 3: " << weight3(x) << "\n";
    std::cout << "method 4: " << weight4(x) << "\n";
    std::cout << "method 5: " << weight5(x) << "\n";

    std::cout << "\nTask 2\n";
    std::cout << "method 1: " << parity1(x) << "\n";
    std::cout << "method 2: " << parity2(x) << "\n";
    std::cout << "method 3: " << parity3(x) << "\n";
    std::cout << "method 4: " << parity4(x) << "\n";
    std::cout << "method 5: " << parity5(x) << "\n";
}

