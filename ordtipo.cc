#include <vector>
#include <iostream>
#include <string>
#include <queue>
using namespace std;


typedef vector<int> Fila;
typedef vector<Fila> Matriu;

void escriure(vector<int> &v){
    for (int i = 0; i < v.size()-1; ++i){
	cout << v[i] << ' ';
    }
    cout << v[v.size()-1] << endl;
}


int main(){
    int n, m;
    while (cin >> n >> m){
	priority_queue(int) pq;
	for (int i = 0; i < n; ++i){
	    pq.push(0);
	}
	vector<int> result(n);
	Matriu mat(n, Fila(0));
	int x, y;
	for (int i = 0; i < m; ++i){
	    cin >> x >> y;
	    mat[x].push_back(y);
	    ++v[y];
	}
	for (int j = 0; j < n; ++j){
	    bool cont = true;
	    for (int i = 0; ((i < n) and cont); ++i){
		if (v[i] == 0){
		    result[j] = i;
		    for (int h = 0; h < mat[i].size(); ++h){
			--v[mat[i][h]];
		    }
		    --v[i];
		    cont = false;
		}
	    }
	}
	escriure(result);
    }
}
    