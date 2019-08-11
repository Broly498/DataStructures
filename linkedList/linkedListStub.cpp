#include "linkedList/linkedList.h"

#include <array>
#include <memory>
#include <new>
#include <vector>

template <typename T1, typename T2>
bool CompareData(T1* array1, size_t array1Size, T2* array2, size_t array2Size)
{
	bool success = true;

	if (array1Size == array2Size)
	{
		for (auto it = 0; it < array1Size; ++it)
		{
			if (array1[it] != array2[it])
			{
				success &= false;
				break;
			}
		}
	}
	else
	{
		success = false;
	}

	return success;
}

template <typename T1, typename T2>
void ForwardPrintData(const T1* const data, const T2& size)
{
	for (auto it = 0; it < size; ++it)
	{
		std::cout << data[it];

		if (it < size - 1)
			std::cout << ", ";
	}
}

int main()
{
	std::cout << "*******************************************" << std::endl;
	std::cout << "*****Beginning Linked List Test Matrix*****" << std::endl;
    std::cout << "*******************************************" << std::endl;
    std::cout << std::endl;

	std::cout << "*******************************************" << std::endl;
	std::cout << "****Beginning Test #1: Stack Allocation****" << std::endl;
	std::cout << "*******************************************" << std::endl;

	try
	{
	std::cout << "\nTest #1: Creating Linked List...";

	auto container = containers::LinkedList<int>();

	std::cout << "\nTest #1: SUCCESS...\n\n";

	std::cout << "*******************************************" << std::endl;
	std::cout << "****Beginning Test #2: Front Insertion*****" << std::endl;
	std::cout << "*******************************************" << std::endl;

	std::cout << "\nTest #2: Inserting Elements to the Front of the List...";
	std::cout << "\nTest #2: Sample Input: First --> [";

    std::vector<int> testTwoInputs = { 1, 2, 3, 4, 5 };
	ForwardPrintData(testTwoInputs.data(), testTwoInputs.size());

	std::cout << "] <-- Last";

	for (auto it = 0; it < testTwoInputs.size(); ++it)
	{
		bool success = container.InsertFront(testTwoInputs[it]);

		if (success)
		{
			std::cout << "\nTest #2: Successfully Inserted [" << *container.Front() << "]";
		}
		else
		{
			std::cout << "\nTest #2: FAILURE...";
			std::cout << "\nTest #2: Insertion Failed[" << testTwoInputs[it] << "]";
			return 1;
		}
	}

	std::cout << "\nTest #2: Expected Output: Front --> [";

    auto testTwoOutputs = testTwoInputs;
    std::reverse(testTwoOutputs.begin(), testTwoOutputs.end());
	ForwardPrintData(testTwoOutputs.data(), testTwoOutputs.size());

	std::cout << "] <-- Back";

	std::cout << "\nTest #2: Actual Output:   ";
	container.ForwardPrint();

    {
        auto containerData = container.GetArray();
        if (CompareData(testTwoOutputs.data(), testTwoOutputs.size(), containerData.first.get(), containerData.second))
        {
            std::cout << "\nTest #2: SUCCESS...\n\n";
        }
        else
        {
            std::cout << "\nTest #2: FAILURE...";
            std::cout << "\nTest #2: Actual Output Differs From Expected Output\n";
            return 1;
        }
    }

	std::cout << "*******************************************" << std::endl;
	std::cout << "*****Beginning Test #3: Back Insertion*****" << std::endl;
	std::cout << "*******************************************" << std::endl;

	std::cout << "\nTest #3: Inserting Elements to the Back of the List...";
	std::cout << "\nTest #3: Sample Input: First --> [";

    std::vector<int> testThreeInputs = { 6, 7, 8, 9, 10 };
	ForwardPrintData(testThreeInputs.data(), testThreeInputs.size());

	std::cout << "] <-- Last";

	for (auto it = 0; it < testThreeInputs.size(); ++it)
	{
		bool success = container.InsertBack(testThreeInputs[it]);

		if (success)
		{
			std::cout << "\nTest #3: Successfully Inserted [" << *container.Back() << "]";
		}
		else
		{
			std::cout << "\nTest #3: FAILURE...";
			std::cout << "\nTest #3: Insertion Failed[" << testThreeInputs[it] << "]";
			return -1;
		}
	}

	std::cout << "\nTest #3: Expected Output: Front --> [";

    auto testThreeOutputs = testTwoInputs;
    std::reverse(testThreeOutputs.begin(), testThreeOutputs.end());
    testThreeOutputs.insert(testThreeOutputs.end(), testThreeInputs.begin(), testThreeInputs.end());
    ForwardPrintData(testThreeOutputs.data(), testThreeOutputs.size());

	std::cout << "] <-- Back";

	std::cout << "\nTest #3: Actual Output:   ";
	container.ForwardPrint();

    {
        auto containerData = container.GetArray();
        if (CompareData(testThreeOutputs.data(), testThreeOutputs.size(), containerData.first.get(), containerData.second))
        {
            std::cout << "\nTest #3: SUCCESS...\n\n";
        }
        else
        {
            std::cout << "\nTest #3: FAILURE...";
            std::cout << "\nTest #3: Actual Output Differs From Expected Output\n";
        }
    }

	std::cout << "**********************************************" << std::endl;
	std::cout << "*****Beginning Test #4: Copy Construction*****" << std::endl;
	std::cout << "**********************************************" << std::endl;

	std::cout << "\nTest #4: Copying Linked List...";

	auto containerCopy = container;

	std::cout << "\nTest #4: Original Contents:   ";
	container.ForwardPrint();

	std::cout << "\nTest #4: Copied Contents:     ";
	containerCopy.ForwardPrint();

    {
        auto originalContents = container.GetArray();
        auto copiedContents = containerCopy.GetArray();

        if (CompareData(originalContents.first.get(), originalContents.second, copiedContents.first.get(), copiedContents.second))
        {
            std::cout << "\nTest #4: SUCCESS...\n\n";
        }
        else
        {
            std::cout << "\nTest #4: FAILURE...";
            std::cout << "\nTest #4: Actual Output Differs From Expected Output\n";
        }
    }

    std::cout << "**********************************************" << std::endl;
    std::cout << "*****Linked List Contents: Forward Order******" << std::endl;
    std::cout << "**********************************************" << std::endl;
    std::cout << std::endl;

	container.ForwardPrint();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "**********************************************" << std::endl;
    std::cout << "*****Linked List Contents: Reverse Order******" << std::endl;
    std::cout << "**********************************************" << std::endl;
    std::cout << std::endl;

    container.ReversePrint();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "*******************************************" << std::endl;
    std::cout << "******Linked List Test Matrix Complete*****" << std::endl;
    std::cout << "*******************************************" << std::endl;
    }
	catch (...)
	{
		std::cout << "\nTest #1: FAILURE...";
		std::cout << "\nTest #1: Unknown Failure Occurred...";
	}

	return 0;
}