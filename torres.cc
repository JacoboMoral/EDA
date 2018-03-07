#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> row;
typedef vector<row> matrix;

bool valid(const vector<int> &v, int it){
    for (int i = 0; i < it; ++i){
	if (v[it] == v[i]) return false;
    }
    return true;
}

void dibujar(const vector<int> &v,int mm){
    matrix m(v.size(),row(mm,'.'));
    for (int i = 0; i < v.size(); ++i){
	m[i][v[i]] = 'R';
    }
    for (int i = 0; i < v.size(); ++i){
	for (int j = 0; j < mm; ++j){
	    cout << m[i][j];
	}
	cout << endl;
    }
    cout << endl;
}

void back_tracking(int it, vector<int> &v, int m){
    if (it != v.size()){
	for (int i = 0; i < m; ++i){
	    v[it] = i;
	    if (valid(v,it)){
		if (it != v.size()-1) back_tracking(it+1,v,m);
		else dibujar(v,m); 
	    }
	}
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector <int> v(n,-1);
    back_tracking(0,v,m);
}