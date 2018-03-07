#include "Player.hh"
#include <stdlib.h>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Kovi



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
      if(cell(Pos(nova.i,nova.j)).haunted) return false;
      if(cell(Pos(nova.i,nova.j)).id != -1) return false;
      return true;
  }

  Pos cercaposicions(Pos act){
      bool found = false;
      Matriu pos_visitades(37, Row(37,false));
      queue<Pos> cua_posicions;
      cua_posicions.push(act);
      while (not found and ! cua_posicions.empty()){
          Pos temp = cua_posicions.front();
          cua_posicions.pop();
          if (not pos_visitades[temp.i][temp.j]){
              pos_visitades[temp.i][temp.j] = true;
              if (interessant(temp)){
                  found = true;
                  return temp;
              }
              else{
                  if (dentro_limites(Pos(temp.i,temp.j + 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //derecha
                  if (dentro_limites(Pos(temp.i + 1,temp.j))) cua_posicions.push(Pos(temp.i + 1,temp.j)); //abajo
                  if (dentro_limites(Pos(temp.i - 1,temp.j))) cua_posicions.push(Pos(temp.i - 1,temp.j)); //arriba
                  if (dentro_limites(Pos(temp.i,temp.j - 1))) cua_posicions.push(Pos(temp.i,temp.j - 1)); //izquierda
              }
          }
      }
      cout << "me cago en tpm" << endl;
      return act;
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


         if (target == actual) command(id,None);
         else{
             Cell check_cell;
             if (abs(distancia_vertical) > abs(distancia_horitzontal)){
                 if (distancia_vertical < 0){
                     check_cell = Cell(actual.i-1,actual.j);
                     command(id,Top);
                 }

                 else command(id,Bottom);
             }
             else{
                 if (distancia_horitzontal < 0) command(id,Left);
                 else command (id,Right);
             }
         }
      }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
