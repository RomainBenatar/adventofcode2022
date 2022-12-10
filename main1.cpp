#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fileIn;
    fileIn.open("test.txt");
	
	string line;

    if (!fileIn)
    {
        cout<<"A error has occured, please contact support.";
		return -1;
    }
	
	int currentMax=0;
	int currentValue=0;
	int currentStack=0;
	string emptyString= "";
	int i=0;
	vector<int> elfStack;
	int elfNumber=0;
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
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
			// Read in an item
			while (getline(sstr, item))
			{
				currentValue=stoi(item);
				currentStack+=currentValue;
				//std::cout << currentValue << std::endl;
			}
		}
	}
	sort(elfStack.begin(), elfStack.end());
	reverse(elfStack.begin(), elfStack.end());
	std::cout << elfStack[0] << std::endl;
	std::cout << elfStack[1] << std::endl;
	std::cout << elfStack[2] << std::endl;
	std::cout << elfStack[0]+elfStack[1]+elfStack[2] << std::endl;
	return 0;
	
}