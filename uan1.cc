#include <vector>
#include <iostream>
using namespace std;

void back_tracking(int it, vector<int> &v, vector<bool> &b){
    if (it == v.size()){
	cout << '(' << v[0];
	for (int i = 1; i < v.size(); ++i){
	    cout << ',' << v[i];
	}
	cout << ')' << endl;
    }
    else{
	for (int i = 0; i < v.size(); ++i){
	    if (not b[i]){
		b[i] = true;
		v[it] = i+1;
		back_tracking(it+1,v,b);
		b[i] = false;
	    }
	}
    }
}

int main(){
    int m;
    cin >> m;
    vector<int> v(m);
    vector<bool> b(m,false);
    back_tracking(0,v,b);
}