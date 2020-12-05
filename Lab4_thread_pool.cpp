// Lab4_thread_pool.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include "FileSorter.h"


#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

int main()
{
    int threadCount = 12;


    FileSorter fileSorter(threadCount);

    fileSorter.SortFileData(INPUT_FILE_NAME, OUTPUT_FILE_NAME);


    return 0;
}
