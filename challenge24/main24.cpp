#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <limits>
/*
#include "libraph/Edge.h"
#include "libraph/Graph.h"
#include "libraph/Node.h"
#include "libraph/SimpleEdge.h"
*/
using namespace std;

enum typeCell {
	Empty,
	Wall,
	Blizzard
};

class blizzard {
	protected:
		char direction;
		pair<int,int> position;
	public:
		blizzard(pair<int,int> position_,char dir_)
		{
			position=position_;
			direction=dir_;
		}
		void setPos(pair<int,int> position_){
			position=position_;
		}
		char getDir(){
			return direction;
		}
		pair<int,int> getPos(){
			return position;
		}
		
};

class cell {
	pair<int,int> position;
	typeCell type;
	public:
	cell(pair<int,int> position_,typeCell type_)
	{
		position=position_;
		type=type_;
	}
	void setType(typeCell type_){
		type=type_;
	}
	
	typeCell getType(){
		return type;
	}
	
	pair<int,int> getPos(){
		return position;
	}
};

vector<blizzard> updateBlizzards(vector<blizzard> blizards_, int height_, int width_){
	vector<blizzard> newBlizzards;
	for (auto &currentBlizzard : blizards_){
		pair<int,int> currentPosition=currentBlizzard.getPos();
		switch (currentBlizzard.getDir()){
			case '<':
				currentPosition.first--;
				currentPosition.first+=width_-1;
				currentPosition.first%=width_;
				currentPosition.first+=1;
				currentBlizzard.setPos(currentPosition);
				break;
			case '>':
				currentPosition.first%=width_;
				currentPosition.first++;
				currentBlizzard.setPos(currentPosition);
				break;
			case '^':
				currentPosition.second--;
				currentPosition.second+=height_-1;
				currentPosition.second%=height_;
				currentPosition.second+=1;
				currentBlizzard.setPos(currentPosition);
				break;
			case 'v':
				currentPosition.second%=height_;
				currentPosition.second++;
				currentBlizzard.setPos(currentPosition);
				break;
			default :
				break;
				
		}
		newBlizzards.push_back(currentBlizzard);
	}
	return newBlizzards;
}

auto comp = [](const pair<int, int> &a, const pair<int, int> &b) {return a.second > b.second; };

int main() {
    ifstream fileIn;
    fileIn.open("input.txt");
	
	string line;

    if (!fileIn)
    {
        cout<<"A error has occured, please contact support.";
		return -1;
    }
	
	vector<blizzard> blizzards;
	vector<cell> grid;
	vector<vector<cell>> grids;
	

	 std::string::size_type sz;   // alias of size_t
	// Read in a line
	int i=0;
	int j=0;
	int width=0;
	int height=0;
	cell entry=cell(make_pair(0,1),Empty);
	cell exit=cell(make_pair(0,1),Empty);
	//Node& rMunich = g.makeNode(Node("Munich"));
	while (getline(fileIn,line))
	{
		for (auto &currentChar : line){
			switch (currentChar)
			{	
				case '#':
					grid.push_back(cell(make_pair(i,j),Wall));
					break;
				case '.':
					grid.push_back(cell(make_pair(i,j),Empty));
					exit=cell(make_pair(i,j),Empty);
					//Node& rHamburg = g.makeNode<Node>("Node"+to_string(i)+"_"+to_string(j)+"0");
					break;
				case '<':
				case '>':
				case '^':
				case 'v':
					grid.push_back(cell(make_pair(i,j),Blizzard));
					blizzards.push_back(blizzard(make_pair(i,j),currentChar));
					break;
				default:
					cout << "wtf ! " << endl;
					break;
					
			}
			cout << currentChar ;
			i++;
			
		}
		cout <<endl;
		j++;
		width=i;
		i=0;
	}
	//Node& rHamburg = g.makeNode<Node>("Hamburg");
	height=j;
	cout << "height " << height <<" width " << width <<endl;
	
	grids.push_back(grid);
	vector<blizzard> next_blizzards;
	
	int a =width-2;
	int b=height-2;
	  int p=a*b;
	  while (a!=b) if (a<b) b-=a; else a-=b;
	  cout << "ppcm :  " << p/a <<endl;
	int numberofTurn =2*p/a;
	cout << "numberofTurn :  " << numberofTurn <<endl;
	int nbNodes=(numberofTurn+1)*width*height;
	
	vector<vector<pair<int, int>>> G(nbNodes); 
	
	for (int i=0;i<numberofTurn;i++){
		cout << " next bilzzard "<<i << endl;
		next_blizzards=updateBlizzards(blizzards,height-2,width-2);
		vector<cell> next_grid;
		for (auto &currentCell : grids[i]){
			cell tempCell = cell(currentCell.getPos(),currentCell.getType());
			if (currentCell.getType() != Wall){
				tempCell.setType(Empty);
				for (auto &currentBlizzard : next_blizzards){
					if (currentBlizzard.getPos() == tempCell.getPos()){
						tempCell.setType(Blizzard);
					}
				}
			}
			next_grid.push_back(tempCell);
		}
		for (auto &currentCell : next_grid){
			if (currentCell.getType() == Empty){
				//cout << ".";
			}
			else if(currentCell.getType() == Wall){
				//cout << "#";
			}
			else if(currentCell.getType() == Blizzard){
				//cout << "B";
			}
			if (currentCell.getPos().first==width-1){
				//cout <<endl;
			}
		}
		
		for (auto &currentCell : grids[i]){
			if (currentCell.getType() == Empty){
				int currentX=currentCell.getPos().first;
				int currentY=currentCell.getPos().second;
				int u=(currentX+width*currentY)+width*height*i;
				int v=(currentX+width*currentY)+width*height*(i+1);
				//cout <<" from " << u << endl;
				if (next_grid[currentX+width*currentY].getType() == Empty){
					G[u].push_back(make_pair(v, 1));
					//cout <<" to " << currentX << " " << currentY<< " ;";
				}
				if (next_grid[currentX+1+width*currentY].getType() == Empty){
					G[u].push_back(make_pair((currentX+1+width*currentY)+width*height*(i+1), 1));
					//cout <<" to " << currentX+1 << " " << currentY<< " ;";
				}
				if (next_grid[currentX-1+width*currentY].getType() == Empty){
					G[u].push_back(make_pair((currentX-1+width*currentY)+width*height*(i+1), 1));
					//cout <<" to " << currentX-1 << " " << currentY<< " ;";
				}
				if (next_grid[currentX+width*(currentY+1)].getType() == Empty){
					G[u].push_back(make_pair((currentX+width*(currentY+1))+width*height*(i+1), 1));
					//cout <<" to " << currentX << " " << currentY+1<< " ;";
				}
				if (currentX+width*(currentY-1)>0 && next_grid[currentX+width*(currentY-1)].getType() == Empty){
					G[u].push_back(make_pair((currentX+width*(currentY-1))+width*height*(i+1), 1));
					//cout <<" to " << currentX << " " << currentY-1<< " ;";
				}
				//cout << endl;
			}
		}
		grids.push_back(next_grid);
		blizzards=next_blizzards;
	}

	int StartNode=1;
	vector<int> Distances(nbNodes, numeric_limits<int>::max());                   
	Distances[StartNode] = 0;                                                     
	vector<int> Parents(nbNodes, -1);                                             
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> Q(comp);
	Q.push(make_pair(StartNode, 0));                                              
	while (!Q.empty()) {                                                          
	int w = Q.top().second;                                                     
	int v = Q.top().first;                                                     
	Q.pop();

	if (w <= Distances[v]) {                                            
		for (const auto& i : G[v]) {
			auto v2 = i.first;
			auto w2 = i.second;
		if (Distances[v] + w2 < Distances[v2]) {                                
			Distances[v2] = Distances[v] + w2;
			Parents[v2] = v;
			Q.push(make_pair(v2, Distances[v2]));
			}
		}
	}
}	
	int end;
	int res;
	for (int i = 0; i != nbNodes; ++i) {                                          // display the results
		if (i%(width*height)==width*height-2 && Distances[i]<width*height){
			cout << "\nPath from node " << StartNode << " to node " << i << " cost " << Distances[i] << endl;
			cout << i;
			for (auto p = Parents[i]; p != -1; p = Parents[p]){
				cout << " <- " << p;   
			}			
			cout << endl;
			res=Distances[i];
			end=i;
			break;
		}			
	}
	StartNode=end;
	vector<int> Distances2(nbNodes, numeric_limits<int>::max());                   
	Distances2[StartNode] = 0;                                                     
	vector<int> Parents2(nbNodes, -1);                                             
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> Q2(comp);
	Q2.push(make_pair(StartNode, 0));        
	while (!Q2.empty()) {                                                          
	int w = Q2.top().second;                                                     
	int v = Q2.top().first;                                                     
	Q2.pop();

	if (w <= Distances2[v]) {                                            
		for (const auto& i : G[v]) {
			auto v2 = i.first;
			auto w2 = i.second;
		if (Distances2[v] + w2 < Distances2[v2]) {                                
			Distances2[v2] = Distances2[v] + w2;
			Parents2[v2] = v;
			Q2.push(make_pair(v2, Distances2[v2]));
			}
		}
	}
	}
	int res2;
	int start2;
	for (auto i = 0; i != nbNodes; ++i) {                                          // display the results
		if (i%(width*height)==1 && Distances2[i]<width*height){
			cout << "\nPath from node " << StartNode << " to node " << i << " cost " << Distances2[i] << endl;
			cout << i;
			for (auto p = Parents2[i]; p != -1; p = Parents2[p]){
				cout << " <- " << p;   
			}			
			cout << endl;
			res2=Distances2[i];
			start2=i;
			break;
		}		
	}
	
	StartNode=start2;
	vector<int> Distances3(nbNodes, numeric_limits<int>::max());                   
	Distances3[StartNode] = 0;                                                     
	vector<int> Parents3(nbNodes, -1);                                             
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> Q3(comp);
	Q3.push(make_pair(StartNode, 0));                                              
	while (!Q3.empty()) {                                                          
	int w = Q3.top().second;                                                     
	int v = Q3.top().first;                                                     
	Q3.pop();

	if (w <= Distances3[v]) {                                            
		for (const auto& i : G[v]) {
			auto v2 = i.first;
			auto w2 = i.second;
		if (Distances3[v] + w2 < Distances3[v2]) {                                
			Distances3[v2] = Distances3[v] + w2;
			Parents3[v2] = v;
			Q3.push(make_pair(v2, Distances3[v2]));
			}
		}
	}
	}
	int res3;
	for (auto i = 0; i != nbNodes; ++i) {                                          // display the results
		if (i%(width*height)==width*height-2 && Distances3[i]<width*height){
			cout << "\nPath from node " << StartNode << " to node " << i << " cost " << Distances3[i] << endl;
			cout << i;
			for (auto p = Parents3[i]; p != -1; p = Parents3[p]){
				cout << " <- " << p;   
			}			
			cout << endl;
			res3=Distances3[i];
			break;
		}		
	}
	cout << "res1 :  " << res << endl;
	cout << "res2 :  " << res2 << endl;
	cout << "res3 :  " << res3 << endl;
	cout << "res :  " << res+res2+res3 << endl;
	
	
	return 0;
}

