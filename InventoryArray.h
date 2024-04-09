
#include "Queue.h"
#include "DynamicArray.h"
#include <cassert>

#ifndef INVENTORYARRAY_H
#define INVENTORYARRAY_H

template <typename K, typename V>
class InventoryArray
{

	// node for individual skus
	struct Node1 {
		K key;
		V value;
		int qty = 0;
		Node1* next;
	};

	// node for package skus
	struct Node2 {
		K key;
		V value;
		int aSiz = 0;
		DynamicArray<K> skuArray;
		Node2* next;
	};

	Node1* firstNode1;
	Node2* firstNode2;
	int siz1;
	int siz2;
	int pQty;
	V dummy;


public:
	InventoryArray(); 													// main constructor
	InventoryArray(const InventoryArray<K, V>&);						// copy constructor 
	InventoryArray<K, V>& operator=(const InventoryArray < K, V>&);		// assignment operator 
	~InventoryArray();													// destructor  
	int operator[](const K&) const;										// quantity getter
	int& operator[](const K&);											// quantity setter
	V primary(const K&) const;											// Node 1 getter
	V& primary(const K&);												// Node 1 setter
	V secondary(const K&) const;										// Node 2 value getter  
	V& secondary(const K&);												// Node 2 value setter
	V packageContents(const K&, const K&) const;						// Node 2 -> Node 1 value getter
	V& packageContents(const K&, const K&);								// Node 2 -> Node 1 value setter
	DynamicArray<K> PackageArray(const K&) const;						// package array getter
	bool containsKey(const K&) const;
	bool containsKeyP(const K&) const;
	bool containsKeyS(const K&) const;									// contains key getter
	void deleteKey(const K&);											// delete key setter
	Queue<K> primaryQueue() const;										// individual key queue
	Queue<K> secondaryQueue() const;									// package key queue
	int size() const { return siz1; };									// size
	int sSize() const { return siz2; };
	int aSize(const K&) const;
	void clear();														// clear
};

/*-----------------------------------------

				Constructors

-----------------------------------------*/

// main constructor
template <typename K, typename V>
InventoryArray<K, V>::InventoryArray() {
	firstNode1 = 0; firstNode2 = 0;
	siz1 = 0; siz2 = 0;
	pQty = 0;
	dummy = V();
}

// copy constructor
template <typename K, typename V>
InventoryArray<K, V>::InventoryArray(const InventoryArray<K, V>& original) {
	firstNode1 = 0;
	Node1* lastNode1 = 0;
	firstNode2 = 0;
	siz1 = original.siz1;
	siz2 = original.siz2;
	pQty = 0;
	dummy = V();
	for (Node1* p = original.firstNode1; p; p = p->next) {
		{
			Node1* temp = new Node1;
			temp->key = p->key;
			temp->value = p->value;
			temp->qty = p->qty;
			temp->next = 0;
			if (lastNode1) lastNode1->next = temp;
			else firstNode1 = temp;
			lastNode1 = temp;
		}
	}

	firstNode2 = 0;
	Node2* lastNode2 = 0;
	for (Node2* q = original.firstNode2; q; q = q->next) {
		{
			Node2* temp = new Node2;
			temp->key = q->key;
			temp->value = q->value;
			for (int i = 0; i < siz2; i++) {
				temp->skuArray[i] = q->skuArray[i];
			}
			temp->aSiz = q->aSiz;
			temp->next = 0;
			if (lastNode2) lastNode2->next = temp;
			else firstNode2 = temp;
			lastNode2 = temp;
		}
	}
}

// assignment operator
template <typename K, typename V>
InventoryArray<K, V>& InventoryArray<K, V>::operator=(const InventoryArray < K, V>& original) {
	if (this != &original) {
		while (firstNode1) {
			Node1* p = firstNode1;
			firstNode1 = firstNode1->next;
			delete p;
		}
		Node1* lastNode1 = 0;
		for (Node1* p = original.firstNode1; p; p = p->next) {
			Node1* temp = new Node1;
			temp->key = p->key;
			temp->value = p->value;
			temp->qty = p->qty;
			temp->next = 0;
			if (lastNode1) lastNode1->next = temp;
			else firstNode1 = temp;
			lastNode1 = temp;
		}
		siz1 = original.siz1;

		while (firstNode2) {
			Node2* q = firstNode2;
			firstNode2 = firstNode2->next;
			delete q;
		}
		Node2* lastNode2 = 0;
		for (Node2* q = original.firstNode2; q; q = q->next) {
			Node2* temp = new Node2;
			temp->key = q->key;
			temp->value = q->value;
			temp->aSiz = q->aSiz;
			for (int i = 0; i < siz2; i++) {
				temp->skuArray[i] = q->skuArray[i];
			}
			temp->next = 0;
			if (lastNode2) lastNode2->next = temp;
			else firstNode2 = temp;
			lastNode2 = temp;
		}
		siz2 = original.siz2;
	}



	return *this;
}

// destructor
template <typename K, typename V>
InventoryArray<K, V>::~InventoryArray() {
	while (firstNode2) {
		Node2* q = firstNode2;
		firstNode2 = firstNode2->next;
		delete q;
	}
	while (firstNode1) {
		Node1* p = firstNode1;
		firstNode1 = firstNode1->next;
		delete p;
	}
}


/*-----------------------------------------

	Getters/Setters for Main Functions

-----------------------------------------*/

// square bracket operator returns quantities (getter)
template <typename K, typename V>
int InventoryArray<K, V>::operator[](const K& key) const {
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return p->qty;
	}

	return pQty;
}

// square bracket operator returns quantities (setter)
template <typename K, typename V>
int& InventoryArray<K, V>::operator[](const K& key) {
	pQty = 0;
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return p->qty;
	}

	int tempA = 0;
	int tempB = 0;
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key) {
			for (int i = 0; i < q->aSiz; i++) {
				for (Node1* p = firstNode1; p; p = p->next) {
					if (p->key == q->skuArray[i]) {
						if (tempA == 0) { tempA = p->qty; continue; }
						tempB = p->qty;
						if (tempB < tempA) tempA = tempB;
					}
				}
			}
			pQty = tempA;
			return pQty;
		}
	}
	return pQty;
}

// getter for individual sku values
template <typename K, typename V>
V InventoryArray<K, V>::primary(const K& key) const {
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return p->value;
	}
	return dummy;
}

// setter for individual sku values
template <typename K, typename V>
V& InventoryArray<K, V>::primary(const K& key) {
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return p->value;
	}
	Node1* temp = new Node1;
	temp->key = key;
	temp->value = V();
	temp->qty = 0;
	temp->next = firstNode1;
	firstNode1 = temp;
	siz1++;
	return firstNode1->value;
}

// getter for package sku values
template <typename K, typename V>
V InventoryArray<K, V>::secondary(const K& key) const {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key)
			return q->value;
	}
	return dummy;
}

// setter for package sku values
template <typename K, typename V>
V& InventoryArray<K, V>::secondary(const K& key) {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key)
			return q->value;
	}
	Node2* temp = new Node2;
	temp->key = key;
	temp->aSiz = 0;
	temp->next = firstNode2;
	firstNode2 = temp;
	temp->value = V();
	siz2++;
	return firstNode2->value;
}

// node 2 to node 1 value / package contents getter
template <typename K, typename V>
V InventoryArray<K, V>::packageContents(const K& key, const K& iKey) const {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key) {
			for (int i = 0; i < q->aSiz; i++) {
				if (iKey == q->skuArray[i]) {
					for (Node1* p = firstNode1; p; p = p->next) {
						if (p->key == q->skuArray[i])
							return p->value;
					}
				}
			}
		}
	}
	return dummy;
}

// node 2 to node 1 value / package contents setter
template <typename K, typename V>
V& InventoryArray<K, V>::packageContents(const K& key, const K& iKey) {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key) {
			for (int i = 0; i < q->aSiz; i++) {
				if (iKey == q->skuArray[i]) {
					for (Node1* p = firstNode1; p; p = p->next) {
						if (p->key == q->skuArray[i])
							return p->value;
					}
				}
			}
			for (Node1* p = firstNode1; p; p = p->next) {
				if (p->key == iKey) {
					q->skuArray[q->aSiz] = iKey;
					q->aSiz++;
					return p->value;
				}
			}
			return dummy;
		}
	}

	Node2* temp = new Node2;
	temp->key = key;
	temp->value = V();
	temp->aSiz = 0;
	temp->next = firstNode2;
	firstNode2 = temp;
	siz2++;

	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == iKey) {
			temp->skuArray[temp->aSiz] = iKey;
			temp->aSiz++;
			return p->value;
		}
	}
	return dummy;
}

template <typename K, typename V>
DynamicArray<K> InventoryArray<K, V>::PackageArray(const K& key) const {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key) {
			return q->skuArray;
		}
	}
	return DynamicArray<K>();
}

/*-----------------------------------------

				Housekeeping

-----------------------------------------*/

// contains key all
template <typename K, typename V>
bool InventoryArray<K, V>::containsKey(const K& key) const {
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return true;
	}

	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key)
			return true;
	}
	return false;
}

// key getter individual
template <typename K, typename V>
bool InventoryArray<K, V>::containsKeyP(const K& key) const {
	for (Node1* p = firstNode1; p; p = p->next) {
		if (p->key == key)
			return true;
	}
	return false;
}

// key getter package
template <typename K, typename V>
bool InventoryArray<K, V>::containsKeyS(const K& key) const {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key)
			return true;
	}
	return false;
}

// delete key
template <typename K, typename V>
void InventoryArray<K, V>::deleteKey(const K& key) {
	Node1* p, * prev;
	for (p = firstNode1, prev = 0; p; prev = p, p = p->next) {
		if (p->key == key)
			break;
	}

	if (p) {
		--siz1;
		if (prev) prev->next = p->next;
		else firstNode1 = p->next;
		delete p;

		Node2* q;
		for (q = firstNode2; q; q = q->next) {
			for (int i = 0; i < q->aSiz; i++) {
				if (q->skuArray[i] == key) { 
					while (i < q->aSiz) {
						q->skuArray[i] = q->skuArray[i + 1];
						i++;
					}
					q->aSiz--;
				}
			}
		}
	}

	Node2* q, * prev2;
	for (q = firstNode2, prev2 = 0; q; prev2 = q, q = q->next) {
		if (q->key == key)
			break;
	}

	if (q) {
		--siz2;
		if (prev2) prev2->next = q->next;
		else firstNode2 = q->next;
		delete q;
	}
}

// individual key queue
template <typename K, typename V>
Queue<K> InventoryArray<K, V>::primaryQueue() const {
	Queue<K> keys;

	for (Node1* p = firstNode1; p; p = p->next) {
		keys.push(p->key);
	}
	return keys;
}

// package key queue
template <typename K, typename V>
Queue<K> InventoryArray<K, V>::secondaryQueue() const {
	Queue<K> keys;

	for (Node2* q = firstNode2; q; q = q->next) {
		keys.push(q->key);
	}
	return keys;
}

// package size
template <typename K, typename V>
int InventoryArray<K, V>::aSize(const K& key) const {
	for (Node2* q = firstNode2; q; q = q->next) {
		if (q->key == key) return q->aSiz;
	}
	return 0;
}
// clear
template <typename K, typename V>
void InventoryArray<K, V>::clear() {
	while (firstNode2) {
		Node2* q = firstNode2;
		firstNode2 = firstNode2->next;
		delete q;
		--siz2;
	}

	while (firstNode1) {
		Node1* p = firstNode1;
		firstNode1 = firstNode1->next;
		delete p;
		--siz1;
	}
}

#endif
