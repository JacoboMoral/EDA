#include "Player.hh"
#include <stdlib.h>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Test



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



//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------CODIGO DE LOS FARMERS----------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------


    bool viable_farmer(Pos posicio){ //fisicamente posible entrar y no esta encantada
		Cell c = cell(posicio);
        if((posicio.i > 36) or (posicio.j > 36)) return false;
        if((posicio.i < 0) or (posicio.j < 0)) return false;
        if(c.type == Wall) return false;
        if(c.haunted) return false;
        if(c.id != -1) return false; //no puedo entrar si hay una unidad dentro
        return true;
    }


    bool interessant_farmer(Pos posicio){ //viable y no es de mi dominio
        if(cell(posicio).owner == 0) return false;
		return viable_farmer(posicio);
    }


    Pos cercaposicions_farmers(Pos act){
        Matriu pos_visitades(37, Row(37,false));
        queue<Pos> cua_posicions;
        cua_posicions.push(act);
        while (!cua_posicions.empty()){
            Pos temp = cua_posicions.front();
            cua_posicions.pop();
            if (not pos_visitades[temp.i][temp.j]){
                pos_visitades[temp.i][temp.j] = true;
                if (interessant_farmer(temp)){
                    return temp;
                }
                else{ //  ¿por que aqui no funciona if interessant ... -> queue.push?
                    if (viable_farmer(Pos(temp.i,temp.j + 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //derecha
                    if (viable_farmer(Pos(temp.i + 1,temp.j))) cua_posicions.push(Pos(temp.i + 1,temp.j)); //abajo
                    if (viable_farmer(Pos(temp.i - 1,temp.j))) cua_posicions.push(Pos(temp.i - 1,temp.j)); //arriba
                    if (viable_farmer(Pos(temp.i,temp.j - 1))) cua_posicions.push(Pos(temp.i,temp.j - 1)); //izquierda
                }
            }
        }
        cout << "No hay ninguna posicion a la que quiera ir" << endl;
        return act;
    }


    void command_farmer(int id, int v, int h, Pos actual){
        //para mejorar, hacer buffer con los ultimos movimientos (3 o 4), si se repiten algunos
        //entonces random entre los otros dos posibles, si se puede
        if (abs(v) > abs(h)){ //--> mueve vertical
            if (v > 0){ //--> mueve abajo
                if (viable_farmer(Pos(actual.i+1,actual.j))) command(id,Bottom);
                else{ //ahora miramos si izq o derecha, cual viene mejor
					//int rand = random(0,1);
                    if (h < 0 and viable_farmer(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_farmer(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_farmer(Pos(actual.i-1,actual.j))) command(id,Top);
					//else if (rand == 1 and viable_farmer(Pos(actual.i,actual.j+1))) command(id,Right);
					//else if (rand == 0 and viable_farmer(Pos(actual.i,actual.j+1))) command(id,Left);
					//si ponemos estas lineas: ---RECORDAR--- quitar/poner h >= 0 --> h > 0
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve arriba
                if (viable_farmer(Pos(actual.i-1,actual.j))) command(id,Top);
                else{ //miramos lados
                    if (h < 0 and viable_farmer(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_farmer(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_farmer(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            //si v == 0, v no sera mas grande que h y no estaremos aqui dentro, y si fueran
            // iguales, no estariamos ni en esta funcion porque target == actual y seria command(id,None);
        }
        else{ // --> mueve horizontal
            if (h > 0){ //--> mueve derecha
                if (viable_farmer(Pos(actual.i,actual.j+1))) command(id,Right);
                else{ //miramos vertical
                    if (v < 0 and viable_farmer(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_farmer(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_farmer(Pos(actual.i,actual.j-1))) command(id,Left);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve izquierda
                if (viable_farmer(Pos(actual.i,actual.j-1))) command(id,Left);
                else{ //miramos vertical
                    if (v < 0 and viable_farmer(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_farmer(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_farmer(Pos(actual.i,actual.j+1))) command(id,Right);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
        }
    }


    void moviment_farmers(){
        VE meusfarmers = farmers(0);
	cout << "Ronda: " << round() << endl;
        for (int id : meusfarmers){
            Pos target = cercaposicions_farmers(unit(id).pos);
            Pos actual = unit(id).pos;
            int distancia_vertical = target.i - actual.i;
            int distancia_horitzontal = target.j - actual.j;


            cout << "Farmer id: " << id << "    dist_vert: " << distancia_vertical << "    dist_horit: " << distancia_horitzontal << endl;
            cout << "posicio actual: " << actual.i << ' ' << actual.j << "    target: " << target.i << ' ' << target.j << endl << endl;


            if (target == actual) command(id,None);
            else command_farmer(id, distancia_vertical, distancia_horitzontal, actual);
        }
    }






//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------CODIGO DE LOS KNIGHTS----------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------


	bool viable_knight(Pos posicio){ //fisicamente posible entrar y no esta encantada
		Cell c = cell(posicio);
        if((posicio.i > 36) or (posicio.j > 36)) return false;
        if((posicio.i < 0) or (posicio.j < 0)) return false;
        if(c.type == Wall) return false;
        if(c.haunted) return false;
        return true;
    }


	bool interessant_knight(Pos posicio){
		if (unit(cell(posicio).id).player == 0) return false;
		if (unit(cell(posicio).id).type == Witch) return false;
		if (cell(posicio).id == -1) return false;
		return viable_knight(posicio);
	}


	Pos cercaposicions_knights(Pos act){
		Matriu pos_visitades(37, Row(37,false));
        queue<Pos> cua_posicions;
        cua_posicions.push(act);
        while (!cua_posicions.empty()){
            Pos temp = cua_posicions.front();
            cua_posicions.pop();
            if (not pos_visitades[temp.i][temp.j]){
                pos_visitades[temp.i][temp.j] = true;
                if (interessant_knight(temp)){
                    return temp;
                }
                else{ //  ¿por que aqui no funciona if interessant ... -> queue.push?
                    if (viable_knight(Pos(temp.i,temp.j + 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //derecha
                    if (viable_knight(Pos(temp.i + 1,temp.j))) cua_posicions.push(Pos(temp.i + 1,temp.j)); //abajo
                    if (viable_knight(Pos(temp.i - 1,temp.j))) cua_posicions.push(Pos(temp.i - 1,temp.j)); //arriba
                    if (viable_knight(Pos(temp.i,temp.j - 1))) cua_posicions.push(Pos(temp.i,temp.j - 1)); //izquierda
                }
            }
        }
        cout << "No hay ninguna posicion a la que quiera ir" << endl;
        return act;
	}


    void command_knight(int id, int v, int h, Pos actual){
		//para mejorar, hacer buffer con los ultimos movimientos (3 o 4), si se repiten algunos
        //entonces random entre los otros dos posibles, si se puede
        if (abs(v) > abs(h)){ //--> mueve vertical
            if (v > 0){ //--> mueve abajo
                if (viable_knight(Pos(actual.i+1,actual.j))) command(id,Bottom);
                else{ //ahora miramos si izq o derecha, cual viene mejor
					//int rand = random(0,1);
                    if (h < 0 and viable_knight(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_knight(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_knight(Pos(actual.i-1,actual.j))) command(id,Top);
					//else if (rand == 1 and viable_knight(Pos(actual.i,actual.j+1))) command(id,Right);
					//else if (rand == 0 and viable_knight(Pos(actual.i,actual.j+1))) command(id,Left);
					//si ponemos estas lineas: ---RECORDAR--- quitar/poner h >= 0 --> h > 0
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve arriba
                if (viable_knight(Pos(actual.i-1,actual.j))) command(id,Top);
                else{ //miramos lados
                    if (h < 0 and viable_knight(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_knight(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_knight(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            //si v == 0, v no sera mas grande que h y no estaremos aqui dentro, y si fueran
            // iguales, no estariamos ni en esta funcion porque target == actual y seria command(id,None);
        }
        else{ // --> mueve horizontal
            if (h > 0){ //--> mueve derecha
                if (viable_knight(Pos(actual.i,actual.j+1))) command(id,Right);
                else{ //miramos vertical
                    if (v < 0 and viable_knight(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_knight(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_knight(Pos(actual.i,actual.j-1))) command(id,Left);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve izquierda
                if (viable_knight(Pos(actual.i,actual.j-1))) command(id,Left);
                else{ //miramos vertical
                    if (v < 0 and viable_knight(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_knight(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_knight(Pos(actual.i,actual.j+1))) command(id,Right);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
        }
	}


    void moviment_knights(){
		VE meusknights = knights(0);
	cout << "Ronda: " << round() << endl;
        for (int id : meusknights){
            Pos target = cercaposicions_knights(unit(id).pos);
            Pos actual = unit(id).pos;
            int distancia_vertical = target.i - actual.i;
            int distancia_horitzontal = target.j - actual.j;


            cout << "Knight id: " << id << "    dist_vert: " << distancia_vertical << "    dist_horit: " << distancia_horitzontal << endl;
            cout << "posicio actual: " << actual.i << ' ' << actual.j << "    target: " << target.i << ' ' << target.j << endl;
			cout << "tipo de objetivo: " << unit(cell(target).id).type << "      equipo: " << unit(cell(target).id).player << endl << endl;


            if (target == actual) command(id,None);
            else command_knight(id, distancia_vertical, distancia_horitzontal, actual);
        }
    }






//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------CODIGO DE LAS WITCHES----------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------


    bool viable_witch(Pos posicio){ //fisicamente posible entrar y no esta encantada
		Cell c = cell(posicio);
        if((posicio.i > 36) or (posicio.j > 36)) return false;
        if((posicio.i < 0) or (posicio.j < 0)) return false;
        if(c.type == Wall) return false;
        if(unit(cell(posicio).id).type == Witch) return false; //solo no puedo entrar si hay otra witch, else podre entrar porque habra muerto mientras voy (jaja)
        return true;
    }


    bool interessant_witch(Pos posicio){ //viable y no es de mi dominio
        if(cell(posicio).owner == 0) return false;
		return viable_farmer(posicio);
    }


	Pos cercaposicions_witches(Pos act){
		Matriu pos_visitades(37, Row(37,false));
        queue<Pos> cua_posicions;
        cua_posicions.push(act);
        while (!cua_posicions.empty()){
            Pos temp = cua_posicions.front();
            cua_posicions.pop();
            if (not pos_visitades[temp.i][temp.j]){
                pos_visitades[temp.i][temp.j] = true;
                if (interessant_witch(temp)){
                    return temp;
                }
                else{ //  ¿por que aqui no funciona if interessant ... -> queue.push?
                    if (viable_witch(Pos(temp.i,temp.j + 1))) cua_posicions.push(Pos(temp.i,temp.j + 1)); //derecha
                    if (viable_witch(Pos(temp.i + 1,temp.j))) cua_posicions.push(Pos(temp.i + 1,temp.j)); //abajo
                    if (viable_witch(Pos(temp.i - 1,temp.j))) cua_posicions.push(Pos(temp.i - 1,temp.j)); //arriba
                    if (viable_witch(Pos(temp.i,temp.j - 1))) cua_posicions.push(Pos(temp.i,temp.j - 1)); //izquierda
                }
            }
        }
        cout << "No hay ninguna posicion a la que quiera ir" << endl;
        return act;
	}

    void command_witch(int id, int v, int h, Pos actual){
		if (abs(v) > abs(h)){ //--> mueve vertical
            if (v > 0){ //--> mueve abajo
                if (viable_witch(Pos(actual.i+1,actual.j))) command(id,Bottom);
                else{ //ahora miramos si izq o derecha, cual viene mejor
					//int rand = random(0,1);
                    if (h < 0 and viable_witch(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_witch(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_witch(Pos(actual.i-1,actual.j))) command(id,Top);
					//else if (rand == 1 and viable_witch(Pos(actual.i,actual.j+1))) command(id,Right);
					//else if (rand == 0 and viable_witch(Pos(actual.i,actual.j+1))) command(id,Left);
					//si ponemos estas lineas: ---RECORDAR--- quitar/poner h >= 0 --> h > 0
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve arriba
                if (viable_witch(Pos(actual.i-1,actual.j))) command(id,Top);
                else{ //miramos lados
                    if (h < 0 and viable_witch(Pos(actual.i,actual.j-1))) command(id,Left);
                    else if (h >= 0 and viable_witch(Pos(actual.i,actual.j+1))) command(id,Right);
                    else if (viable_witch(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            //si v == 0, v no sera mas grande que h y no estaremos aqui dentro, y si fueran
            // iguales, no estariamos ni en esta funcion porque target == actual y seria command(id,None);
        }
        else{ // --> mueve horizontal
            if (h > 0){ //--> mueve derecha
                if (viable_witch(Pos(actual.i,actual.j+1))) command(id,Right);
                else{ //miramos vertical
                    if (v < 0 and viable_witch(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_witch(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_witch(Pos(actual.i,actual.j-1))) command(id,Left);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
            else{ // --> mueve izquierda
                if (viable_witch(Pos(actual.i,actual.j-1))) command(id,Left);
                else{ //miramos vertical
                    if (v < 0 and viable_witch(Pos(actual.i-1,actual.j))) command(id,Top);
                    else if (v >= 0 and viable_witch(Pos(actual.i+1,actual.j))) command(id,Bottom);
                    else if (viable_witch(Pos(actual.i,actual.j+1))) command(id,Right);
                    else command(id,None); //solo si esta atrapado por los cuatro lados
                }
            }
        }
	}

    void moviment_witches(){
		VE meveswitches = witches(0);
	cout << "Ronda: " << round() << endl;
        for (int id : meveswitches){
            Pos target = cercaposicions_witches(unit(id).pos);
            Pos actual = unit(id).pos;
            int distancia_vertical = target.i - actual.i;
            int distancia_horitzontal = target.j - actual.j;


            cout << "Witch id: " << id << "    dist_vert: " << distancia_vertical << "    dist_horit: " << distancia_horitzontal << endl;
            cout << "posicio actual: " << actual.i << ' ' << actual.j << "    target: " << target.i << ' ' << target.j << endl;

            if (target == actual) command(id,None);
            else command_witch(id, distancia_vertical, distancia_horitzontal, actual);
        }
    }


    typedef vector<int> VE;

    virtual void play () {
        moviment_farmers();
        moviment_knights();
        moviment_witches();
    }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
