/*
* Code from Cherno channel (Youtube channel)
* 
* reference code for what happens with dynamic memory allocation
*/

#include<iostream>
#include<memory>

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

// Custom overloaded delete function
void* operator new(size_t size)
{
	s_AllocationMetrics.TotalAllocated += size;

	std::cout << "Allocating " << size << " bytes\n";
	return malloc(size);
}

// Custom overloaded delete function
void operator delete(void* memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;

	std::cout << "Freeing " << size << " bytes\n";
	free(memory);
}

static void PrintMemoryUsage()
{
	std::cout << "Memory Usage " << s_AllocationMetrics.CurrentUsage() << "\n";
}

struct Object
{
	int x, y, z;
};

int main()
{
	PrintMemoryUsage();
	// Dynamic allocation and freeing of string 
	{
		std::string	str = "Hello World\n";
	}

	PrintMemoryUsage();
	// Dynamic allocation, but no freeing of memory for the raw pointer
	{
		Object* o = new Object();
	}

	PrintMemoryUsage();
	// Dynamic allocation and freeing of unique_ptr
	{
		std::unique_ptr<Object> o1 = std::make_unique<Object>();
	}
}
