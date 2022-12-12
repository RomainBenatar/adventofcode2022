#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void RemoveWordFromLine(std::string &line, const std::string &word)
{
  auto n = line.find(word);
  if (n != std::string::npos)
  {
    line.erase(n, word.length());
  }
}

void setDirectorySize(string folderString, map<string, vector<string>>& subfolder_,map<string, int>& folder_){
	if (subfolder_[folderString].size()>0){
		for (int p=0;p<subfolder_[folderString].size();p++) {
			setDirectorySize(subfolder_[folderString][p],subfolder_,folder_);
			cout << folderString << folder_[folderString] <<endl;
			cout << subfolder_[folderString][p] << folder_[subfolder_[folderString][p]] <<endl;
			folder_[folderString]+=folder_[subfolder_[folderString][p]];
		}
	}
}


int main() {
    ifstream fileIn;
    fileIn.open("input.txt");
	
	string line;
	string currentFolder;
	vector<string> currentFolderPath;
	vector<int> currentSize;
	typedef map<string, int> folderShape;
	map<string, int> folder;
	map<string, vector<string>> subfolder;
	string::size_type sz;   // alias of size_t
	bool readingFiles=false;
    if (!fileIn)
    {
        cout<<"A error has occured, please contact support.";
		return -1;
    } 
	 while (getline(fileIn,line))
	 {
		string item;
		stringstream sstr(line);
		 if (line[0]=='$') {
			 readingFiles=false;
		// Read in an item
			getline(sstr, item, ' ');
			getline(sstr, item, ' ');
			if (item.compare("cd")==0){
				getline(sstr, item, '\n');
				if (item.compare("/")==0){
					currentFolder="/";
				}
				else if (item.compare("..")==0){
					currentFolder.pop_back();
					while (currentFolder.back()!='/'){
						currentFolder.pop_back();
					}
				}
				else {
					currentFolder+=item;
					currentFolder+="/";	
				}
			}
			else if (item.compare("ls")==0){
				readingFiles=true;
			}
			
		 }
		 else if (readingFiles==true){
			string item2;
			stringstream sstr2(line);
			//cout << line << endl;
			getline(sstr2, item2, ' ');
			if (item2.compare("dir")==0){
				getline(sstr2, item2, ' ');
				subfolder[currentFolder].push_back(currentFolder+item2+"/");
			}
			else
			{
				folder[currentFolder]+=stoi(item2,&sz);
				cout <<"add "<< item2 <<" in " << currentFolder<<endl;
			}	
		}
		
	 }/*
	 for(folderShape::const_iterator it=folder.begin() ; it!=folder.end() ; ++it)
	 {
		 cout << it->first << endl;
		 cout << it->second << endl;
	 }
	 */
 
	 setDirectorySize("/",subfolder,folder);

	 int somme=0;
	 int min=30000000;
	 int usedSpace=folder["/"];
	 int freeSpace=70000000-usedSpace;
	 int prev=70000000;
	 for(folderShape::const_iterator it=folder.begin() ; it!=folder.end() ; ++it)
	 {
		 if (freeSpace+it->second>=min && it->second<prev){
			 prev=it->second;
		 }
	 }
	 cout << "prev " << prev << endl;
	 
	return 0;
	
}

