#include <iostream>
#include <vector>
using namespace std;

int posicio(double x, const vector<double>& v, int esq, int dre){
  int mid = (dre+esq)/2;
  if (dre < esq) return -1;
  else if (v[mid] == x) return mid;
  else if (x > v[mid]) return posicio(x,v,mid+1,dre);
  else if (x < v[mid]) return posicio(x,v,esq,mid-1 );
}

int main(){
  vector <double> vec(10);
  for(int i=0; i<10; ++i){
    cin >> vec[i];
  }
  int pos = posicio(8,vec,0,9);
  cout << pos << endl;
}