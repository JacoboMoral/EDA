#include <iostream>
#include <vector>
#include <string>
using namespace std;

void back_tracking(int it, vector<int> &v, vector<string> &vs, vector<bool> &b){
    if (it == v.size()){
	cout << '(' << v[0];
	for (int i = 1; i < v.size(); ++i){
	    cout << ',' << vs[v[i]];
	}
	cout << ')' << endl;
    }
    else{
	for (int i = 0; i < v.size(); ++i){
	    if (not b[i]){
		b[i] = true;
		v[it] = i;
		back_tracking(it+1,v,vs,b);
	    }
	}
    }
    
}


int main(){
    int n;
    cin >> n;
    vector<string> vs(n);
    for (int i = 0; i < n; ++i){
	cin >> vs[i];
    }
    vector<bool>b(n,false);
    vector<int> v(n);
    back_tracking(0,v,vs,b);
}