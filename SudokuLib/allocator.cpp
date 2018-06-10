#include "stdafx.h"
#include "allocator.h"

/*
namespace ds
{
	Allocator::Allocator()
	{
	}

	Allocator::~Allocator()
	{
	}

	void * Allocator::allocate(uint32_t numBytes)
	{
		return malloc(numBytes);
	}

	void Allocator::free(void * ptr)
	{
		free(ptr);
	}

	void * Allocator::alignedAllocate(uint32_t numBytes, uint32_t alignement)
	{
		return _aligned_malloc(alignement, numBytes);
	}

	void Allocator::alignedFree(void * ptr)
	{
		_aligned_free(ptr);
	}
	MyAllocator::MyAllocator() : m_ptr(nullptr), m_size(0), m_aligned(false)
	{

	}
	MyAllocator::MyAllocator(uint32_t sizeInBytes, uint32_t alignement, bool aligned = false) : m_ptr(nullptr), m_size(0), m_aligned(false)
	{
		m_aligned = aligned;
		m_size = sizeInBytes;
		if (sizeInBytes > 0)
		{
			if (aligned)
			{
				m_ptr = malloc(sizeInBytes);
			}
			else
			{
				m_ptr = _aligned_malloc(alignement, sizeInBytes);
			}
		}
	}
	MyAllocator::~MyAllocator()
	{
		if (m_ptr)
		{
			if (m_aligned)
			{
				_aligned_free(m_ptr);
			}
			else
			{
				free(m_ptr);
			}
		}
	}
	void * MyAllocator::allocate(uint32_t numBytes)
	{
		if (numBytes > m_nextFree)
		{
			return alloc(numBytes);
		}
		m_ptr += m_nextFree;
		return m_ptr + m_nextFree;
	}
	void MyAllocator::free(void * ptr)
	{
		if (m_aligned) throw 1;
	}
	void * MyAllocator::alignedAllocate(uint32_t numBytes, uint32_t alignement)
	{
		return nullptr;
	}
	void MyAllocator::alignedFree(void * ptr)
	{
		if (!m_aligned) throw 1;
	}
}
*/