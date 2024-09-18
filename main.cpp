#include <iostream>
#include <vector>
#include <fstream>
#include "Bitacora.h"
#include <unordered_map>

using namespace std;

void leer(vector<Bitacora>& datos);
int mesANum(string mesTemp);
void archivoOrdenado(vector<Bitacora>& datos);

void swapD(int i, int j, vector<Bitacora>& vec);
void ordenaInsercion(vector<Bitacora>& vec);
int busqBinaria(vector<Bitacora>& vec, int mes, int dia);

int busqBinaria(vector<Bitacora>& vec, int mes, int dia){
    int inicio = 0;
    int fin = vec.size() - 1;
    while (inicio <= fin){
        int medio = inicio + (fin - inicio) / 2;

        if (vec[medio].getMes() == mes){
            if (vec[medio].getDia() == dia){
                return medio;
            }
            else if (vec[medio].getDia() < dia){
                inicio = medio + 1;
            }
            else{
                fin = medio - 1;
            }
        } 
        else if (vec[medio].getMes() < mes){
            inicio = medio + 1;
        } 
        else{
            fin = medio - 1;
        }
    }
    return -1;
}

void leer(vector<Bitacora>& datos){
    ifstream archivo;
    string mesTemp;
    int mes;
    int dia;
    string hora;
    string IP;
    string razon;

    archivo.open("bitacora-1.txt",ios::in);
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
        exit(1);
    }

    for (int i=0;i<16807;i++){
        archivo >> mesTemp >> dia >> hora >> IP;
        getline(archivo, razon);
        razon = razon.substr(1);
        mes = mesANum(mesTemp);
        Bitacora dato(mes, mesTemp, dia, hora, IP, razon);
        datos.push_back(dato);
    }
}

int mesANum(string mesTemp){
    unordered_map<string,int> meses={
    {"Jan",1}, {"Feb",2}, {"Mar",3}, {"Apr",4}, {"May",5}, {"Jun",6}, {"Jul",7}, {"Aug",8}, {"Sep",9}, {"Oct",10}, {"Nov",11}, {"Dec",12}
    };

    return meses[mesTemp];
}

void swapD(int i, int j, vector<Bitacora>& vec){

    Bitacora aux=vec[i];
    vec[i]=vec[j];
    vec[j]=aux;
}

void ordenaInsercion(vector<Bitacora>& vec){

    int sizeV=vec.size();

    for (int i=1;i<sizeV;i++){
        for (int j=i-1;j>=0;j--){
            if (vec[j+1]<vec[j]){
                swapD(j+1,j,vec);
            }
            else{
                break;
            }
        }
    }
}

void archivoOrdenado(vector<Bitacora>& datos){
    ofstream archivo;
    int sizeV;

    archivo.open("bitacoraOrdenada1.3-eq3.txt",ios::out);
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
                exit(1);
    }

    sizeV=datos.size();

    for(int i=0;i<sizeV;i++){
        archivo<<datos[i].getMesS()<<" "<<datos[i].getDia()<<" "<<datos[i].getHora()<<" "<<datos[i].getIP()<<" "<<datos[i].getRazon()<<endl;
    }
    archivo.close();
}

int main(){
    vector<Bitacora> datos;
    string fechaInicio, fechaFin;
    static int contador=1;

    cout << "Leyendo datos." << endl;
    leer(datos);
    cout << "Ordenando datos." << endl;
    ordenaInsercion(datos);
    cout << "Creando archivo ordenado." << endl;
    archivoOrdenado(datos);
    cout << "Archivo ordenado listo." << endl;

    cout << "Ingrese la fecha de inicio (MMM DD): ";
    getline(cin, fechaInicio);
    cout << "Ingrese la fecha de fin (MMM DD): ";
    getline(cin, fechaFin);

    int mesInicio = mesANum(fechaInicio.substr(0, 3));
    int diaInicio = stoi(fechaInicio.substr(4));
    int mesFin = mesANum(fechaFin.substr(0, 3));
    int diaFin = stoi(fechaFin.substr(4));

    cout << "Buscando registros entre " << fechaInicio << " y " << fechaFin << "." << endl;

    string nombreArchivo = "salida" + to_string(contador) + "-eq3.txt";
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida){
        cout << "No se pudo crear el archivo de salida." << endl;
        return 1;
    }

    for (size_t i = 0; i < datos.size(); i++){
        Bitacora entry = datos[i];
        int mes = entry.getMes();
        int dia = entry.getDia();

        if ((mes > mesInicio || (mes == mesInicio && dia >= diaInicio)) &&
            (mes < mesFin || (mes == mesFin && dia <= diaFin))){
            archivoSalida << entry.getMesS() << " " << entry.getDia() << " " << entry.getHora() << " "
                          << entry.getIP() << " " << entry.getRazon() << endl;
        }
    }

    archivoSalida.close();
    cout << "Registros guardados en el archivo " << nombreArchivo << endl;

    contador++;

    return 0;
}