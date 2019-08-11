#include "linkedList/linkedList.h"

#include <memory>

int main()
{
	size_t MAX_ITEMS = 100;
	auto container = LinkedList<int>();

	for (size_t it = 0; it < MAX_ITEMS; ++it)
	{
		bool success = container.Insert(it);

		if (success)
			std::cout << "Successfully Inserted: " << container.Peek() << std::endl;
		else
			std::cout << "Insertion Failed: " << it << std::endl;
	}

	return 0;
}