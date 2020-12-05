#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "FileSorter.h"

#define SPLIT_SIZE 10

void FileSorter::SortFileData(const std::string& inputFileName, const std::string& outputFileName)
{
	std::vector<std::string> fileContent = ReadFileToStringsArr(inputFileName);
	SortString(fileContent);
	WriteStringsToFile(fileContent, outputFileName);
}

void FileSorter::SortString(std::vector<std::string>& str)
{
	int newSplitSize = SortStringParts(str, SPLIT_SIZE);
	MergeString(str, newSplitSize);
}

int FileSorter::SortStringParts(std::vector<std::string>& str, unsigned int splitSize)
{
	if (str.empty()) {
		return 0;
	}
	int partCount = str.size() / SPLIT_SIZE;
	int leftCount = str.size() % SPLIT_SIZE;

	int currOffset = 0;
	for (int i = 0; i < partCount; i++)
	{
		m_threadPool.SubmitCallbackTask(str.begin() + currOffset, str.begin() + currOffset + SPLIT_SIZE);
		currOffset += SPLIT_SIZE;
	}
	if (leftCount > 0) {
		m_threadPool.SubmitCallbackTask(str.begin() + currOffset, str.begin() + currOffset + leftCount);
	}

	m_threadPool.WaitAndClose();

	return (str.size() < SPLIT_SIZE ? leftCount : SPLIT_SIZE);
}

void FileSorter::MergeString(std::vector<std::string>& str, unsigned int splitSize)
{
	if (str.size() == 0) {
		return;
	}
	int partCount = str.size() / splitSize;
	std::vector<std::string>::iterator curr = str.begin() + splitSize;
	for (int i = 0; i < partCount - 1; i++)
	{
		std::inplace_merge(str.begin(), curr, curr + splitSize);
		curr += splitSize;
	}
}

std::vector<std::string> FileSorter::ReadFileToStringsArr(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	std::string line;
	std::vector<std::string> resultArr;
	while (std::getline(inputFile, line)) {
		resultArr.push_back(line);
	}
	inputFile.close();
	return resultArr;
}

void FileSorter::WriteStringsToFile(const std::vector<std::string> str, const std::string& fileName)
{
	std::ofstream outputFile(fileName);
	for (const auto& value : str) {
		outputFile << value << "\n";
	}
	outputFile.close();
}