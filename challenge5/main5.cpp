#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void RemoveWordFromLine(std::string &line, const std::string &word)
{
  auto n = line.find(word);
  if (n != std::string::npos)
  {
    line.erase(n, word.length());
  }
}

int main() {
    ifstream fileIn;
    fileIn.open("input.txt");
	
	string line;

    if (!fileIn)
    {
        cout<<"A error has occured, please contact support.";
		return -1;
    }
	
	int i=0;
	int count=0;
	int fromStack=0;
	int toStack=0;
	vector<vector<char>> stacks;
	std::string::size_type sz;   // alias of size_t
	 
	 getline(fileIn,line);
	 
	 int number_of_stacks = (line.length()+1)/4;
	 for (int i=0;i<number_of_stacks;i++){
		 vector<char> currentStack;
		 if (line[4*i+1]!=' '){
			currentStack.push_back(line[4*i+1]);
		 }
		 stacks.push_back(currentStack);
	 }
	 getline(fileIn,line);
	 
	 while (line[1]!='1'){
		 for (int i=0;i<number_of_stacks;i++){
			 if (line[4*i+1]!=' '){
				stacks[i].push_back(line[4*i+1]);
			 }
		}
		getline(fileIn,line);
	 }
	 getline(fileIn,line);
	 
	  for (int i=0;i<number_of_stacks;i++){
		  reverse(stacks[i].begin(),stacks[i].end());
		   cout << stacks[i].size() << endl;
		   cout << stacks[i].back() << endl;
		   cout << endl;
	  }
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		RemoveWordFromLine(line,"move ");
		RemoveWordFromLine(line,"from ");
		RemoveWordFromLine(line,"to ");
		stringstream sstr(line);
		// Read in an item
		getline(sstr, item,' ');
		//std::cout << "item " << item << std::endl;
		count=stoi(item,&sz);
		getline(sstr, item,' ');
		//std::cout << "item " << item << std::endl;
		fromStack=stoi(item,&sz);
		getline(sstr, item,' ');
		//std::cout << "item " << item << std::endl;
		toStack=stoi(item,&sz);
		
		for (int j=0; j<count;j++){
			char currentChar = stacks[fromStack-1].back();
			stacks[toStack-1].push_back(currentChar);
			stacks[fromStack-1].pop_back();
		}

	 }
	for (int i=0;i<number_of_stacks;i++){
		 cout << stacks[i].back() << endl;
	}
	 
	
	return 0;
	
}

