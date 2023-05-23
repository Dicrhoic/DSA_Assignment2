/*
 * menu.h
 *
 *  Created on: 12 May 2020
 *      Author: Home
 */

#ifndef MENU_H_
#define MENU_H_

class menu {
public:
	int targetID;
	void options();
	void selection(int choice);
	IdeaBank IB;
	string word;
	int deleteID;
};

void menu::options(){
	cout << "-----Ideas Bank-----\n";
	cout << "------19396431------\n";
	cout << "Select you option \n";
	cout << "1) Insert a new idea \n";
	cout << "2) Display an idea by giving its id\n";
	cout << "3) Display all ideas in the database \n";
	cout << "4) Delete an idea\n";
	cout << "5) Import Ideas from a file\n";
	cout << "6) Print the indices of the bank\n";
	cout << "7) Search for an idea from ideas bank \n";
	cout << "8) Search for an idea from indexing tree\n";
	cout << "0) Quit " << endl;

}

void menu::selection(int choice){
	switch(choice){
		case 0:
			cout << "Exiting Ideas Bank....." << endl;
			break;
		case 1:
			IB.userIdeaInput();
			break;
		case 2:
			cout << "Enter the ID you wish to search for." << endl;
			cin >> targetID;
			IB.displayID(targetID);
			break;
		case 3:
			IB.displayAll();
			break;
		case 4:
			cout << "Please enter the id of the idea you want to delete ..." << endl;
			cin >> deleteID;
			IB.deleteIdea(deleteID);
			break;
		case 5:
			IB.importFromFile();
			break;
		case 6:
			IB.printTree();
			IB.indexWords();
			break;
		case 7:
			cout << "Please enter a word to search for ..." << endl;
			cin >> word;
			IB.searchWOIndex(word);
			break;
		case 8:
			cout << "Please enter a word to search for ..." << endl;
			cin >> word;
			IB.searchIndex(word);
			break;
		default:
			cout << "Invalid action!" << endl;
			break;
	}
}

#endif /* MENU_H_ */
