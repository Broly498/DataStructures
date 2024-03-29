#pragma once

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <memory>
#include <new>
#include <iostream>

template<typename T>
struct Node
{
	Node() = delete;
	Node(const T& data) : Data{data} {}

	Node* Next{nullptr};
	T Data;
};

template <typename T>
class LinkedList
{
public:
	LinkedList() = default;
	~LinkedList()
	{
		while (!IsEmpty())
		{
			auto nextNode = head_->Next;
			delete head_;
			head_ = nextNode;
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

	const T Front() const { return head_->Data; }

	const T Back() const { return RecurseAndRetreive(head_); }

	void ForwardPrint() const
	{
		std::cout << "Linked List Contains the Following Elements in Forward Order:" << std::endl;
		RecurseAndForwardPrint(head_);
	}

	void ReversePrint() const
	{
		std::cout << "Linked List Contains the Following Elements in Reverse Order:" << std::endl;
		RecurseAndReversePrint(head_);
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

	const T RecurseAndRetreive(Node<T>* currentNode) const
	{
		T data;

		if (currentNode->Next != nullptr)
			data = RecurseAndRetreive(currentNode->Next);
		else
			data = currentNode->Data;

		return data;
	}
	
	void RecurseAndForwardPrint(Node<T>* currentNode) const
	{
		std::cout << "Data:" << currentNode->Data << std::endl;

		if (currentNode->Next != nullptr)
			RecurseAndForwardPrint(currentNode->Next);
	}
	
	void RecurseAndReversePrint(Node<T>* currentNode) const
	{
		if (currentNode->Next != nullptr)
			RecurseAndReversePrint(currentNode->Next);

		std::cout << "Data:" << currentNode->Data << std::endl;
	}


	Node<T>* head_{nullptr};
	size_t size_{0};
};

#endif