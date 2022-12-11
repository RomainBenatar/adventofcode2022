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
	vector<int> minimum;
	vector<int> maximum;
	 std::string::size_type sz;   // alias of size_t
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
		
		// Read in an item
		while (getline(sstr, item,','))
		{	
			std::cout << "item " << item << std::endl;
			string value;
			stringstream sstr2(item);
			getline(sstr2, value, '-');
			std::cout << "value " << value << std::endl;
			minimum.push_back(stoi(value,&sz));
			getline(sstr2, value);
			std::cout << "value " << value << std::endl;
			maximum.push_back(stoi(value,&sz));
		}
		i+=2;
		if ((minimum[i-2]<=maximum[i-1] && maximum[i-2]>=maximum[i-1]) || 
		(minimum[i-2]<=minimum[i-1] && minimum[i-1]<=maximum[i-2]) || 
		(minimum[i-1]<=maximum[i-2] && maximum[i-1]>=maximum[i-2]) || 
		(minimum[i-1]<=minimum[i-2] && minimum[i-2]<=maximum[i-1])
		)
		{
			count++;
		}
		cout << "count " << count << endl;
	}
	
	return 0;
	
}