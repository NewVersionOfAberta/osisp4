// Lab4_thread_pool.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include "FileSorter.h"

#include <stdio.h>
#include <thread>
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

int main()
{
    int maxThreadCount = std::thread::hardware_concurrency();
    bool isNotCorrect;
    int threadCount;
    do {
        isNotCorrect = false;
        threadCount = 0;
        std::cout << "Enter amount of threads from: "<< 1 << " to " << maxThreadCount << std::endl;
        std::cin >> threadCount;
        if ((threadCount < 1) || (threadCount > maxThreadCount)) {
            isNotCorrect = true;
            std::cout << "Incorrect input." << std::endl;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INT_MAX,'\n');
            }
        }
    } while (isNotCorrect);

    FileSorter fileSorter(threadCount);

    fileSorter.SortFileData(INPUT_FILE_NAME, OUTPUT_FILE_NAME);


    return 0;
}
