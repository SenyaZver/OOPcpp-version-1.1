#pragma once
#include <iostream>



template <typename T>
class Container
{
private:

	template <typename T>
	struct Node {
		T value;
		Node<T>* nextElement;
		Node<T>* previousElement;
	};

	Node<T>* head;
	Node<T>* tail;
	int size;



public:
	Container() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}


	class Iterator {
	private:
		Node<T>* element;

		Node<T>* lastElement = this->tail;

	public:
		Iterator(Node<T>* newElement, Node<T>* newLastElem): element(newElement), lastElement(newLastElem) {}

		void next() {
			if (element == lastElement->nextElement) {
				return;
			}
			element = element->nextElement;
		}

		void previous() {
			if (element->previousElement == nullptr) {
				return;
			}
			if (element == lastElement->nextElement) {
				element = lastElement;
			}
			element = element->previousElement;
		}

		bool operator!= (const Iterator& other) {
			return element != other.element;
		}

		T value() {
			return element->value;
		}

	};

	Iterator begin() {
		return Iterator(this->head, this->tail);
	}
	Iterator end() {
		return Iterator(this->tail->nextElement, this->tail);
	}

	void add_toFront(const T& value) {
		Node<T>* newNode = new Node<T>;
		newNode->nextElement = nullptr;
		newNode->previousElement = nullptr;
		newNode->value = value;

		if (this->size == 0) {
			head = newNode;
			tail = newNode;
			size = 1;
		}
		else {
			newNode->nextElement = head;
			head->previousElement = newNode;
			head = newNode;
			size++;
		}
	}
	void add_toEnd(const T& value) {
		Node<T>* newNode = new Node<T>;
		newNode->nextElement = nullptr;
		newNode->previousElement = nullptr;
		newNode->value = value;

		if (this->size == 0) {
			head = newNode;
			tail = newNode;
			size = 1;
		}
		else {
			newNode->previousElement = tail;
			tail->nextElement = newNode;
			tail = newNode;
			size++;
		}
	}

	void remove_front() {
		if (size == 0) {
			return;
		}
		Node<T>* newHead = head->nextElement;
		delete head;
		head = newHead;

		size--;
	}

	void remove_end() {
		if (head == nullptr) {
			return;
		}
		Node<T>* newTail = tail->previousElement;
		delete tail;

		tail = newTail;
		newTail->nextElement = nullptr;

		size--;
	}

	T  getFirstElem() const {
		return head->value;
	}

	T getLastElem() const{
		return tail->value;
	}

	int getSize() const {
		return size;
	}

	bool isEmpty() const {
		return !head;
	}

	void clear() {
		while (head)
		{
			if (head->nextElement == nullptr) {
				size = 0;
				tail = nullptr;
				head = nullptr;
				return;
			}
			tail = head->nextElement;
			delete head;
			head = tail;
		}
	}

	static void switchContainers(Container& first, Container& second) {
		std::swap(first.head, second.head);
		std::swap(first.tail, second.tail);
		std::swap(first.size, second.size);
	}


	void reverse() {
		Container<T>* reversed = new Container<T>;
		Node<T>* temp = this->tail;


		for (int i = 1; i <= this->size; i++) {
			reversed->add_toEnd(temp->value);

			temp = temp->previousElement;
		}
		this->clear();
		this->head = reversed->head;
		this->tail = reversed->tail;
	}

	~Container() {
		this->clear();
	}


	void printAll() {
		Node<T>* test = this->head;
		while (test != nullptr) {
			std::cout << test->value << std::endl;
			test = test->nextElement;
		}
	}
};