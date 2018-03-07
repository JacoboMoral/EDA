#include <iostream>
#include <vector>

using namespace std;


int fixedp(int a,vector <int> &v, int esq, int dre){
  if (esq > dre) return -1;
  int mid=(dre+esq)/2;
  if (v[mid] + a == mid and (mid == 0 or v[mid-1]+1 != mid)) return v[mid];  
  if (v[mid]+1 < mid) return fixedp(a, v, mid + 1, dre);
  else return fixedp(a, v, esq, mid - 1);
}

int main(){
  int n;
  cin >> n;
  vector <int> s(n);
  for (int i=0; i<n; ++i){
    cin >> s[i];
  }
  cin >> n;
  int a;
  for (int i=0; i<n; ++i){
    cin >> a;
    int r = fixedp(a,s,0,n-1);
    if (r != -1){
      cout << "fixed point for " << a << ": " << r << endl;
    }
    else cout << "no fixed point for " << a << endl;
  }
}
    