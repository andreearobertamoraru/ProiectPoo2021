#pragma once

#include<iostream>
#include<vector>
class Utils {
public:
	static std::vector<std::string> splitVector(std::vector<std::string> v, int indexStart, int indexEnd)
	{
		std::vector<std::string> newVector;
		for (int i = indexStart; i < indexEnd; i++)
		{
			newVector.push_back(v[i]);
		}
		return newVector;
	}
	static std::string subVectorToString(std::vector<std::string> v, int indexStart, int indexEnd)
	{
		std::string str;
		for (int i = indexStart; i < indexEnd; i++)
		{
			str += v[i] + " ";
		}
		return substring(str, 0, str.length() - 1);
	}
	static std::vector<std::string> splitString(std::string str, char delimiter, bool lower)
	{
		std::vector<std::string> tokens;
		std::string temp;
		for (char letter : str)
		{
			if (letter == delimiter)
			{
				tokens.push_back(temp);
				temp = "";
			}
			else
			{
				if (lower)
					letter = tolower(letter);
				temp += letter;
			}
		}
		if (temp != "")
			tokens.push_back(temp);
		return tokens;
	}
	static char** splitStringChar(std::string str, char delimiter, bool lower, int& nrTokens)
	{
		void* pointer;
		char** matrixArgs = nullptr;
		pointer = (char**)malloc(2 * sizeof(char*));

		if (pointer != nullptr)
			matrixArgs = (char**)pointer;

		std::string temp;
		for (char letter : str)
		{
			if (letter == delimiter)
			{
				if (matrixArgs != nullptr) {
					matrixArgs[nrTokens] = (char*)malloc((temp.length() + 1) * sizeof(char));
					strcpy_s(matrixArgs[nrTokens++], temp.length() + 1, temp.c_str());
				}
				pointer = realloc(matrixArgs, (2 + nrTokens) * sizeof(char*));
				if (pointer != nullptr)
					matrixArgs = (char**)pointer;
				temp = "";
			}
			else
			{
				if (lower)
					letter = tolower(letter);
				temp += letter;
			}
		}
		if (temp != "") {
			if (matrixArgs != nullptr) {
				matrixArgs[nrTokens] = (char*)malloc((temp.length() + 1) * sizeof(char));
				if (matrixArgs[nrTokens] != nullptr)
					strcpy_s(matrixArgs[nrTokens++], temp.length() + 1, temp.c_str());
			}
			pointer = (char**)realloc(matrixArgs, (2 + nrTokens) * sizeof(char*));
			if (pointer != nullptr)
				matrixArgs = (char**)pointer;
		}
		return matrixArgs;
	}
	static std::string substring(std::string str, int indexStart, int indexEnd)
	{
		std::string newStr;
		if (indexEnd > str.length())
			indexEnd = str.length();
		for (int i = indexStart; i < indexEnd; i++)
			newStr += str[i];
		return newStr;
	}
	static std::string vectorToString(std::vector<std::string> v)
	{
		std::string str;
		for (int i = 0; i < v.size(); i++)
			str += v[i] + " ";
		return str;
	}
	static std::string intToString(int number)
	{
		std::string str = "";
		str += (char)(number + '0');
		return str;
	}
	static std::string toLower(std::string str)
	{
		std::string toLowerStr;

		for (char letter : str)
		{
			toLowerStr += tolower(letter);
		}
		return toLowerStr;
	}
	static std::string toUpper(std::string str)
	{
		std::string toUpperStr;

		for (char letter : str)
		{
			toUpperStr += toupper(letter);
		}
		return toUpperStr;
	}
	static bool isNumber(std::string str)
	{
		for (char letter : str)
			if (!isdigit(letter))
				return false;
		return true;
	}
	static std::string strip(std::string str)
	{
		std::string newStr;
		int i = 0;
		int j = str.size() - 1;
		while (str[i] == ' ')
			i++;
		while (str[j] == ' ')
			j--;
		for (int idx = i; idx <= j; idx++)
			newStr += str[idx];
		return newStr;
	}
	static bool print(bool success, std::string message) {
		if (message != "")
			std::cout << message << std::endl;
		return success;
	}
	static void afisareMatriceChar(char** matrix, int size) {
		for (int i = 0; i < size; i++)
			std::cout << matrix[i] << '\n';
	}
};
