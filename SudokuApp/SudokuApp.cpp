// SudokuApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include "../SudokuLib/Sudoku.h"

#define Sudoku9x9 Sudoku<9,4> 
#define Sudoku16x16 Sudoku<16,4> 
#define Sudoku25x25 Sudoku<25,5>
#define Sudoku36x36 Sudoku<36,6>

uint32_t getInt(const char c) throw()
{
	switch (c)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		throw 1;
		break;
	}
}

uint32_t parseInt(const std::string& s) throw()
{
	uint32_t result = 0;
	for (uint32_t i = 0; i < s.length(); i++)
	{
		result += getInt(s[i]) * 10 * i;
	}
	return result;
}

std::vector<uint32_t> split(const std::string& string, const char del)
{
	std::vector<uint32_t> vec;
	std::string str = "";
	int n;
	uint32_t j = 0, i = 0, result = 0, base = 1;
	while (i < string.length())
	{
		result = 0;
		j = 0;
		base = 1;
		while (i < string.length() && string[j] != del)
		{
			result += getInt(string.c_str()[i]) * base;
			base *= 10;
			i++;
			j++;
		}
		vec.push_back(result);
		str = "";
		i++;
	}
	return vec;
}

bool isQuadratNumber(uint32_t i)
{
	return uint32_t(sqrt(i)) * uint32_t(sqrt(i)) == i;
}

void waitOnEnd()
{
	std::string s = "1";
	std::getline(std::cin, s);
	while (s.length() > 0)
	{
		std::getline(std::cin, s);
	}
}

int main()
{
	std::string line;

	try
	{
		std::cout << "--Sudoku-Solver--" << std::endl;
		Sudoku<9, 4> s = Sudoku<9, 4>();

		std::cout << "Bitte das Spielfeld Zeile fuer Zeile eingeben: " << std::endl;
		std::vector<uint32_t> vec;
		uint32_t i = 0;
		while (i < 9)
		{
			//std::cin.ignore();
			std::getline(std::cin, line);
			std::cout << "\r" << std::flush;
			vec = split(line, ',');
			line = "";
			for (uint32_t j = 0; j < vec.size(); j++)
			{
				s.setSudokuValue(i, j, vec[j]);
			}
			i++;
		}

		std::cout << "Loese Spielfeld: " << std::endl;
		std::cout << s.toString().c_str() << std::endl;
		Report r = s.solve();
		std::cout << std::flush;
		std::cout << "Ergebnis: " << std::endl;
		std::cout << s.toString().c_str() << std::endl;
		std::cout << std::flush;
		std::cout << "Valid: " << r.m_valid << " Versuche: " << r.m_numberOfTest << " in " << r.m_time << " ms und " << s.byteSize() << " Bytes." << std::endl;
		std::cout << std::flush;

		waitOnEnd();
	}
	catch (...)
	{
		std::cout << "Fehler!" << std::endl;
	}
	return 0;
}

