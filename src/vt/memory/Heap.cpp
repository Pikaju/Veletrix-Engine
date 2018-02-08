#include "Heap.h"

#include "../Types.h"
#include "../debug/Exception.h"

namespace vt {
	namespace heap {

		i32f blocks;

		void initialize()
		{
			blocks = 0;
		}

		void cleanup()
		{
			if (blocks != 0) {
				log::fatal("There have been ", blocks, " memory leaks");
				exception::crash();
			}
		}

		void* allocate(size_t size)
		{
			blocks++;
			return malloc(size);
		}

		void* allocateZero(size_t size)
		{
			void* block = allocate(size);
			VT_ZERO_MEMORY(block, size);
			return block;
		}

		void* reallocate(void* block, size_t size)
		{
			return realloc(block, size);
		}

		void deallocate(void* block)
		{
			blocks--;
			free(block);
		}

	}
}