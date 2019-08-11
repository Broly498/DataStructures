#include "linkedList/linkedList.h"

#include <memory>

int main()
{
	size_t MAX_ITEMS = 100;
	auto container = containers::LinkedList<int>();

	for (size_t it = 0; it < MAX_ITEMS; ++it)
	{
		bool success = container.InsertFront(it);

		if (success)
			std::cout << "Successfully Inserted: " << container.Front() << std::endl;
		else
			std::cout << "Insertion Failed: " << it << std::endl;
	}

	for (size_t it = 0; it < MAX_ITEMS; ++it)
	{
		bool success = container.InsertBack(it);

		if (success)
			std::cout << "Successfully Inserted: " << container.Back() << std::endl;
		else
			std::cout << "Insertion Failed: " << it << std::endl;
	}

	container.ForwardPrint();
	
	container.ReversePrint();

	return 0;
}