#include <iostream>
#include <cstdio>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>

#include <bits/stdc++.h>

using namespace std;


struct Nodo{	
	vector<vector<char>> estado;//estado actual del nivel.
	string movimientos;//secuencia de movimientos que llevan al estado actual.
	int costoTotal;//Costo total de llegar al estado actual.
	int valorH;//valor para calcular la heuristica basada en distancia.
	bool nulo;
};


//Lee el nivel
vector<vector<char>> lectura(int numero){

	vector< vector<char> > m;
	
	string nombre = "levels/level_";
	
	nombre.append(to_string(numero) + ".txt");

	ifstream level;

	level.open(nombre);

	if(level.is_open()){
		
		string s;
		
		while(getline(level, s)){
			
			int l = s.length();
			char a[l+1];
			
			s.copy(a, l+1);
			
			a[l] = '\0';

			vector<char> row;
			
			for(int i=0; i<l+1; i++){
				
				row.push_back(a[i]);
			}
			
			m.push_back(row);
		}
		
		level.close();
	}
	
	else cout << "Error al leer el archivo";
	
	return m;

}

/*
//Retorna Nodo con el siguiente estado dependiendo del movimiento a revisar.
Nodo exploracion(const Nodo &actual, int x, int y, char direccion){

	Nodo nuevoNodo;
	nuevoNodo.nulo = true;
	char entidad;
	char destinoCaja;
	vector<vector<char>> estadoSiguiente;

	switch(direccion){

		case 'N'://Norte
			entidad = actual.estado[y-1][x];

			switch(entidad){

				case '$':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y-1][x] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}
				destinoCaja = estadoSiguiente[y-2][x];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y-2][x] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y-2][x] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("U\n");

				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '*':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y-1][x] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				destinoCaja = estadoSiguiente[y-2][x];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y-2][x] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y-2][x] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("U\n");

				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '.':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y-1][x] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("U\n");

				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case ' ':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y-1][x] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("U\n");

				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '#':
				break;			

				default:

				break;
			}

			break;

		case 'S'://Sur
			entidad = actual.estado[y+1][x];

			switch(entidad){

				case '$':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y+1][x] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}
				destinoCaja = estadoSiguiente[y+2][x];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y+2][x] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y+2][x] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("D\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '*':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y+1][x] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				destinoCaja = estadoSiguiente[y+2][x];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y+2][x] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y+2][x] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("D\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '.':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y+1][x] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("D\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case ' ':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y+1][x] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("D\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case '#':
				break;			

				default:
				
				break;
			}

			break;

		case 'E'://Este
			entidad = actual.estado[y][x+1];

			switch(entidad){

				case '$':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x+1] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}
				destinoCaja = estadoSiguiente[y][x+2];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y][x+2] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y][x+2] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("R\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '*':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x+1] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				destinoCaja = estadoSiguiente[y][x+2];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y][x+2] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y][x+2] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("R\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '.':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x+1] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("R\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case ' ':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x+1] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("R\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case '#':
				break;			

				default:
				
				break;
			}

			break;
		
		case 'O'://Oeste
			entidad = actual.estado[y][x-1];

			switch(entidad){

				case '$':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x-1] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}
				destinoCaja = estadoSiguiente[y][x-2];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y][x-2] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y][x-2] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("L\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '*':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x-1] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				destinoCaja = estadoSiguiente[y][x-2];

				if (destinoCaja == '#'){
					break;
				}
				else if (destinoCaja == '$'){
					break;
				}
				else if (destinoCaja == '*'){
					break;
				}
				else if (destinoCaja == ' '){
					estadoSiguiente[y][x-2] = '$';
				}
				else if (destinoCaja == '.'){
					estadoSiguiente[y][x-2] = '*';
				}
				else{
					break;
				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("L\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;

				case '.':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x-1] = '+';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("L\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case ' ':

				estadoSiguiente = actual.estado;

				estadoSiguiente[y][x-1] = '@';

				if(actual.estado[y][x] == '@'){

					estadoSiguiente[y][x] = ' ';

				}else{

					estadoSiguiente[y][x] = '.';

				}

				nuevoNodo = actual;

				nuevoNodo.movimientos.append("L\n");
				
				nuevoNodo.costoTotal += COSTO_MOVIMIENTO;			
				nuevoNodo.valorH = heuristica(nuevoNodo);			
				nuevoNodo.valorH += nuevoNodo.costoTotal;	
				nuevoNodo.estado = estadoSiguiente;
				nuevoNodo.nulo = false;

				return nuevoNodo;

				break;
				
				case '#':
				break;			

				default:
				
				break;
			}

			break;

		default:// O este otro xd
		
			break;	
	}

	return nuevoNodo;
}	


//Retorna una lista de estados futuros validos.
queue<Nodo> crearPosiblesFuturos (const Nodo &actual){

	queue<Nodo> movimientosValidos;

	vector< vector<char> > estadoSiguiente;
	Nodo nuevoNodo;

	char elArroba;
	int x = 1000;
	int y = 1000; 

	for(int i = 0; i < actual.estado.size(); i++){

		for(int j = 0; j < actual.estado[i].size(); j++){

			if(actual.estado[i][j] == '@' || actual.estado[i][j] == '+'){

				elArroba = actual.estado[i][j];
				x = j;
				y = i;
				break;
			}

		}

		if(x != 1000){
			break;
		}

	}
	

	nuevoNodo = exploracion(actual, x, y, 'N');
	if(!nuevoNodo.nulo){

		movimientosValidos.push(nuevoNodo);

	}

	nuevoNodo = exploracion(actual, x, y, 'S');
	if(!nuevoNodo.nulo){

		movimientosValidos.push(nuevoNodo);
		
	}

	nuevoNodo = exploracion(actual, x, y, 'E');
	if(!nuevoNodo.nulo){

		movimientosValidos.push(nuevoNodo);
		
	}

	nuevoNodo = exploracion(actual, x, y, 'O');
	if(!nuevoNodo.nulo){

		movimientosValidos.push(nuevoNodo);
		
	}

	return movimientosValidos;
}
*/

//Función para marcar las esquinas del nivel
vector<vector<char>> esquinar (vector<vector<char>> level){

	int n = level.size(); //número de filas del nivel

	int m; //número de columna

	for(int i=0; i<n; i++){

		m = level.at(i).size();

		for(int j=0; j<m; j++){

			if(j-1>=0 && level[i][j-1] == '#'){

				if(i-1>=0 && level[i-1][j] == '#'){

					if(level[i][j] == ' '){

						level[i][j] = 'e';
					}
					else if(level[i][j] == '@'){

						level[i][j] = 'E';
					}
				}

				if(i+1<n && level[i+1][j] == '#'){

					if(level[i][j] == ' '){

						level[i][j] = 'e';
					}
					else if(level[i][j] == '@'){

						level[i][j] = 'E';
					}
				}
			}

			if(j+1<m && level[i][j+1] == '#'){

				if(i-1>=0 && level[i-1][j] == '#'){

					if(level[i][j] == ' '){

						level[i][j] = 'e';
					}
					else if(level[i][j] == '@'){

						level[i][j] = 'E';
					}
				}

				if(i+1<n && level[i+1][j] == '#'){

					if(level[i][j] == ' '){

						level[i][j] = 'e';
					}
					else if(level[i][j] == '@'){

						level[i][j] = 'E';
					}
				}
			}
		}
	}

	return level;
}

vector<vector<char>> paredear (vector<vector<char>> level){

	int n = level.size(); //número de filas del nivel

	int m, l; //número de columna

	bool izquierda, derecha, arriba, abajo;

	for(int i=0; i<n; i++){

		m = level.at(i).size();

		for(int j = 0; j < m; j++){

			if(level[i][j] == 'e'){

				derecha = false;
				abajo = false;
				arriba = false;
				izquierda = false;

				//Si se encuentra esquina con pared arriba e izquierda
				if(i-1 >= 0 && level[i-1][j] == '#'){

					if(j-1 >= 0 && level[i][j-1] == '#'){

						//revisa la pared hacia la derecha
						for(int k = j+1; k < m; k++){

							if(level[i-1][k] != '#'){

								break;

							}

							if(level[i][k] == '*' || level[i][k] == '.'){

								break;

							}

							if(level[i][k] == 'e'){

								derecha = true;
								break;

							}

						}

						//revisa la pared hacia abajo
						for(int k = i+1; k < n; k++){

							if(level[k][j-1] != '#'){

								break;

							}

							if(level[k][j] == '*' || level[k][j] == '.'){

								break;

							}

							if(level[k][j] == 'e'){

								abajo = true;
								break;

							}

						}

						//Si se encontro 'e' hacia la derecha
						if(derecha){

							l = j+1;

							while(l < m && level[i][l] != 'e'){

								if(level[i][l] == ' '){

									level[i][l] = 'd';

								}
								else if(level[i][l] == '@'){

									level[i][l] = 'D';

								}

								l++;

							}

						}

						//Si se encontro 'e' hacia abajo
						if(abajo){

							l = i+1;

							while(l < n && level[l][j] != 'e'){

								if(level[l][j] == ' '){

									level[l][j] = 'd';

								}
								else if(level[l][j] == '@'){

									level[l][j] = 'D';

								}

								l++;

							}

						}

					}

				}

				//Si se encuentra esquina con pared abajo y derecha				
				if(i+1 < n && level[i+1][j] == '#'){

					if(j+1 < m && level[i][j+1] == '#'){

						//revisa la pared hacia la izquierda
						for(int k = j-1; k >= 0; k--){

							if(level[i+1][k] != '#'){

								break;

							}

							if(level[i][k] == '*' || level[i][k] == '.'){

								break;

							}

							if(level[i][k] == 'e'){

								izquierda = true;
								break;

							}

						}

						//revisa la pared hacia arriba
						for(int k = i-1; k >= 0; k--){

							if(level[k][j+1] != '#'){

								break;

							}

							if(level[k][j] == '*' || level[k][j] == '.'){

								break;

							}

							if(level[k][j] == 'e'){

								arriba = true;
								break;

							}

						}

						//Si se encontro 'e' hacia la izquierda
						if(izquierda){

							l = j-1;

							while(l >= 0 && level[i][l] != 'e'){

								if(level[i][l] == ' '){

									level[i][l] = 'd';

								}
								else if(level[i][l] == '@'){

									level[i][l] = 'D';

								}

								l--;

							}

						}

						//Si se encontro 'e' hacia arriba
						if(arriba){

							l = i-1;

							while(l >= 0 && level[l][j] != 'e'){

								if(level[l][j] == ' '){

									level[l][j] = 'd';

								}
								else if(level[l][j] == '@'){

									level[l][j] = 'D';

								}

								l--;

							}

						}

					}

				}

			}

		}	

	}
	return level;

}

int main(){


	vector<vector<char>> level;
	vector<vector<char>> esquinas;
	int numero;
	
	cout << "Ingrese el número del nivel (1-155): ";
	cin >> numero;
	
	if(numero < 1 || numero > 155){
		
		cout << "ERROR en número\n";
		
		return 0;
	}
	
	level = lectura(numero);

	esquinas = esquinar(level);

	esquinas = paredear(esquinas);

	for(int i=0; i<esquinas.size(); i++){

		for(int j=0; j<esquinas.at(i).size(); j++){

			cout<<esquinas[i][j];
		}

		cout<<"\n";
	}

	return 0;
}
