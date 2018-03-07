#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(){
  map <string, int> jugadors;
  string jugador;
  string accio;
  int guany;
  map <string, int>::iterator it;
  while (cin >> jugador >> accio){
    it = jugadors.find(jugador);
    if (it == jugadors.end()){
      if (accio == "enters") jugadors.insert(make_pair(jugador,0));
      else cout << jugador << " is not in the casino" << endl;
      if (accio == "wins") cin >> guany;
    }
    else if (accio == "enters") cout << jugador << " is already in the casino" << endl;
    else if (accio == "wins"){
      cin >> guany;
      it -> second += guany;
    }
    else if (accio == "leaves"){
      cout << jugador << " has won " << it -> second << endl;;
      jugadors.erase(it);
    }
  }
  cout << "----------" << endl;
  for (it = jugadors.begin(); it != jugadors.end(); ++it){
    cout << it ->first << " is winning " << it -> second << endl;
  }
}