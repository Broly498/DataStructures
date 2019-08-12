#include "linkedList/linkedList.h"

#include <memory>

int main()
{
	std::cout << "**************************************************" << std::endl;
	std::cout << "*********Begining Linked List Container 1*********" << std::endl;
	std::cout << "**************************************************" << std::endl;

	size_t MAX_ITEMS = 3;
	auto container = containers::LinkedList<int>();

	std::cout << "\nLinked List Successfully Created.\n";
	std::cout << "\nBeginning Forward Insertion Test.\n\n";

	for (size_t it = 0; it < MAX_ITEMS; ++it)
	{
		bool success = container.InsertFront(it);

		if (success)
			std::cout << "Successfully Inserted: " << container.Front() << std::endl;
		else
			std::cout << "Insertion Failed: " << it << std::endl;
	}

	std::cout << "\nForward Insertion Test Completed.";
	std::cout << "\nLinked List Size: " << container.GetSize();
	std::cout << "\n\nBeginning Reverse Insertion Test.\n\n";

	for (size_t it = 0; it < MAX_ITEMS; ++it)
	{
		bool success = container.InsertBack(it);

		if (success)
			std::cout << "Successfully Inserted: " << container.Back() << std::endl;
		else
			std::cout << "Insertion Failed: " << it << std::endl;
	}

	std::cout << "\nReverse Insertion Test Completed.";
	std::cout << "\nLinked List Size: " << container.GetSize();
	std::cout << "\n\nBeginning Forward Print Test.\n\n";

	container.ForwardPrint();

	std::cout << "\nForward Print Test Completed.";
	std::cout << "\n\nBeginning Reverse Print Test.\n\n";

	container.ReversePrint();

	std::cout << "\nReverse Print Test Completed.";
	std::cout << "\n\nBeginning Copy-Constructor Test.";

	auto containerCopy = container;

	std::cout << "\n\nCopy-Constructor Test Completed.";
	std::cout << "\nLinked List Size: " << containerCopy.GetSize();
	std::cout << "\n\nBeginning Forward Print Test.\n\n";

	containerCopy.ForwardPrint();

	std::cout << "\nForward Print Test Completed.";
	std::cout << "\n\nBeginning Reverse Print Test.\n\n";

	containerCopy.ReversePrint();

	std::cout << "\nReverse Print Test Completed.";

	container.Clear();
	return 0;
}