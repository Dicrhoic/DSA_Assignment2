/*
 * IdeaBank.h
 *
 *  Created on: 4 May 2020
 *      Author: Home
 */

#ifndef IDEABANK_H_
#define IDEABANK_H_

#include "AVL_ADT.h"

struct DATA
{
	string key;
	vector<int> idList;

};
void print(DATA d){
	cout << "key: " << d.key << endl;
	cout << "idList: ";
	for (int i = 0; i < d.idList.size(); i++) {
	            cout << d.idList[i];

	            if (i+1 != d.idList.size()){
	              cout << ", ";
	            }
	        }
	        cout << endl << endl;
}
class IdeaBank{
	vector<Idea> ideas;
	AvlTree<DATA, string> tree;
	vector<string> wordBank;
	vector<int> relatedIDs;
	vector<string> word_vec;

public:
	void userIdeaInput();
	void displayID(int id);
	void displayAll();
	void deleteIdea(int id);
	void importFromFile();
	void indexWords();
	void spiltWords(string str, vector<string> &kword_vector); //used to extract keywords
	void printTree();
	void searchWOIndex(string word);
	void searchIndex(string word);
	void duplicateFilter(string word, vector<int>relevantIDs);
};



void IdeaBank::printTree(){
	if(tree.AVL_Empty()){
		cout << "Empty tree, nothing to display." << endl;
	}
	else {
		//cout << "Tree Content\n" << endl;
		//tree.AVL_Print();
		cout << endl;
		cout << "Total number of words in the wordTree: " << tree.AVL_Count() << endl;
		tree.AVL_Traverse(print);
	}
}


void IdeaBank::userIdeaInput(){
	bool exit = false;
	string proposer, keyword, content;

	cout << "\nEnter new Idea " << endl;

	Idea newIdea;

	newIdea.setID(); //Sets ID
	cin.ignore();

	cout << "Enter Proposer's Name: " << endl;
	getline(cin,proposer);
	newIdea.setProposer(proposer);

	/* Setting the keywords */

	cout << "Enter the keywords (when finished press 'q'): " << endl;
	while (!exit){
		cin >> keyword;
		if (keyword == "q" || keyword == "Q"){
			exit = true;
		}
		else{
			newIdea.setKeywords(keyword);
		}
	}

	/* Setting Content */
	cout << "Enter content for the idea " << endl;
	//cin >> content; does not work for string thus we use
	cin.ignore(10000, '\n');
	getline(cin,content);
	newIdea.setContent(content);

	cout << "Propser's Name: " << proposer << "\n";
	cout << " Content: " << content<< endl;

	ideas.push_back(newIdea);
}

void IdeaBank::displayID(int id){
	bool found;
	if(ideas.size() == 0){
		cout << "No ideas to display." << endl;
	}
	else {
		for (int i = 0; i < ideas.size(); i++){
			if(ideas[i].getId() == id){
				cout << "Found idea: " << id;
				cout << ". Displaying idea....." << endl;
				ideas[i].printIdea();
				found = true;
				break;
			}
		}
	}
	if (!found){
		cout << "Could not find Idea with ID " << id << endl;
	}

}

void IdeaBank::displayAll(){
	if(ideas.size() == 0){
		cout << "No ideas to display." << endl;
	}
	else {
		for (int i = 0; i < ideas.size(); i++){
			ideas[i].printIdea();
		}
	}

}

void IdeaBank::deleteIdea(int ID){
	bool found = false;
	vector<string> kwordToDlt;
	vector<string> kword_vector;
	string key;

	//delete from ideas bank
	for (int i = 0; i< ideas.size(); i++){
		if (ID == ideas[i].getId() ){
			kwordToDlt = ideas[i].getKeywords();
			ideas.erase(ideas.begin() + i);
			found = true;
		}
		for (int j = 0; j < ideas[i].getKeywords().size(); j++){
			key = ideas[i].getKeywords()[j];

			DATA modifyIndex;
			if (tree.AVL_Retrieve(key, modifyIndex)){
				for (int i = 0; i < modifyIndex.idList.size(); i++){
					if(ID == modifyIndex.idList[i]){
						modifyIndex.idList.erase(modifyIndex.idList.begin()+i); //delete all instances
						tree.AVL_Update(key, modifyIndex);
					}
				}
			}
		}
	}//end of idea traversal

	for (int i = 0; i < kwordToDlt.size(); i++){
		tree.AVL_Delete(kwordToDlt[i]); //deletes word from tree
	}

	if (!found){
		cout << "No such id exits" << endl;
	}


	//delete that id from the tree

}

void IdeaBank::importFromFile(){
	string proposer, content, kyWord, line, input;
	vector<string> kword_vector;
	vector<string> text;
	int id_num = 0;
	int type = 0;
	int num_ideas = 0;
	string eoi = "#end#";
	char contentSect;
	char target;
	ifstream file;

	file.open("ideasbank.txt");

	if (file.fail()){
		cout << "Failed to open file. Please check that the file is in "
				"the folder." << endl;
	}

	while(!file.eof()){
		getline(file,line);
		//cout << line << endl;

		target = line.find("# ");
		if (target != string::npos){
			input = line.substr(target+1);
			type++;
			//cout << "\ntype = " << type << endl;
		}
		switch (type){
		case 1:
			id_num = stoi(input);
			//cout << "ID: " << id_num << endl;
			break;
		case 2:
			proposer = input;
			//cout << "Proposer: " << proposer << endl;
			break;
		case 3:
			spiltWords(input, kword_vector);
			//cout << "Keyword: " << kyWord << endl;
			break;
		case 4:
			content = input;
			//cout << "Content: " << content << endl;
			break;
		}
		if(type == 4){
			//cout << "End of idea" << endl;
			num_ideas++;
			Idea newIdea;
			newIdea.setIDTXT(id_num);
			newIdea.setProposer(proposer);

			for (int i = 0; i < kword_vector.size(); i++){
				newIdea.setKeywords(kword_vector[i]);
			}
			newIdea.setContent(content);
			ideas.push_back(newIdea);
			if(kword_vector.size() != 0){
				kword_vector.clear();
			}
			type = 0;
		}
	}
	cout << "Done adding " << num_ideas  << " ideas."<< endl;
	file.close();
	indexWords();
}

void IdeaBank::indexWords(){
	vector<string> kword_vector;
	vector<string> content_vector;
	vector<string> wordBank;
	vector<int> relevantIDs;
	int idFoundIn;
	string words;
	string contents;

	for (int i = 0; i < ideas.size(); i++){
		wordBank = ideas[i].getKeywords(); //gets all the keywords from one idea
		contents = ideas[i].getContent(); //gets the content from the idea
		spiltWords(contents,wordBank); //splits content to singular words


		for (int i = 0; i < wordBank.size(); i++){
				//finds if the keywords exists in another idea
			for (int j = 0; j < ideas.size(); j++){
				if(ideas[j].checkForWord(wordBank[i])){ //if keyword is found elsewhere
					words = wordBank[i];
					idFoundIn = ideas[j].getId();
					relevantIDs.push_back(idFoundIn);
				}
				//end of search for keyword
			}
			tree.AVL_UpdateAndInsert(words,relevantIDs);
			//duplicateFilter(words,relevantIDs);
			relevantIDs.clear();
		}
	}
	//printTree();
}

void IdeaBank::searchWOIndex(string word){
	bool found;
	vector<int> relatedIDs;
	Idea idea;
	for (int i = 0; i < ideas.size(); i++){
		//cout << "Searching idea " << ideas[i].getId() << endl;
		if (ideas[i].checkForWord(word) == true){
		//	cout << "Found a related idea" << endl;
			relatedIDs.push_back(ideas[i].getId());
		}
	}
	cout << "Search outcome from Ideasbank\n";
			cout << "Related ideas: "<< endl;
	for (int j = 0; j < relatedIDs.size(); j++){
		//cout << "Idea " << relatedIDs[j] << endl;
		displayID(relatedIDs[j]);
	}

}

void IdeaBank::searchIndex(string word){
	DATA indexSearch;

    if (tree.AVL_Retrieve(word, indexSearch)){
    	cout << "Search outcome from Indexing for: "
              << word << ":" << endl;
         for (int i = 0; i < indexSearch.idList.size(); i++){
             cout << indexSearch.idList[i] << endl;
             displayID(indexSearch.idList[i]);
         }
     }
     else{
         cout << "\nNo relevant ideas found for "
              << word << endl;
     }
}

void IdeaBank::spiltWords(string str, vector<string> &word_vector){
	istringstream ss(str);
	int len;

	do {
		//read word
		string word;
		ss >> word;
		//remove punctuations
		for (int i = 0, len = word.size(); i < len; i++){
			if(ispunct(word[i])){
				word.erase(i--, 1);
				len = word.size();
			}
		}
		//Print the read word
		//cout << word << endl;
		word_vector.push_back(word);

	}
	while (ss);
}

void IdeaBank::duplicateFilter(string word, vector<int>relevantIDs){
	Idea idea;
	vector<string> words;
	vector<int> idsToStore;
	words.push_back(word);
	//removes duplicate words from an idea.
	for (int i = 1; i < words.size(); i++){
		for (int j = i+1; j < words.size(); j++ ){
			if(words.at(i) == words.at(j)){
				cout<< "DUPE WORD" << endl;
				words.at(j) = words.at(words.size() - 1);
				words.pop_back();
				j--;
			}
		}
	}
	//add to the word_vec
	for (int i = 0; i < word_vec.size(); i++){
		for (int j = 0; j < words.size(); j++){
			if(word_vec.at(i) == words.at(j)){
				cout << "Duplicate word removing" <<endl;
			}
			else {
				word_vec.push_back(word);
			}
		}
	}
	//word_vec should contain every word of Ideas with no duplicates
	for (int i = 0; i < relevantIDs.size(); i++){
			bool idExists = false;
			bool kwordExists = false;

			for(int j = 0; j < relatedIDs.size(); j++){
				if(relevantIDs[i] == relatedIDs[j]){
					idExists = true;
				}
			}
			if (!idExists){
				idsToStore.push_back(relevantIDs[i]);
			}

	}

	DATA newIndex;
	newIndex.key = word;

	for (int i = 0; i < relevantIDs.size(); i++){
		newIndex.idList.push_back(relevantIDs[i]);
	}
	tree.AVL_Insert(newIndex);
}



#endif /* IDEABANK_H_ */
