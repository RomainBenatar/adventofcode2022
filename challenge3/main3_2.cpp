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
	
	int i=0;
	int count=0;
	int score=0;
	vector<char> elf1;
	vector<char> elf2;
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		string item2;
		string item3;
		elf1.clear();
		elf2.clear();
		stringstream sstr(line);
		// Read in an item
		while (getline(sstr, item)){
			std::cout << item << std::endl;
			for (int j=0; j<item.length();j++){
					if(find(elf1.begin(), elf1.end(),item[j])==elf1.end()){
						elf1.push_back(item[j]);
						std::cout << item[j] << std::endl;
					}
			}
			getline(fileIn,line);
			stringstream sstr2(line);
			getline(sstr2, item2);
			std::cout << item2 << std::endl;
			for (int j=0; j<item2.length();j++){
				if(find(elf1.begin(), elf1.end(),item2[j])!=elf1.end()){
					elf2.push_back(item2[j]);
					std::cout << item2[j] << std::endl;
				}
				
			}
			getline(fileIn,line);
			stringstream sstr3(line);
			getline(sstr3, item3);
			for (int j=0; j<item3.length();j++){
				if(find(elf1.begin(), elf1.end(),item3[j])!=elf1.end() 
					&& find(elf2.begin(), elf2.end(),item3[j])!=elf2.end()){
					std::cout << "item[j] " << item3.length() << " " << j << " " << item3[j] << std::endl;
					std::cout << "score " << score << std::endl;
					if (islower(item3[j])){
						score+=item3[j]-96;
					}
					else{
						score+=item3[j]-65+27;
					}
					j=item3.length();
				}
			}
		}
	}
	cout << score << endl;
	return 0;
	
}