#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool valid(vector<int> &v,int it){
    for(int i = 0; i < it; ++i){
	if (v[i] == v[it]) return false;
	if (abs(v[i] - v[it]) == abs(i - it)) return false;
    }
    return true;
}

void back_tracking(int it, vector<int> &v, int &maneras){
    if (v.size() != it){
	for (int i = 0; i < v.size(); ++i){
	    v[it] = i;
	    if (valid(v,it)){
		if( it == v.size() - 1) ++maneras; 
		else back_tracking(it+1,v,maneras);
	    } 
	}
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    int maneras = 0;
    back_tracking(0,v,maneras);
    cout << maneras << endl;
    
}