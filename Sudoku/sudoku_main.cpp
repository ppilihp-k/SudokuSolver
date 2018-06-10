// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "../SudokuLib/array.h"
#include "../SudokuLib/Sudoku.h"

int main()
{
	Sudoku s = Sudoku(9);
	
	std::cout << s.m_sudoku->height() << std::endl;
	for (uint32_t j = 0; j < 9; j++)
	{
		std::cout << &s.m_rows[j] << std::endl;
	}

	s.setSudokuValue(0, 0, 1);
	s.solve();
	std::cout << s.toString().c_str() << std::endl;

	while (1);
	std::cout << "Programm ende" << std::endl;
	return 0;
}