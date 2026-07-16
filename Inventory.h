#pragma once
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class Inventory {
private:
	T* pItems_;
	int capacity_;
	int size_;

public:
	Inventory(int capacity) {
		capacity_ = capacity;
		size_ = 0;
		pItems_ = new T[capacity_];
	}

	bool AddItem(const T& item) {
		if (size_ >= capacity_) {
			return false;
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

