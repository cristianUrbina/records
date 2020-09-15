#include<bits/stdc++.h>
#define BITACORA "bitacora.txt"
using namespace std;

//Pondera el valor del mes
//Entrada: Una cadena con el mes abreviado
//Salida: Valor asociado al mes
// O(1)
int ponderadorMeses(const string &mes){
	if(mes=="Jun")return 1;	
	else if(mes=="Jul") return 2;
	else if(mes=="Aug") return 3;
	else if(mes=="Sep") return 4;
	else return 5;
}

//Realiza el trabajo del operador "<" para los vectores que contienen la fecha
//Entrada: 2 fechas
//Salida si fecha1<fecha2 regresa true, de otro modo false
//O(1)
bool comparadorFechasMenorQue(vector<string>&fecha1,vector<string>&fecha2){
	if(ponderadorMeses(fecha1[0])<ponderadorMeses(fecha2[0]))return true;
	if(ponderadorMeses(fecha1[0])==ponderadorMeses(fecha2[0])){
		if(atoi(fecha1[1].c_str())<atoi(fecha2[1].c_str()))return true;
		if(fecha1[1]==fecha2[1]){
			if(fecha1[2]<fecha2[2])return true;
		}
	}
	return false;
}
//Realiza el trabajo del operador "==" para los vectores que contienen la fecha
//Entrada: 2 fechas
//Salida si fecha1==fecha2 regresa true, de otro modo false
//O(1)
bool comparadorFechasEq(vector<string>&fecha1,vector<string>&fecha2){
	if(ponderadorMeses(fecha1[0])==ponderadorMeses(fecha2[0])&& atoi(fecha1[1].c_str())==atoi(fecha2[1].c_str()) && fecha1[2]==fecha2[2])return true;
	return false;
}

//Hace el último paso después de ordenar por mergesort recursivamente
// Parámetros:
// array: vector de datos a ordenar
// l: limite izquierdo
// m: punto medio
// r: limite derecho
// Valor de retorno: no hay
// Big Omega: Omega(n) El mejor caso es cuando el vector ya está ordenado así que solo se ejecutan n/2 + 1 pasos,
// pues la otra mitad de los datos se inserta de golpe
// Big Theta: Theta(n)
// Big O: O(n) el peor caso es cuando el vector está intercalado y se tienen que insertar un dato de un subconjunto y otro del otro
// donde se deben de hacer n pasos
void merge(vector<vector<string>>&array, const int &l, const int &m, const int &r) {
   int i, j, k, nl, nr,aux;
   nl = m-l+1; nr = r-m; 
   vector<vector<string>> larr, rarr;
   vector<string> v;
   for(int i = 0;i<4;i++) v.push_back("");
   aux=nl;
   while(aux--){
   		larr.push_back(v);
   }
   aux=nr;
   while(aux--){
   		rarr.push_back(v);
   }
   for(i = 0; i<nl; i++)
      larr[i] = array[l+i];
   for(j = 0; j<nr; j++)
      rarr[j] = array[m+1+j];
   i = 0; j = 0; k = l;
   while(i < nl && j<nr) {
      if(comparadorFechasMenorQue(larr[i],rarr[j])){
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {      
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     
      array[k] = rarr[j];
      j++; k++;
   }
}

//Ordena recursivamente con mergeSort
// Parámetros:
// array: vector de datos a ordenar
// p: limite izquierdo
// r: limite derecho
// Valor de retorno: no hay
// Big Omega: Omega(n lg(n)) El mejor caso es cuando el vector ya está ordenado así que solo se ejecutan n/2 + 1 pasos,
// pues la otra mitad de los datos se inserta de golpe, pero aún así se dividen en dos el número de elementos 
// Big Theta: Theta(n lg(n))
// Big O: O(n lg(n)) el peor caso es cuando el vector está intercalado y se tienen que insertar un dato de un subconjunto y otro del otro
// donde se deben de hacer n pasos, pero aún así se dividen en dos el número de elementos
void ordenaMerge(vector<vector<string>>&array,const int&p,const int&r){
	if(p<r){
		int q=(p+r)/2;
		ordenaMerge(array,p,q);
		ordenaMerge(array,q+1,r);
		merge(array,p,q,r);
	}
}

// Realiza una búsqueda binaria
// Parámetros:
// array: vector de datos donde buscar
// fecha: dato a buscar
// Salida:
// k: índice de donde se encuentra el valor x (retorna -1 si no lo encuentra)
// Big Omega: Omega(1) El mejor caso es cuando el elemento que buscamos se 
// encuentra justo en índice central, tomando solo una iteración para encontrarlo.
// Big Theta: Theta() El caso promedio es cuando se encuentra en un indice aproximadamente 
// en 1/4 o 3/4 del tamaño del arreglo. Partiendo del razonamiento de Big O(lg n) tenemos que 
// en promedio se realizarán (lg n)/2 pasos. Entonces Theta(lg n)
// Big O: O(lg n) el peor caso es cuando el elemento no se encuentra en el arreglo, pero cada iteración
// divide a la mitad el rango en donde se ha de buscar, por eso ha de tener una complejidad de O(lg n)
int busqBinaria(vector<vector<string>>&array, vector<string>&fecha){
	int inf = 0;
	int sup = array.size()-1;
	while(inf<sup){
		float k = float(inf+sup)/2;
		if(comparadorFechasEq(array[k],fecha)) return k;
		else if(comparadorFechasMenorQue(array.at((int)k),fecha)) inf=ceil(k);
		else sup = floor(k);
	}
	return -1;
}

//La siguiente función se encarga de leer la bitácora y almacenarla en un vector 
//de cadenas de caractéres.
// entrada:
// bitacora: vector donde almacenar los registros
// O(n)
void leerBitacora(vector<vector<string>>&bitacora){
	ifstream archivoBitacora;
	archivoBitacora.open(BITACORA,ios::in);
	string linea, mes, dia, hora;
	vector<string>aux;
	while(!archivoBitacora.eof()){
		aux.clear();
		mes = dia = hora="";
		archivoBitacora>>mes;
		archivoBitacora>>dia;
		archivoBitacora>>hora;
		aux.push_back(mes);
		aux.push_back(dia);
		aux.push_back(hora);
		getline(archivoBitacora,linea);
		aux.push_back(linea);
		bitacora.push_back(aux);
	}
	archivoBitacora.close();
}

//Se encarga de pedir las fechas inicio y fin
//Entrada:
// inicio: fecha inicial
// fin: fecha final
void pedirFechas(vector<string>& inicio, vector<string>& fin){
	string linea, mes, dia, hora;
	cout<<"Ingrese la la fecha de inicio: (Ejemplo Jun 17 22:26:54)\n";
	cin>>mes;
	cin>>dia;
	cin>>hora;
	inicio.push_back(mes);
	inicio.push_back(dia);
	inicio.push_back(hora);

	cout<<"Ingrese la la fecha final: (Ejemplo Oct 9 10:32:24) \n";
	cin>>mes;
	cin>>dia;
	cin>>hora;
	fin.push_back(mes);
	fin.push_back(dia);
	fin.push_back(hora);
}

// Llena el reporte con la información solicitada
//Entrada:
// bitacora: vector ordenado de la bitacora
// inicio: fecha inicial
// fin: fecha final
void generarReporte(const vector<vector<string>>&bitacora, const int &inicio, const int &fin){
	ofstream reporte("reporte.txt",ios::out);
	for(int x=inicio;x<=fin;x++) {
		for(int j=0;j<4;j++){
			reporte<<bitacora.at(x)[j]<<" ";
		}
		reporte<<"\n";
	}
}

int main(){
	vector<vector<string>>bitacora;
	leerBitacora(bitacora);
	ordenaMerge(bitacora,0,bitacora.size()-1);
	vector<string>fechaInicio, fechaFin;
	pedirFechas(fechaInicio, fechaFin);
	
	int inicio = busqBinaria(bitacora,fechaInicio);
	int fin = busqBinaria(bitacora,fechaFin);
	
	generarReporte(bitacora,inicio,fin);
	for(int x=inicio;x<=fin;x++) {
		for(int j=0;j<4;j++){
			cout<<bitacora.at(x)[j]<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}
