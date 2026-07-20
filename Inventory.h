#pragma once
#include "Item.h"
#include<algorithm>
#include <string>
#include <iostream>
using namespace std;

inline bool compareByPrice(const Item& a, const Item& b) {
	return a.price < b.price;
}

template<typename T>
class Inventory {
private:
	T* pItems_;
	int capacity_;
	int size_;
	void Resize(int newCapacity) {

		T* newItems = new T[newCapacity];
		for (int i = 0; i < size_; i++) {
			newItems[i] = pItems_[i];
		}
		delete[] pItems_;
		pItems_= newItems;
		capacity_ = newCapacity;
	}

public:

	Inventory(int capacity) {
		capacity_ = capacity;
		size_ = 0;
		pItems_ = new T[capacity_];
	}

	bool AddItem(const T& item) {
		if (size_ >= capacity_) {
			int oldCapacity = capacity_;
			Resize(capacity_ * 2);
			cout << "-> 인벤토리 자동 확장! ("
				<< oldCapacity << " -> "
				<< capacity_<< ")" << endl;
		}
		pItems_[size_] = item;
		size_++;
		return true;
	}
	bool RemoveLastItem() {
		if (size_ <= 0) {
			return false;
		}
		size_--;
		return true;
	}

	int GetSize() const {
		return size_;
	}
	int GetCapacity() const {
		return capacity_;
	}

	void SortItems() {
		sort(pItems_, pItems_ + size_, compareByPrice);
	}

	void PrintAllItems() const {
		if (size_ == 0) {
			cout << "인벤토리가 비어있습니다. " << endl;
			return;
		}
		for (int i = 0; i < size_; i++) {
			pItems_[i].PrintInfo();
		}
	}

	Inventory(const Inventory& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[other.capacity_];
		for (int i = 0; i < other.size_;i++) {
			pItems_[i] = other.pItems_[i];
		}
	}

	Inventory& operator = (const Inventory& other) {
		if (this == &other) {
			return *this;
		}

		delete[] pItems_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[other.capacity_];
		for (int i = 0; i < other.size_; i++) {
			pItems_[i] = other.pItems_[i];
		}
		return *this;
	}

			~Inventory() {
			delete[] pItems_;
		}
	};

