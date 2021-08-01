#include <bits/stdc++.h>
#include <sys/time.h>

#define COSTO_MOVIMIENTO 1

using namespace std;

struct Nodo
{	
	vector<vector<char>> estado;//estado actual del nivel.
	string movimientos;//secuencia de movimientos que llevan al estado actual.
	int costoTotal;//Costo total de llegar al estado actual.
	int valorH;//valor para calcular la heuristica basada en distancia.
	bool nulo;
};

//Heuristica
int heuristica(const Nodo &actual){

	int x, y;
	vector< pair<int, int> > cajas;
	vector< pair<int, int> > metas;
	vector< pair<int, int> > deadlocks;
 	int valor = 0;
	int radioElArroba = 1000;

	int disHorizontal;
	int disVertical;

	int sumaDistancias;
	int minDead;


	//Identifica posiciones de entidades
	for(int i = 0; i < actual.estado.size(); i++){

		for(int j = 0; j < actual.estado[i].size(); j++){

			if (actual.estado[i][j] == '@' ){

				x = j;
				y = i;

			}else if (actual.estado[i][j] == 'E' || actual.estado[i][j] == 'D' ){

				x = j;
				y = i;
				pair<int, int> aux(j,i);
				deadlocks.push_back(aux);
			
			}else if (actual.estado[i][j] == 'e' || actual.estado[i][j] == 'd' ){

				pair<int, int> aux(j,i);
				deadlocks.push_back(aux);

			}
			else if (actual.estado[i][j] == '+' ){

				x = j;
				y = i;
				pair<int, int> aux(j,i);
				metas.push_back(aux);

			}else if (actual.estado[i][j] == '$' ){

				pair<int, int> aux(j,i);
				cajas.push_back(aux);

			}else if (actual.estado[i][j] == '.' ){

				pair<int, int> aux(j,i);
				metas.push_back(aux);

			}else if(actual.estado[i][j] == '*'){

				valor -= 1000;
			}
		}
	}

	//Distancia entre cajas y metas
	for (int i = 0; i < cajas.size(); i++){

		for (int j = 0; j < metas.size(); j++){

			disHorizontal = cajas[i].first - metas[j].first;
			disVertical = cajas[i].second - metas[j].second;

			disHorizontal = abs(disHorizontal);
			disVertical = abs(disVertical);

			valor += disHorizontal;
			valor += disVertical;
		}

		disHorizontal = cajas[i].first - x;
		disVertical = cajas[i].second - y;

		disHorizontal = abs(disHorizontal);
		disVertical = abs(disVertical);

		if (radioElArroba > (disVertical + disHorizontal)){
			radioElArroba = (disVertical + disHorizontal);
		}
	}

	valor += radioElArroba;

	
	//Distancias entre cajas y deadlocks
	for (int i = 0; i < cajas.size(); i++){

		minDead = abs(deadlocks[0].first - cajas[i].first) + abs(deadlocks[0].second - cajas[i].second);

		for (int j = 1; j < deadlocks.size(); j++){

			sumaDistancias = abs(deadlocks[j].first - cajas[i].first) + abs(deadlocks[j].second - cajas[i].second);

			if(sumaDistancias < minDead){

				minDead = sumaDistancias;

			}

		}

		valor -= minDead;
	}
	

	return valor;
}

//Retorna Nodo con el siguiente estado dependiendo del movimiento a revisar.
Nodo exploracion(const Nodo &actual, int x, int y, char direccion){

	Nodo nuevoNodo;
	nuevoNodo.nulo = true;
	char entidad;
	char destinoCaja;
	vector<vector<char>> estadoSiguiente;

	int ny, nx, cx, cy;
	string d;

	if(direccion == 'N'){

		ny = y-1;
		nx = x;
		cy = y-2;
		cx = x;
		d = "U\n";
	}

	else if(direccion == 'S'){

		ny = y+1;
		nx = x;
		cy = y+2;
		cx = x;
		d = "D\n";
	}

	else if(direccion == 'E'){

		ny = y;
		nx = x+1;
		cy = y;
		cx = x+2;
		d = "R\n";
	}

	else{

		ny = y;
		nx = x-1;
		cy = y;
		cx = x-2;
		d = "L\n";
	}

	entidad = actual.estado[ny][nx];

	switch(entidad){

		case '$':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = '@';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			destinoCaja = estadoSiguiente[cy][cx];

			if (destinoCaja == '#'){
				break;
			}
			else if (destinoCaja == '$'){
				break;
			}
			else if (destinoCaja == '*'){
				break;
			}
			else if (destinoCaja == 'd'){
				break;
			}
			else if (destinoCaja == 'e'){
				break;
			}
			else if (destinoCaja == ' '){
				estadoSiguiente[cy][cx] = '$';
			}
			else if (destinoCaja == '.'){
				estadoSiguiente[cy][cx] = '*';
			}
			else{
				break;
			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

			nuevoNodo.costoTotal += COSTO_MOVIMIENTO;
			nuevoNodo.valorH = heuristica(nuevoNodo);
			nuevoNodo.valorH += nuevoNodo.costoTotal;
			nuevoNodo.estado = estadoSiguiente;
			nuevoNodo.nulo = false;

			return nuevoNodo;

			break;

		case '*':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = '+';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			destinoCaja = estadoSiguiente[cy][cx];

			if (destinoCaja == '#'){
				break;
			}
			else if (destinoCaja == '$'){
				break;
			}
			else if (destinoCaja == '*'){
				break;
			}
			else if (destinoCaja == 'd'){
				break;
			}
			else if (destinoCaja == 'e'){
				break;
			}
			else if (destinoCaja == ' '){
				estadoSiguiente[cy][cx] = '$';
			}
			else if (destinoCaja == '.'){
				estadoSiguiente[cy][cx] = '*';
			}
			else{
				break;
			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

			nuevoNodo.costoTotal += COSTO_MOVIMIENTO;
			nuevoNodo.valorH = heuristica(nuevoNodo);
			nuevoNodo.valorH += nuevoNodo.costoTotal;
			nuevoNodo.estado = estadoSiguiente;
			nuevoNodo.nulo = false;

			return nuevoNodo;

			break;

		case '.':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = '+';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

			nuevoNodo.costoTotal += COSTO_MOVIMIENTO;
			nuevoNodo.valorH = heuristica(nuevoNodo);
			nuevoNodo.valorH += nuevoNodo.costoTotal;
			nuevoNodo.estado = estadoSiguiente;
			nuevoNodo.nulo = false;

			return nuevoNodo;

			break;

		case ' ':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = '@';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

			nuevoNodo.costoTotal += COSTO_MOVIMIENTO;
			nuevoNodo.valorH = heuristica(nuevoNodo);
			nuevoNodo.valorH += nuevoNodo.costoTotal;
			nuevoNodo.estado = estadoSiguiente;
			nuevoNodo.nulo = false;

			return nuevoNodo;

			break;

		case 'e':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = 'E';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

			nuevoNodo.costoTotal += COSTO_MOVIMIENTO;
			nuevoNodo.valorH = heuristica(nuevoNodo);
			nuevoNodo.valorH += nuevoNodo.costoTotal;
			nuevoNodo.estado = estadoSiguiente;
			nuevoNodo.nulo = false;

			return nuevoNodo;

			break;

		case 'd':

			estadoSiguiente = actual.estado;

			estadoSiguiente[ny][nx] = 'D';

			if(actual.estado[y][x] == '@'){

				estadoSiguiente[y][x] = ' ';

			}
			else if(actual.estado[y][x] == '+'){

				estadoSiguiente[y][x] = '.';

			}
			else if(actual.estado[y][x] == 'D'){

				estadoSiguiente[y][x] = 'd';

			}else{

				estadoSiguiente[y][x] = 'e';

			}

			nuevoNodo = actual;
			nuevoNodo.movimientos.append(d);

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

			if(actual.estado[i][j] == '@' || actual.estado[i][j] == '+' || actual.estado[i][j] == 'D' || actual.estado[i][j] == 'E'){

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

//Retorna verdadero o falso dependiendo de si se llego al estado objetivo o no.
bool meta(Nodo &actual){

	//Si encontramos una caja '$' entonces no se ha llegado al estado objetivo
	for(int i = 0; i < actual.estado.size(); i++){

		for(int j = 0; j < actual.estado[i].size(); j++){

			if(actual.estado[i][j] == '$'){

				return false;
			}

		}

	}

	return true;
}

//retorna un string con la secuencia de movimientos de la solucion optima.
string aEstrella(Nodo &estadoI){

	deque<Nodo> porVisitar;
	vector<Nodo> visitados;

	Nodo actual;

	porVisitar.push_back(estadoI);

	while (!porVisitar.empty()){

		actual = porVisitar.front();
		porVisitar.pop_front();
		
		visitados.push_back(actual);
		
		if (meta(actual)){

			return actual.movimientos;
			break;

		}
		
		queue<Nodo> nodosValidos;
		nodosValidos = crearPosiblesFuturos(actual);
		deque<Nodo>::iterator it;
		vector<Nodo>::iterator itr;

		while (!nodosValidos.empty()){

			bool visitado = false;
			bool insertado = false;
			Nodo aux = nodosValidos.front();

			for (it = porVisitar.begin(); it != porVisitar.end(); it++){

				if (it->estado == aux.estado){

					visitado = true;
					break;
				}
			}

			for (itr = visitados.begin(); itr != visitados.end(); itr++){

				if (itr->estado == aux.estado){

					visitado = true;
					break;
				}
			}

			if (!visitado){

				for (it = porVisitar.begin(); it != porVisitar.end(); it++){

					if (it->valorH > aux.valorH){

						porVisitar.insert(it, aux);
						insertado = true;
						break;
					}
				}

				if (!insertado){
					porVisitar.push_back(aux);
				}

			}
			nodosValidos.pop();
		}
	}
	
	return "";
}

//Lee el nivel.
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

//Escribe la solucion a archivo.
void escritura(int numero, string solucion){

	string nombre = "soluciones/";
	nombre.append(to_string(numero) + ".txt");
	
	solucion.append("F\n");
	
	ofstream archivo(nombre);
	
	if (archivo.is_open()){
		
		archivo << solucion;
		archivo.close();
		
		cout << "\nSolución encontrada y guardada en:  " << nombre <<"\n";
	}
	
	else cout << "Error al escribir solución al archivo";
}

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
	
	timeval inicio, fin;
	long segundo, microsegundo;
	vector<vector<char>> level;
	string solucion;
	int numero;
	
	cout << "Ingrese el número del nivel (1-155): ";
	cin >> numero;
	
	if(numero < 1 || numero > 155){
		
		cout << "ERROR en número\n";
		
		return 0;
	}
	
	level = lectura(numero);

	level = esquinar(level);

	level = paredear(level);

	Nodo estadoI;

	estadoI.estado = level;
	estadoI.movimientos = "";
	estadoI.costoTotal = 0;
	estadoI.valorH = 0;
	estadoI.nulo = false;
	
	gettimeofday(&inicio, NULL);
	solucion = aEstrella(estadoI);
	gettimeofday(&fin, NULL);
	
	escritura(numero, solucion);
	
	
	cout << "Tiempo de ejecución: \n";
	segundo = fin.tv_sec - inicio.tv_sec;
	microsegundo = fin.tv_usec - inicio.tv_usec;
	cout << (segundo + (microsegundo/1000000.0))<< " segundos\n";


	return 0;
}
