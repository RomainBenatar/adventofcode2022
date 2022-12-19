#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <algorithm>
#include <map>

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
	int hx=0;
	int hy=0;
	int phx=0;
	int phy=0;
	int tx=0;
	int ty=0;
	char dir;
	int speed;
	vector<pair<int,int>> encouteredPos;

	 std::string::size_type sz;   // alias of size_t
	 encouteredPos.push_back({0,0});
	// Read in a line
	while (getline(fileIn,line))
	{
		string item;
		stringstream sstr(line);
		
		// Read in an item
		getline(sstr, item,' ');
		//std::cout << "item " << item << std::endl;
		dir = item[0];
		getline(sstr, item);
		speed= stoi(item,&sz);
		phx=hx;
		phy=hy;
		for (int i=0;i<speed;i++){
			switch (dir) {
				case 'U':
					hy++;
					if (abs(hy-ty)>1) {ty++;
					if (abs(hx-tx)>0) tx=hx;}
					break;
				case 'L':
					hx--;
					if (abs(hx-tx)>1) {tx--;
					if (abs(hy-ty)>0) ty=hy;}
					break;
				case 'D':
					hy--;
					if (abs(hy-ty)>1) {ty--;
					if (abs(hx-tx)>0) tx=hx;}
					break;
				case 'R':
					hx++;
					if (abs(hx-tx)>1) {tx++;
					if (abs(hy-ty)>0) ty=hy;}
					break;
				default :
					cerr << "error" << endl;
					break;
			}
			//std::cout << "hx " << hx << " hy "<< hy << std::endl;
			std::cout << "tx " << tx << " ty "<< ty << std::endl;
			int vecSize=std::count(encouteredPos.begin(),encouteredPos.end(),make_pair(tx,ty));
			if (vecSize==0) encouteredPos.push_back(make_pair(tx,ty));
		};

	}

	std::cout << "Number of unique elements is "
              << encouteredPos.size()
              << std::endl;
	return 0;
	
}