#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SudokuLib/Sudoku.h"
#include <assert.h>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_Array)
		{
			uint32_t i = 0;
			uint32_t result = 0;
			uint32_t mask = 64 - 1;
			uint32_t mod = 64;
			uint32_t number;

			for (uint32_t i = 0; i < 10000; i++)
			{
				number = rand();
				Assert::AreEqual(number & mask, number % mod);
			}
		}

		std::string intToBinaryString32(uint32_t integer)
		{
			std::string s;
			for (uint32_t i = 0; i < 32; i++)
			{
				s += (integer & (uint32_t(1) << i) ? "1" : "0");
			}
			return s;
		}

		std::string intToBinaryString64(uint64_t integer)
		{
			std::string s;
			for (uint32_t i = 0; i < 64; i++)
			{
				s += (integer & (uint64_t(1) << i) ? "1" : "0");
			}
			return s;
		}

		TEST_METHOD(Test_Tables)
		{
			for (uint32_t i = 0; i < 32; i++)
			{
				Logger::WriteMessage((std::to_string(i) + ": " + intToBinaryString32(ds::s_maskTable32[i]) + "\n").c_str());
			}
			for (uint32_t i = 0; i < 64; i++)
			{
				Logger::WriteMessage((std::to_string(i) + ": " + intToBinaryString64(ds::s_maskTable64[i]) + "\n").c_str());
			}
		}
	};
}