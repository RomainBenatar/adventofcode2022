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
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
		// Read in an item
		while (getline(sstr, item))
		{	std::cout << "item " << item << std::endl;
			for (int j=0; j<item.length()/2;j++){
				for (int i=item.length()/2;i<item.length();i++){
					if(item[j]==item[i]){
						if (islower(item[i])){
							score+=item[i]-96;
						}
						else{
							score+=item[i]-65+27;
						}
						std::cout << "item[j] " << item.length() << " " << i << " " << j << " " << item[j] << std::endl;
						std::cout << "score " << score << std::endl;
						j=item.length();
						i=item.length();
					}
					
				}
			}
		}
	}
	std::cout << score << std::endl;
	return 0;
	
}