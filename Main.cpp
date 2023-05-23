/*
 * Main.cpp
 *
 *  Created on: 4 May 2020
 *      Author: Home
 */

#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <sstream>
#include <fstream>

#include "Idea.h"
#include "IdeaBank.h"
#include "AVL_ADT.h"
#include "menu.h"

using namespace std;

int main(){
	menu m;
	int option;
	do {
		m.options();
		cin >> option;
		m.selection(option);
	}
	while (option !=0 );

	return 0;
}



