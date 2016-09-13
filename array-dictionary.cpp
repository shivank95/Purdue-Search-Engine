
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary()
{
  // Add your code here
  maxNumber = 2000;
  array = (ArrayDictionaryNode*) malloc (2000 * sizeof(ArrayDictionaryNode));
  currentNumber = 0;	//points to next empty element
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
        // Add your code here
        
	//Check if record already exists

	//Record already present, modify data
	char * keyToCompare = strdup((char *) key);
	for (int i = 0; i < currentNumber; i++) {
		char * currentKey = strdup(array[i].key);
		if(!strcmp(currentKey, keyToCompare)) {
		
			//Found, edit value
			array[i].data = (void*) record;
			return false;
		}
	}
	//Check if array is full
	if (currentNumber == maxNumber) {
		
		//Resize
		maxNumber = maxNumber * 2;
		array = (ArrayDictionaryNode*) realloc (array, maxNumber * sizeof(ArrayDictionaryNode));
		
	}
	
	//Add element to array
	ArrayDictionaryNode * e = new ArrayDictionaryNode;
	e->key = strdup((char *) key);
	e->data = (void *) record;
	array[currentNumber] = *e;
	currentNumber++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
        // add your code here
        
    char * keyToCompare = (char *) key;
	for (int i = 0; i < currentNumber; i++) {
		char * currentKey = array[i].key;
		if(!strcmp(currentKey, keyToCompare)) {
			
			//Found
			return (DataType) array[i].data;
		}
	}
	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
        // Add your code here
	char * keyToCompare = (char *) key;
	for (int i = 0; i < currentNumber; i++) {
		char * currentKey = array[i].key;
		if(!strcmp(currentKey, keyToCompare)) {
			
			//Found Element to remove, Shift elements left
			for (int j = i; j < currentNumber-1; j++) {
			
				array[j].key = array[j+1].key;
				array[j].data = array[j+1].data;
			}
			
			//Reduce index
			currentNumber--;
			
			return true;
		}
	}
	return false;
	
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
        // Add yoru code here
	*n = currentNumber;
	KeyType * strArray = (KeyType *) malloc (currentNumber * sizeof(ArrayDictionaryNode));
	int cnt = 0;
	for (int i = 0; i < currentNumber; i++) {
		strArray[i] = (KeyType) strdup(array[i].key);
	}
	
	return strArray;
}
