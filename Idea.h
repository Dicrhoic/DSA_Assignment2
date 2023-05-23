/*
 * Idea.h
 *
 *  Created on: 4 May 2020
 *      Author: Kevin Vo Le 19396431
 */

#ifndef IDEA_H_
#define IDEA_H_

using namespace std;

class Idea{
private:
	int ID;
	string proposer;
	vector<string> keywords;
	string content;

public:
	Idea();
	bool checkForWord(string word);
	//setting data
	void setID();
	void setIDTXT(int id);
	void setProposer(string name);
	void setKeywords(string kw);
	void setContent(string desc);
	//retrieving data
	int getId();
	string getProposer();
	vector<string> getKeywords();
	string getContent();
	//print out data
	void printIdea();

};

Idea::Idea(){
	/*Default constr.
	 */
	//ID = 0;
}

bool Idea::checkForWord(string word){
	//keyword search
	for (int i = 0; i < keywords.size(); i++){
		if(word == keywords[i]){
			return true;
		}
	}

	//content search
	size_t target;
	target = content.find(word);
	if (target != string::npos){
		return true;
	}
	return false;

}

void Idea::setID(){
	static int id;
	ID = id++;
}

void Idea::setProposer(string name){
	proposer = name;
}

void Idea::setKeywords(string kw){
	keywords.push_back(kw);
}

void Idea::setContent(string desc){
	content = desc;
}

void Idea::printIdea(){
    cout << "\nIdea ID: " << ID << "\n"
         << "Proposer: " << proposer << "\n"
         << "Keywords: ";

    for (int i = 0; i < keywords.size(); i++) {
        cout << keywords[i];
        if (i+1 != keywords.size()){
            cout << ", ";
        }
    }
    cout << "\nContent: " << content << endl;
    cout << endl;
}

int Idea::getId(){
	return ID;
}

vector<string> Idea::getKeywords(){
	return keywords;
}

void Idea::setIDTXT(int id){
	ID = id;
}

string Idea::getContent(){
	return content;
}

#endif /* IDEA_H_ */
