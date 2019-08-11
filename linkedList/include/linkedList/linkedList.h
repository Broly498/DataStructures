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

	bool Insert(const T& data)
	{
		bool success;

		try
		{
			auto newNode = new Node<T>(data);
			newNode->Next = head_;
			head_ = newNode;
			success = true;
		}
		catch (std::bad_alloc& e)
		{
			std::cout << "Allocation Failed: " << e.what() << std::endl;
			success = false;
		}

		return success;
	}

	const T& Peek() const { return head_->Data; }

protected:
private:
	Node<T>* head_{nullptr};
};

#endif