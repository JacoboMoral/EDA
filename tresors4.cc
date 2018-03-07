#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pos{
    int x;
    int y;
    int dist;
};

typedef vector<char> Fila;
typedef vector<Fila> Matriu;

typedef vector<bool> Filb;
typedef vector<Filb> Matrib;


void leer(Matriu &mapa, Matrib &mapb){
    for (int i = 0; i < mapa.size(); ++i){
        for (int j = 0; j < mapa[0].size(); ++j){
            cin >> mapa[i][j];
	    if (mapa[i][j] == 'X') mapb[i][j] = true;
        }
    }
}

bool fora_limits(int x, int y, const Matriu &mapa){
    if (x >= mapa.size()) return true;
    else if (y >= mapa[0].size()) return true;
    else if (x < 0 or y < 0) return true;
    else return false;
}

void push(queue<Pos> &pendents, int x, int y, int dist){
    Pos aux;
    aux.x = x;
    aux.y = y;
    aux.dist = dist + 1;
    pendents.push(aux);
}



int cerca(const Matriu &mapa, Matrib &mapb, int x, int y){
    queue<Pos> pendents;
    Pos aux;
    aux.x = x;
    aux.y = y;
    aux.dist = 0;
    pendents.push(aux);
    vector<int> distancies;
    while (not pendents.empty()){
	Pos temp = pendents.front();
	pendents.pop();
	if (not mapb[temp.x][temp.y]){
	    mapb[temp.x][temp.y] = true;
	    if (mapa[temp.x][temp.y] == 't') distancies.push_back(temp.dist);
	    
	    if (not fora_limits(temp.x + 1, temp.y, mapa)) push(pendents,temp.x + 1, temp.y, temp.dist);
	    if (not fora_limits(temp.x - 1, temp.y, mapa)) push(pendents,temp.x - 1, temp.y, temp.dist);
	    if (not fora_limits(temp.x, temp.y + 1, mapa)) push(pendents,temp.x, temp.y + 1, temp.dist);
	    if (not fora_limits(temp.x, temp.y - 1, mapa)) push(pendents,temp.x, temp.y - 1, temp.dist);
	}
    }
    int distanciafinal = -1; 
    for(int i = 0; i < distancies.size(); ++i){
	if (distanciafinal < distancies[i]) distanciafinal = distancies[i];
    }
    return distanciafinal;
}
    
    
int main(){
    int n, m;
    cin >> n >> m;
    Matriu mapa(n, Fila(m));
    Matrib mapb(n, Filb(m,false));
    leer(mapa, mapb);
    int temp1,temp2;
    cin >> temp1 >> temp2;  
    int r = cerca(mapa,mapb, temp1-1,temp2-1);
    if (r != -1){
        cout << "distancia maxima: " << r << endl;
    }
    else cout << "no es pot arribar a cap tresor" << endl;
}
