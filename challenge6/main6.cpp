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
	 getline(fileIn,line);
	 bool markerFound=false;
	 int res=0;
	 int i=0;
	 bool currentValue=false;
	 while (!markerFound){
		 currentValue=true;
		 for (int k=0+i; k<14+i;k++){
			 for (int p=k+1; p<14+i ;p++) {
				 currentValue &= (line[k]!=line[p]);
			 }
		 }
		if (currentValue)
		{
			markerFound=true;
			res=i+14;
		}
		i++;
	 }
	 cout << res << endl;
	return 0;
	
}

