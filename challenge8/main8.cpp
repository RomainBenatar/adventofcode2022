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
	vector<int> treeSize;
	vector<bool> treeVisibility;
	vector<int> treeScore;
	int currentMax=0;
	 std::string::size_type sz;   // alias of size_t
	// Read in a line
	int lines =0;
	int columns = 0;
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
		columns=line.length();
		// Read in an item
		for (int i=0;i<columns;i++){
			treeSize.push_back(line[i]);
			treeVisibility.push_back(false);
			treeScore.push_back(0);
		}
		lines++;
	}
	int visibleTrees=0;
	cout << lines << endl;
	for (int i=0;i<columns;i++){
		for (int j=0;j<lines;j++){
			if (i==0||j==0||i==(columns-1)||j==(lines-1))
			{
				treeVisibility[i+j*columns]=true;
				visibleTrees++;
			}
			else {
				bool visibility=false;
				bool lVisibilty=true;
				bool rVisibilty=true;
				bool nVisibilty=true;
				bool sVisibilty=true;
				int tempScore=0;
				//Left visibility
				for (int k=i-1;k>=0;k--){
					if (lVisibilty)
					{
						tempScore++;
					}
					if (treeSize[i+j*columns]<=treeSize[k+j*columns]){
						lVisibilty=false;
					}
				}
				cout << tempScore << endl;
				treeScore[i+j*columns]=tempScore;
				tempScore=0;
				//right visibility
				for (int k=i+1;k<columns;k++){
					if (rVisibilty)
					{
						tempScore++;
					}
					if (treeSize[i+j*columns]<=treeSize[k+j*columns]){
						rVisibilty=false;
					}
				}
				cout << tempScore << endl;
				treeScore[i+j*columns]*=tempScore;
				tempScore=0;
				//North visibility
				for (int k=j-1;k>=0;k--){
					if (nVisibilty)
					{
						tempScore++;
					}
					if (treeSize[i+j*columns]<=treeSize[i+k*columns]){
						nVisibilty=false;
					}
				}
				cout << tempScore << endl;
				treeScore[i+j*columns]*=tempScore;
				tempScore=0;
				//south visibility
				for (int k=j+1;k<lines;k++){
					if (treeSize[i+j*columns]<=treeSize[i+k*columns]){
						sVisibilty=false;
					}
					if (sVisibilty)
					{
						tempScore++;
					}
				}
				treeScore[i+j*columns]*=tempScore;
				cout << tempScore << endl;
				visibility = (lVisibilty || nVisibilty || rVisibilty || sVisibilty);
				treeVisibility[i+j*columns]=visibility;
				if (visibility) visibleTrees++;
				if (treeScore[i+j*columns]>currentMax) 
				{
					currentMax=treeScore[i+j*columns];
					cout << "highest scenic score " << currentMax << endl; 
				}


			}

		}
		
	}
	cout << "highest scenic score " << currentMax << endl;
	cout << "visible trees : " << visibleTrees << endl;
	return 0;
	
}