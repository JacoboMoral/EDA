#include <iostream>
#include <vector>
using namespace std;


void back_tracking(int it, vector<int> &v, const vector<char> &c){
    if (it == v.size()){
	for (int i = 0; i < it; ++i){
	    cout << c[v[i]];
	}
	cout << endl;
    }
    else{
	for (int i = 0; i < 4; ++i){
	    v[it] = i;
	    back_tracking(it+1,v,c);
	}
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    vector<char> c(4);
    c[0] = 'A';
    c[1] = 'C';
    c[2] = 'G';
    c[3] = 'T';
    back_tracking(0,v,c);
}