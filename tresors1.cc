#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


typedef vector<char> Fila;
typedef vector<Fila> Matriu;

void entrada(int h, int w, vector< vector <char> > &m, int &x, int &y){
  for (int i = 0; i < h; ++i){
    for (int j = 0; j < w; ++j){
	cin >> m[i][j];
    }
  }
    cin >> x >> y;
}

bool wasVisited(const Matriu& visited, int x, int y) {
    return visited[x][y];
}

bool validPosition(const Matriu& m, int x, int y) {
    return not(x < 0 or x >= m.size() or y < 0 or y >= m[0].size());
}
  
bool tressor(const Matriu &m,int h, int w, int x, int y, Matriu& visited){
    if (m[x][y] == 't') return true;
    else if (m[x][y] == 'X') return false;
    else{
	visited[x][y] = true;
	
	if (validPosition(m, x+1, y) and not wasVisited(visited, x+1, y)) {
	    if(tressor(m,h,w,x+1,y,visited)) return true;
	    visited[x+1][y] = true;
	}
	if (validPosition(m, x-1, y) and not wasVisited(visited, x-1, y)) {
	    if(tressor(m,h,w,x-1,y,visited)) return true;
	    visited[x-1][y] = true;
	}
	if (validPosition(m, x, y+1) and not wasVisited(visited, x, y+1)) {
	    if(tressor(m,h,w,x,y+1,visited)) return true;
	    visited[x][y+1] = true;
	}
	if (validPosition(m, x, y-1) and not wasVisited(visited, x, y-1)) {
	    if(tressor(m,h,w,x,y-1,visited)) return true;
	    visited[x][y-1] = true;
	}
    }
    return false;
}
	
	

int main(){
    int h, w, x, y;
    cin >> h >> w;
    
    Matriu m(h, Fila(w));
    Matriu visited(h, Fila(w, false));
    entrada(h,w,m,x,y);
    
    bool yn = tressor(m, h,w, x-1 , y-1, visited);
    if (yn) cout << "yes" << endl;
    else cout << "no" << endl;
}