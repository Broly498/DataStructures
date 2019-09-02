#pragma once

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <memory>
#include <new>
#include <iostream>

namespace containers
{
template<typename T>
struct Node
{
	Node() = delete;
	Node(const T& data) : Data{ data } {}
	Node(const T&& data) : Data{ data } {}

	Node* Next{ nullptr };
    Node* Previous{ nullptr };
	T Data;
};

template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList() = default; // Complete

    DoublyLinkedList(const DoublyLinkedList& other) { RecurseAndCopy(other.head_); }

	~DoublyLinkedList() // Complete
	{
		if (!IsEmpty())
		{
			Clear();
			head_ = nullptr;
		}
	}

	bool IsEmpty() const { return head_ == nullptr; } // Complete

	size_t GetSize() const { return size_; } // Complete

	bool InsertFront(const T& data) // Complete
	{
		bool success;

		try
		{
			auto newNode = new Node<T>(data);
			newNode->Next = head_;
			head_ = newNode;
            
            auto nextNode = head_->Next;
            if (nextNode)
                newNode->Previous = head_;

			success = true;
			++size_;
		}
		catch (std::bad_alloc& e)
		{
			std::cout << "Allocation Failed: " << e.what() << std::endl;
			success = false;
		}

		return success;
	}

	bool InsertBack(const T& data) // Complete
	{
		bool success;

		if (IsEmpty())
			success = InsertFront(data);
		else
			success = IterateAndInsert(data);

		return success;
	}

	T* Front() const // Complete
	{
		T* front{ nullptr };

		if (!IsEmpty())
			front = &head_->Data;

		return front;
	}

	T* Back() const // Complete
	{
		T* back{ nullptr };

		if (!IsEmpty())
			back = IterateAndRetreiveBack();

		return back;
	}

	void ForwardPrint() const // Complete
	{
		std::cout << "Front --> [";
		IterateAndForwardPrint();
		std::cout << "] <-- Back";
	}

	void ReversePrint() const // Complete
    {
        std::cout << "Front --> [";
        IterateAndReversePrint(head_);
        std::cout << "] <-- Back";
    }

	bool Clear()
	{
		bool success;

		if (IsEmpty())
			success = false;
		else
			success = RecurseAndErase(head_);

		head_ = nullptr;

		return success;
	}

	std::pair<std::unique_ptr<T[]>, size_t> GetArray() const
	{
		std::unique_ptr<T[]> arrayOut{ nullptr };
		
		if (!IsEmpty())
		{
			size_t arrayIndex = 0;
			arrayOut = std::make_unique<T[]>(size_);
            RecurseAndCreateArray(head_, arrayOut.get(), arrayIndex);
        }

		return std::make_pair(std::move(arrayOut), size_);
	}

protected:
private:
	bool IterateAndInsert(const T& data) // Complete
	{
		bool success;

		try
		{
            auto currentNode = head_;
            
            while (currentNode)
            {
                if (!currentNode->Next)
                {
                    auto newNode = new Node<T>(data);
                    newNode->Previous = currentNode;
                    currentNode->Next = newNode;
                    success = true;
                    ++size_;
                }

                currentNode = currNode->NextNode;
            }
		}
		catch (std::bad_alloc& e)
		{
			std::cout << "Allocation Failed: " << e.what() << std::endl;
			success = false;
		}

		return success;
	}

	T* IterateAndRetreiveBack() const // Complete
	{
		T* back{nullptr};

        auto currentNode = head_;

        while (currentNode)
        {
            if (!currentNode->Next)
                back = &currentNode->Data;

            currentNode = currentNode->Next;
        }

		return back;
	}

	void IterateAndForwardPrint() const // Complete
	{
        auto currentNode = head_;

        while (currentNode)
        {
            std::cout << currentNode->Data;

            if (currentNode->Next)
                std::cout << ", ";

            currentNode = currentNode->Next;
        }
	}

	void RecurseAndReversePrint(Node<T>* currentNode) const
	{
        if (currentNode)
        {
            RecurseAndReversePrint(currentNode->Next);
            std::cout << currentNode->Data;
            
            if (currentNode != head_)
                std::cout << ", ";
        }
	}

	bool RecurseAndErase(Node<T>* currentNode)
	{
		bool success;

		if (currentNode->Next != nullptr)
			RecurseAndErase(currentNode->Next);

		delete currentNode;
		--size_;
		success = true;

		return success;
	}

	void RecurseAndCopy(Node<T>* currentNode)
	{
		if (currentNode->Next != nullptr)
			RecurseAndCopy(currentNode->Next);

		InsertFront(currentNode->Data);
	}

    void RecurseAndCreateArray(Node<T>* currentNode, T* arrayIn, size_t& indexIn) const
    {
        arrayIn[indexIn++] = currentNode->Data;

        if (currentNode->Next)
            RecurseAndCreateArray(currentNode->Next, arrayIn, indexIn);
    }

	Node<T>* head_{ nullptr };
	size_t size_{ 0 };
};
}

#endif