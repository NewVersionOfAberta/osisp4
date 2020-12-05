#pragma once

#include <string>
#include "ItemThreadPool.h"

class FileSorter
{
	public:
		FileSorter(unsigned int threadCount) : m_threadPool(threadCount, threadCount) {}
		void SortFileData(const std::string& inputFileName, const std::string& outputFileName);
	private:
		void SortString(std::vector<std::string>& str);
		int SortStringParts(std::vector<std::string>& str, unsigned int splitSize);
		void MergeString(std::vector<std::string>& str, unsigned int splitSize);

		std::vector<std::string> ReadFileToStringsArr(const std::string& fileName);
		void WriteStringsToFile(const std::vector<std::string> str, const std::string& fileName);

		ItemThreadPool m_threadPool;
};

