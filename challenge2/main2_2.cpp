#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fileIn;
    fileIn.open("input.txt");
	
	string line;

    if (!fileIn)
    {
        cout<<"A error has occured, please contact support.";
		return -1;
    }
	
	char opponentMove;
	char myMove;
	
	int win=6;
	int loss=0;
	int draw=3;
	
	int rock=1;
	int paper=2;
	int scissors=3;

	int i=0;
	int score=0;
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
		/*
		if (line.empty())
		{
			//std::cout << "emptyline" << std::endl;
			if (currentStack>currentMax){
				currentMax=currentStack;
				std::cout << "currentMax "<< currentMax << std::endl;
			}
			elfStack.push_back(currentStack);
			elfNumber++;
			currentStack=0;
		}
		else {
			*/
		// Read in an item
		while (getline(sstr, item, ' '))
		{	
			std::cout << "item "<< item << std::endl;	
			if (i%2==0){
				opponentMove=item[0];
			}
			else {
				myMove=item[0];
			}
			i++;
		}
			std::cout << "myMove "<< myMove << std::endl;
		std::cout << "opponentMove "<< opponentMove << std::endl;
		switch (opponentMove) {
			case 'A':
				if (myMove=='Y'){
					score+=rock;
					score+=draw;
				}
				if (myMove=='X'){
					score+=scissors;
					score+=loss;
				}
				if (myMove=='Z'){
					score+=paper;
					score+=win;
				}
				break;
			case 'B':
				if (myMove=='Y'){
					score+=paper;
					score+=draw;
				}
				if (myMove=='X'){
					score+=rock;
					score+=loss;
				}
				if (myMove=='Z'){
					score+=scissors;
					score+=win;
				}
				break;
			case 'C':
				if (myMove=='Y'){
					score+=scissors;
					score+=draw;
				}
				if (myMove=='X'){
					score+=paper;
					score+=loss;
				}
				if (myMove=='Z'){
					score+=rock;
					score+=win;
				}			
				break;
		}
	}
	std::cout << score << std::endl;
	return 0;
	
}