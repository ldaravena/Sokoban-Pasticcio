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
	int valor = 0;
	int radioElArroba = 1000;

	int disHorizontal;
	int disVertical;

	for(int i = 0; i < actual.estado.size(); i++){

		for(int j = 0; j < actual.estado[i].size(); j++){

			if (actual.estado[i][j] == '@'){

				x = j;
				y = i;

			}else if (actual.estado[i][j] == '+' ){

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
	return valor;
}

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

//Retorna verdadero o falso dependiendo de si se llego al estado objetivo o no.
bool meta(Nodo &actual){

	//Si encontramos un '.' o '+' entonces no se ha llegado al estado objetivo
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
