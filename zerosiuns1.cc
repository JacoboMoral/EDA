#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> V;

void back_tracking(V &v,int it){
    if (it == v.size()){
	cout << v[0];
	for (int i = 1; i < it; ++i){
	    cout << ' ' << v[i];
	}
	cout << endl;
    }
    else{
	back_tracking(v,it+1);
	v[it] = 1;
	back_tracking(v,it+1);
	v[it] = 0;
    }
}


int main(){
    int n;
    cin >> n;
    V v(n,0);
    back_tracking(v,0);
}


/*int n = v.size();
if (it == n){ sacar vector
else{
    backtracking(v,it+1);
    v[it] = 1;
    backtracking(v,it+1);
    v[it] = 0;
}*/
