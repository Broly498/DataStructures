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
	T Data;
};

template <typename T>
class LinkedList
{
public:
	LinkedList() = default;

	LinkedList(const LinkedList& other) { RecurseAndCopy(other.head_); }

	~LinkedList()
	{
		if (!IsEmpty())
		{
			Clear();
			head_ = nullptr;
		}
	}

	bool IsEmpty() const { return head_ == nullptr; }

	size_t GetSize() const { return size_; }

	bool InsertFront(const T& data)
	{
		bool success;

		try
		{
			auto newNode = new Node<T>(data);
			newNode->Next = head_;
			head_ = newNode;
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

	bool InsertBack(const T& data)
	{
		bool success;

		if (IsEmpty())
			success = InsertFront(data);
		else
			success = RecurseAndInsert(head_, data);

		return success;
	}

	T* Front() const
	{
		T* front{ nullptr };

		if (!IsEmpty())
			front = &head_->Data;

		return front;
	}

	T* Back() const
	{
		T* back{ nullptr };

		if (!IsEmpty())
			back = RecurseAndRetreiveBack(head_);

		return back;
	}

	void ForwardPrint() const
	{
		std::cout << "Front --> [";
		RecurseAndForwardPrint(head_);
		std::cout << "] <-- Back";
	}

	void ReversePrint() const
    {
        std::cout << "Front --> [";
        RecurseAndReversePrint(head_);
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
	bool RecurseAndInsert(Node<T>* currentNode, const T& data)
	{
		bool success;

		if (currentNode->Next != nullptr)
		{
			success = RecurseAndInsert(currentNode->Next, data);
		}
		else
		{
			try
			{
				auto newNode = new Node<T>(data);
				currentNode->Next = newNode;
				success = true;
				++size_;
			}
			catch (std::bad_alloc& e)
			{
				std::cout << "Allocation Failed: " << e.what() << std::endl;
				success = false;
			}
		}

		return success;
	}

	T* RecurseAndRetreiveBack(Node<T>* currentNode) const
	{
		T* back{nullptr};

		if (currentNode->Next != nullptr)
			back = RecurseAndRetreiveBack(currentNode->Next);
		else
			back = &currentNode->Data;

		return back;
	}

	void RecurseAndForwardPrint(Node<T>* currentNode) const
	{
		std::cout << currentNode->Data;

		if (currentNode->Next != nullptr)
		{
			std::cout << ", ";
			RecurseAndForwardPrint(currentNode->Next);
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