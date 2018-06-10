#ifndef __ALOCATOR_H__

#define __ALOCATOR_H__

#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
/*
namespace ds
{
	class Allocator
	{
	public:
		Allocator();
		virtual ~Allocator() = 0;
		virtual void* allocate(uint32_t numBytes);
		virtual void free(void *ptr);
		virtual void* alignedAllocate(uint32_t numBytes, uint32_t alignement);
		virtual void alignedFree(void *ptr);
	};

	class MyAllocator : Allocator
	{
	private:
		bool m_aligned;
		uint32_t m_size;
		uint32_t m_nextFree;
		void *m_ptr;
		void* alloc(uint32_t num);
	public:
		MyAllocator();
		MyAllocator(uint32_t sizeInBytes, uint32_t alignement, bool aligned);
		~MyAllocator();
		void* allocate(uint32_t numBytes);
		void free(void *ptr);
		void* alignedAllocate(uint32_t numBytes, uint32_t alignement);
		void alignedFree(void *ptr);
	};
}
*/

#endif