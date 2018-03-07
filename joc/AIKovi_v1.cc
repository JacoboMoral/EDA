#include "Player.hh"
#include <stdlib.h>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Kovi1



struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  /**
   * Play method, invoked once per each round.
   */
  typedef vector<bool> Row;
  typedef vector<Row> Matriu;

  bool interessant(Pos actual){
      if(cell(Pos(actual.i,actual.j)).owner == 0) return false;
      if(cell(Pos(actual.i,actual.j)).haunted) return false;
      if(cell(Pos(actual.i,actual.j)).type == Wall) return false;
      if(cell(Pos(actual.i,actual.j)).id != -1) return false;
      if((actual.i > 36) or (actual.j > 36)) return false;
      if((actual.i < 0) or (actual.j < 0)) return false;
      return true;
  }


  bool dentro_limites(Pos nova){
      if((nova.i > 36) or (nova.j > 36)) return false;
      if((nova.i < 0) or (nova.j < 0)) return false;
      return true;
  }

  Pos cercaposicions(Pos act){
      Matriu pos_visitades(37, Row(37,false));
      queue<Pos> cua_posicions;
      cua_posicions.push(act);
      while (not cua_posicions.empty()){
          Pos temp = cua_posicions.front();
          cua_posicions.pop();
          if (not pos_visitades[temp.i][temp.j]){
              pos_visitades[temp.i][temp.j] = true;
              return temp;
              if (interessant(Pos(temp.i,temp.j + 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //derecha
              if (interessant(Pos(temp.i + 1,temp.j))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //arriba
              if (interessant(Pos(temp.i - 1,temp.j))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //abajo
              if (interessant(Pos(temp.i,temp.j - 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //izquierda
          }
      } return act;
  }


  typedef vector<int> VE;

  virtual void play () {
      VE meusfarmers = farmers(0);
        cout << "ronda: " << round() << endl;
      for (int id : meusfarmers){
         Pos target = cercaposicions(unit(id).pos);
         Pos actual = unit(id).pos;
         int distancia_vertical = target.i - actual.i;
         int distancia_horitzontal = target.j - actual.j;
         cout << "id: " << id << "    dist_vert: " << distancia_vertical << "    dist_horit: " << distancia_horitzontal << endl;
         cout << "posicio actual: " << actual.i << ' ' << actual.j << "    target: " << target.i << ' ' << target.j << endl << endl;

         if (abs(distancia_vertical) > abs(distancia_horitzontal)){
             if (distancia_vertical < 0) command(id,Bottom);
             else command(id,Top);
         }
         else{
             if (distancia_horitzontal < 0) command(id,Left);
             else command (id,Right);
         }
      }
  }

/*
  int distancia(int f, int c, vector< vector<char> > mapa) {
      int min_dist = 0;
      bool trobat = false;
      queue<posicio> pending;
      vector< vector<bool> > visitats ((int)mapa.size(), vector<bool>((int)mapa[0].size(),false));
      posicio act;
      act.f = f;
      act.c = c;
      act.d = 0;
      pending.push(act);
      while (not trobat and not pending.empty()){
          posicio aux = pending.front();
          pending.pop();
          if (not visitats[aux.f][aux.c]) {
              visitats[aux.f][aux.c] = true;
              if (mapa[aux.f][aux.c] == 't')
              {
                  trobat = true;
                  min_dist = aux.d;
              }
              else if (mapa[aux.f][aux.c] != 'X') {
                  if (aux.f > 0 and not visitats[aux.f-1][aux.c]) {
                      posicio amunt;
                      amunt.f = aux.f-1;
                      amunt.c = aux.c;
                      amunt.d = aux.d+1;
                      pending.push(amunt);
                  }
                  if (aux.f < (int)mapa.size()-1 and not visitats[aux.f+1][aux.c]) {
                      posicio avall;
                      avall.f = aux.f+1;
                      avall.c = aux.c;
                      avall.d = aux.d+1;
                      pending.push(avall);
                  }
                  if (aux.c > 0 and not visitats[aux.f][aux.c-1]) {
                      posicio esquerre;
                      esquerre.f = aux.f;
                      esquerre.c = aux.c-1;
                      esquerre.d = aux.d+1;
                      pending.push(esquerre);
                  }
                  if (aux.c < (int)mapa[0].size()-1 and not visitats[aux.f][aux.c+1]) {
                      posicio dreta;
                      dreta.f = aux.f;
                      dreta.c = aux.c+1;
                      dreta.d = aux.d+1;
                      pending.push(dreta);
                  }
              }
          }
      }
      return min_dist;
  }
*/



};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
