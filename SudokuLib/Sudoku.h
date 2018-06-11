#pragma once
#include <unordered_map>
#include "array.h"
#include <string>
#include <chrono>
#include <intrin.h>
#include <immintrin.h>

class Report
{
public:
	bool m_valid;
	uint32_t m_numberOfTest = 0;
	double m_time = 0.0;
};

template<uint32_t t_length, uint32_t t_tau>
class Sudoku
{
private:
	/*
	unsortierte Felder
	*/
	uint32_t m_blockLength;
	uint32_t m_tau;

	uint32_t quadrantRow(uint32_t i) const;
	uint32_t quadrantCol(uint32_t j) const;
	uint32_t quadrant(uint32_t i, uint32_t j);
	bool contains(const ds::FixedSizeArray<t_length, uint32_t(1)>& array, uint32_t number) const;
	void addNumber(ds::FixedSizeArray<t_length, uint32_t(1)>& array, uint32_t value);
	void removeNumber(ds::FixedSizeArray<t_length, uint32_t(1)>& array, uint32_t value);
	bool containsAllNumbers(const ds::FixedSizeArray<t_length, uint32_t(1)>& array) const;
	bool solve(uint32_t i, uint32_t j, Report &report);
	bool test(Report& report) const;
	void resetValue(uint32_t i, uint32_t j, uint32_t value);
	bool setValue(uint32_t i, uint32_t j, uint32_t value, Report& report);
	bool setValue(uint32_t i, uint32_t j, uint32_t value);
	bool isBaseValue(uint32_t i, uint32_t j) const;
	std::pair<uint32_t, uint32_t> nextIndex(uint32_t i, uint32_t j) const;
public:
	//ds::Array2D *m_sudoku, *m_baseValues, *m_qudrantCache;
	ds::FixedSizeArray2D<t_length, t_tau> m_sudoku;
	ds::FixedSizeArray2D<t_length, uint32_t(1)> m_baseValues;
	ds::FixedSizeArray2D<t_length, t_tau> m_qudrantCache;

	//ds::Array *m_columns, *m_rows, *m_blocks;
	ds::FixedSizeArray<t_length, uint32_t(1)> m_columns[t_length], m_rows[t_length], m_blocks[t_length];
	//Sudoku(uint32_t length);
	Sudoku();
	~Sudoku();
	uint32_t length() const;
	void setSudokuValue(uint32_t i, uint32_t j, uint32_t value);
	uint32_t byteSize() const;
	void readFile(const std::string& path);
	Report solve();
	std::string toString() const;
};

template<uint32_t t_length, uint32_t t_tau>
inline uint32_t Sudoku<t_length, t_tau>::quadrantRow(uint32_t i) const
{
	return i / m_blockLength;
};

template<uint32_t t_length, uint32_t t_tau>
inline uint32_t Sudoku<t_length, t_tau>::quadrantCol(uint32_t j) const
{
	return quadrantRow(j);
};

template<uint32_t t_length, uint32_t t_tau>
inline uint32_t Sudoku<t_length, t_tau>::quadrant(uint32_t i, uint32_t j)
{
	uint32_t q = m_qudrantCache.get(i, j);
	if (q != 0) return q;
	uint32_t row = quadrantRow(i);
	uint32_t col = quadrantCol(j);
	uint32_t result = row * m_blockLength + col;
	m_qudrantCache.set(i, j, result);
	return result;
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::contains(const ds::FixedSizeArray<t_length, uint32_t(1)> & array, uint32_t number) const
{
	return array.get(number) == 1;
};

template<uint32_t t_length, uint32_t t_tau>
inline void Sudoku<t_length, t_tau>::addNumber(ds::FixedSizeArray<t_length, uint32_t(1)> & array, uint32_t value)
{
	array.set(value, 1);
};

template<uint32_t t_length, uint32_t t_tau>
inline void Sudoku<t_length, t_tau>::removeNumber(ds::FixedSizeArray<t_length, uint32_t(1)> & array, uint32_t value)
{
	array.set(value, 0);
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::containsAllNumbers(const ds::FixedSizeArray<t_length, uint32_t(1)> & array) const
{
	for (uint32_t i = 1; i < length(); i++)
	{
		if (array.get(i) == 0) return false;
	}
	return true;
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::solve(uint32_t i, uint32_t j, Report & report)
{
	if (i >= length())
	{
		return test(report);
	}
	_mm_prefetch((const char*)&m_columns[i], 1);
	_mm_prefetch((const char*)&m_rows[j], 1);
	_mm_prefetch((const char*)&m_blocks[quadrant(i, j)], 1);

	/*rekursion*/
	std::pair<uint32_t, uint32_t> ni = nextIndex(i, j);
	uint32_t nexti = ni.first, nextj = ni.second;

	if (isBaseValue(i, j))
	{
		return solve(nexti, nextj, report);
	}
	else
	{
		uint32_t k = 1;
		bool s;
		while (k <= length())
		{
			if (setValue(i, j, k, report))
			{
				if (solve(nexti, nextj, report))
				{
					return true;
				}
				else
				{
					resetValue(i, j, k);
				}
			}
			k++;
		}
		return false;
	}
};

template<uint32_t t_length, uint32_t t_tau>
inline Report Sudoku<t_length, t_tau>::solve()
{
	Report report;
	std::chrono::high_resolution_clock::time_point start, end;

	start = std::chrono::high_resolution_clock::now();

	report.m_valid = solve(0, 0, report);

	end = std::chrono::high_resolution_clock::now();
	report.m_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	return report;
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::test(Report& report) const
{
	uint32_t len = length();
	for (uint32_t i = 0; i < len; i++)
	{
		if (!containsAllNumbers(m_blocks[i]))
		{
			return false;
		}
	}
	for (uint32_t i = 0; i < len; i++)
	{
		if (!containsAllNumbers(m_rows[i]))
		{
			return false;
		}
		if (!containsAllNumbers(m_columns[i]))
		{
			return false;
		}
	}
	return true;
};

template<uint32_t t_length, uint32_t t_tau>
inline void Sudoku<t_length, t_tau>::resetValue(uint32_t i, uint32_t j, uint32_t value)
{
	removeNumber(m_rows[i], value);
	removeNumber(m_columns[j], value);
	removeNumber(m_blocks[quadrant(i, j)], value);
	m_sudoku.set(i, j, 0);
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::setValue(uint32_t i, uint32_t j, uint32_t value, Report& report)
{
	if (!Sudoku::contains(m_rows[i], value) && !Sudoku::contains(m_columns[j], value) && !Sudoku::contains(m_blocks[quadrant(i, j)], value))
	{
		addNumber(m_rows[i], value);
		addNumber(m_columns[j], value);
		addNumber(m_blocks[quadrant(i, j)], value);
		m_sudoku.set(i, j, value);
		return true;
	}
	report.m_numberOfTest++;
	return false;
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::setValue(uint32_t i, uint32_t j, uint32_t value)
{
	if (!Sudoku::contains(m_rows[i], value) && !Sudoku::contains(m_columns[j], value) && !Sudoku::contains(m_blocks[quadrant(i, j)], value))
	{
		addNumber(m_rows[i], value);
		addNumber(m_columns[j], value);
		addNumber(m_blocks[quadrant(i, j)], value);
		m_sudoku.set(i, j, value);
		return true;
	}
	return false;
};

template<uint32_t t_length, uint32_t t_tau>
inline bool Sudoku<t_length, t_tau>::isBaseValue(uint32_t i, uint32_t j) const
{
	return m_baseValues.get(i, j) == 1;
};

template<uint32_t t_length, uint32_t t_tau>
inline std::pair<uint32_t, uint32_t> Sudoku<t_length, t_tau>::nextIndex(uint32_t i, uint32_t j) const
{
	uint32_t nexti = j == length() - 1 ? i + 1 : i, nextj = (j + 1) % length();
	//nexti = nexti >= length() ? nexti - 1 : nexti;
	return std::make_pair(nexti, nextj);
};

template<uint32_t t_length, uint32_t t_tau>
inline Sudoku<t_length, t_tau>::Sudoku()
{
	m_tau = uint32_t(ceil(log2(t_length)));
	m_blockLength = uint32_t(ceil(sqrt(t_length)));
	//m_blockLength = uint32_t(ceil(sqrt(length)));
	//m_tau = uint32_t(ceil(log2(length)));

	/*
	m_columns = new ds::Array[length];
	m_rows = new ds::Array[length];
	m_blocks = new ds::Array[length];
	m_qudrantCache = new ds::Array2D(length, length, m_blockLength);

	for (uint32_t i = 0; i < length; i++)
	{
	m_columns[i] = ds::Array(length + 1, 1);
	m_rows[i] = ds::Array(length + 1, 1);
	m_blocks[i] = ds::Array(length + 1, 1);
	}

	m_sudoku = new ds::Array2D(length, length, m_tau);
	m_baseValues = new ds::Array2D(length, length, 1);
	*/
}

template<uint32_t t_length, uint32_t t_tau>
inline Sudoku<t_length, t_tau>::~Sudoku()
{
	/*
	uint32_t len = length();
	if (m_columns) delete[] m_columns;
	if (m_rows) delete[] m_rows;
	if (m_blocks) delete[] m_blocks;
	if (m_sudoku) delete m_sudoku;
	if (m_baseValues) delete m_baseValues;
	*/
};

template<uint32_t t_length, uint32_t t_tau>
inline uint32_t Sudoku<t_length, t_tau>::length() const
{
	return m_sudoku.height();
};

template<uint32_t t_length, uint32_t t_tau>
inline void Sudoku<t_length, t_tau>::setSudokuValue(uint32_t i, uint32_t j, uint32_t value)
{
	setValue(i, j, value);
	if (value != 0) m_baseValues.set(i, j, 1);
};

template<uint32_t t_length, uint32_t t_tau>
inline uint32_t Sudoku<t_length, t_tau>::byteSize() const
{
	return 2 * sizeof(uint32_t) + sizeof(m_sudoku) + sizeof(m_baseValues) + sizeof(m_qudrantCache) + 3 * sizeof(m_columns[0]) * t_length;
};

template<uint32_t t_length, uint32_t t_tau>
inline std::string Sudoku<t_length, t_tau>::toString() const
{
	std::string s = "+";
	for (uint32_t i = 0; i < 2 + length() * 2 + length() / m_blockLength; i++)
	{
		s += "-";
	}
	s += "+\n";
	for (uint32_t i = 0; i < length(); i++)
	{
		for (uint32_t j = 0; j < length(); j++)
		{
			if (j == 0)
			{
				s += "|";
			}
			s += (isBaseValue(i, j) ? " _" : "  ") + std::to_string(m_sudoku.get(i, j));
			if (j == length() - 1)
			{
				s += "|";
			}
		}
		s += "\n";
	}

	s += "+";
	for (uint32_t i = 0; i < length() * 2 + length() / m_blockLength; i++)
	{
		s += "-";
	}
	return s;
};


