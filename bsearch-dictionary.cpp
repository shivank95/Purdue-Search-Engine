
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	return ArrayDictionary::addRecord(key, record);
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
	if (!sorted) {
		sort();
		sorted = true;
	}
	
	// Use binary search
	int low = 0;
	int high = currentNumber - 1;
	while (high >= low) {
		
		int mid = (high + low) / 2;
		int result = strcmp(key, array[mid].key);
		
		if (result == 0) {	//Found key
			
			return array[mid].data;
		}
		
		else if(result > 0) {	//update low
			low = mid+1;
		}
		else {					//update high
			high = mid-1;
		}
	}

	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	printf("Before\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s\n", array[i].key);
	}
    // Add your code here
        
    heap = new ArrayDictionaryNode[currentNumber];
    
    for (int i = 0; i < currentNumber; i++) {
    	insert(array[i]);
    }
    
    for (int i = 0; i < currentNumber; i++) {
    	
    	array[i] = removeMin();
    }    

	printf("After\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s\n", array[i].key);
	}
}

int 
BinarySearchDictionary::left(int p) {	//p is the parent index
	return 2*p+1;
			
}
	
int 
BinarySearchDictionary::right(int p) {
	return 2*p + 2;
}
	
int 
BinarySearchDictionary::theParent (int c) {
	return (c-1)/2;
}

void 
BinarySearchDictionary::insert(ArrayDictionaryNode key) {
	heap[last] = key;
	
	last++;
	
	//Apply upheap
	
	//indexes intitialize
	int child = last - 1;
	int parent = theParent(child);
	
	while (child > 0) {
		if(strcmp(heap[child].key, heap[parent].key) < 0) {
		
			//swap
			ArrayDictionaryNode temp = heap[child];	
			heap[child] = heap[parent];
			
			heap[parent] = temp;
			
			child = parent;
			
			parent = theParent(child);
		}
		else {
			break;
		}
	}
}

ArrayDictionaryNode
BinarySearchDictionary::removeMin() {
	
	
	ArrayDictionaryNode minKey;
	
	minKey.key = heap[0].key;
	minKey.data = heap[0].data;
	
	heap[0] = heap[last - 1];
	
	last--;
	
	int parent = 0;
	
	int ileft = left(parent);
	int iright = right(parent);
	
	while (ileft < last) {
		
		int minChild = ileft;
		
		if (iright < last && strcmp(heap[iright].key, heap[ileft].key) < 0) {
			minChild = iright;
		}
		if(strcmp(heap[parent].key, heap[minChild].key) > 0) {
			//swap
			
			ArrayDictionaryNode temp = heap[parent];
			
			heap[parent] = heap[minChild];
			heap[minChild] = temp;
			
			parent = minChild;
			ileft = left(parent);
			iright = right(parent);
			
		}
		
		else {
			break;
		}
	}
	
	return minKey;
}





