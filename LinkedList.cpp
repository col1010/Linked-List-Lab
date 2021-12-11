/* Name: Coleby Kauffman
 * Class: CS-311
 * Assignment: Project 1
 */

#include<iostream>
using namespace std;

struct ListNode {
	string data;
	ListNode* next;
};

class WordList {
	ListNode *start = 0;
	bool reversed = false;
public:
	void add(string w){
		ListNode *toadd = new ListNode;
		toadd->data = w;
		toadd->next = 0;
		if(!start){
			start = toadd;
			return;
		}
		ListNode *place = start;
		ListNode *last = 0;
		if (reversed) {
			while(place && place->data > toadd->data){
				last = place;
				place = place->next;
			}
		} else {
			while(place && place->data < toadd->data){
			last = place;
			place = place->next;
		}
		
		}
		if (place && place->data == w) { // in the case of a duplicate word, place->data will always be the word it matches
			cout << " Duplicate word: " << place->data << "! Word not added.\n";
			delete toadd; // don't leak memory!
			return;
		}
			
		if(last)
			last->next = toadd;
		if(!last)
			start = toadd;
		toadd->next = place;
		
	}
	void remove(string w) {
		ListNode *place = start;
		ListNode *last = 0;
		while (place) {                           // while there are more words
			if (place->data == w) {               // if the current word matches the word to remove
				if (last) {                       // if the current word is not the first in the list
					if (place->next)              // if the current word is not the last in the list
						last->next = place->next; // set last's next pointer to the word after the one being removed
					else 
						last->next = 0;           // else set last's next pointer to nothing
					delete place;
				} else {                          // the word to be removed is the first in the list
					start = place->next;          // set the starting word to be the word after the one being removed
					delete place;
				}
				return;
			}
			last = place;        // increment last
			place = place->next; // increment place
		}
		cout << " Word was not found in list.\n";
		return;
	}
	int length() {
		ListNode *place = start;
		int count = 0;
		while (place) {
			count++;
			place = place->next;
		}
		return count;
	}

	int find(string w) {
		ListNode *place = start;
		int count = 0;
		while (place) {
			if (place->data == w) {
				return count; // word found, return the index
			}
			place = place->next;
			count++;
		}
		return -1; // word not found, return -1
	}
	
	void reverse() {
		reversed = !reversed; // set reversed to the opposite of whatever it is now

		if (!start || !start->next) // if the list contains one or zero elements, return after setting reversed bool
			return;
		
		ListNode *prevNode = start;
		ListNode *place = start->next;
		ListNode *nextNode;
		if (start->next->next) {           // if there are 3 or more elements in the list
			nextNode = start->next->next;  // set the nextNode to the 3rd element
			prevNode->next = 0;            // set the first node's pointer to null (it's the new end of the list)
			while (nextNode) {             // while there is a next node
				place->next = prevNode;    // set the current position's node's pointer to the previous node
				prevNode = place;          // set the previous node to the current node
				place = nextNode;          // set the current node to the next node
				nextNode = nextNode->next; // set the next node to what it points to
			}
			place->next = prevNode;        // after the while loop ends, connect the new first element to the new second element
			start = place;                 // set the new start to the old end of the list

		} else {                           // else (if there are 2 elements in the list, this runs)
			start = place;                 // set the start to the 2nd element
			place->next = prevNode;        // set the 2nd element's pointer to the first element
			prevNode->next = 0;            // set the 1st element's pointer to nothing (it is the new final element)
		}
	}

	void print(){
		ListNode *place = start;
		if (place) {
			cout << "[";
			while(place){
				cout << place->data << ", ";
				place = place->next;
			}
		cout << "\b\b]\n";
		} else {
			cout << " The list is empty.\n";
			// print nothing
		}
		
	}
	~WordList(){
		ListNode *place = start, *next;
		while(place){
			next = place->next;
			delete place;
			place = next;
		}
	}
};



int main(){
	WordList names;
	string word;
	int choice = 3;

	names.add("Gandalf");
	names.add("Frodo");
	names.add("Sam");
	names.add("Aragorn");
	names.add("Boromir");
	names.add("Pippin");

	while (choice > 0 && choice < 6) {
		cout << "1) Add a word to the list\n";
		cout << "2) Remove a word from the list\n";
		cout << "3) Print the list\n";
		cout << "4) Print the length of the list\n";
		cout << "5) Reverse the list\n";
		cout << "6) Exit the program\n";
		cout << "\n Which action would you like to perform on the list? (1-6): ";
		cin >> choice;
		cin.ignore();
		switch (choice) {
			case 1:
				cout << "\n Enter a word to be added: ";
				getline(cin, word);
				names.add(word);
				break;
			case 2:
				cout << "\n Enter a word to be removed: ";
				getline(cin, word);
				names.remove(word);
				cout << "\n";
				break;
			case 3:
				names.print();
				cout <<"\n";
				break;
			case 4:
				cout << " Length of the list: " << names.length() << "\n\n";
				break;
			case 5:
				names.reverse();
				cout << " List has been reversed. The new list is\n ";
				names.print();
				cout << "\n";
				break;
			case 6:
				cout << " Exiting program.\n\n";
				break;
		}
	}
}

/*
 * Starting with the code above add these features (20% of grade each).  Add test code for each, to make sure they work.
 * 	1.  If a word is already in the list, don't add a second copy of it
 * 	2.  Add a remove method, which takes a word and removes it from the list.  Don't leak memory!
 * 	3.  Add a length method, which returns the length of the list
 * 	4.  Add a find method, which finds the index of an item, and returns -1 if it is not in the list.  Remember to put in test code for both cases.
 * 	5.  Add a reverse method, which will reverse the order of the list.  Once the list is reversed, it should stay reversed even when new words are added.  Keep a private boolean property called "reversed" which will track whether the list is currently reversed or not, and modify the add method so that it uses this property to figure out where to put new data.
 *
 * 	Test code here can be either interactive or not, but compiling and running the program should provide a convincing demonstration that your linked list ADT works.  Keep all data members private in the WordList class.
 */
