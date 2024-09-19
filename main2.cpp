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
void quickSort(vector<Bitacora>& vec);
void quickSort(int ini, int fin, vector<Bitacora>& vec);
int particion(int ini, int fin, vector<Bitacora>& vec);
int busqBinaria(vector<Bitacora>& vec, int mes, int dia);

int main()
{
    vector<Bitacora> datos;
    string fechaInicio, fechaFin;
    static int contador=1;
    int repetir;

    cout << "Leyendo datos." << endl;
    leer(datos);
    cout << "Ordenando datos." << endl;
    quickSort(datos);
    cout << "Creando archivo ordenado." << endl;
    archivoOrdenado(datos);
    cout << "Archivo ordenado listo." << endl;

    repetir=1;

    while (repetir == 1) {
        cout << "\nIngrese la fecha de inicio (MMM DD): ";
        getline(cin, fechaInicio);
        cout << "Ingrese la fecha de fin (MMM DD): ";
        getline(cin, fechaFin);

        cout<<"Mes inicio: "<<mesANum(fechaInicio.substr(0, 3))<<endl;
        int mesInicio = mesANum(fechaInicio.substr(0, 3));
        cout<<"Dia inicio: "<<stoi(fechaInicio.substr(4))<<endl;
        int diaInicio = stoi(fechaInicio.substr(4));
        cout<<"Mes fin: "<<mesANum(fechaFin.substr(0, 3))<<endl;
        int mesFin = mesANum(fechaFin.substr(0, 3));
        cout<<"Dia fin: "<<stoi(fechaFin.substr(4))<<endl;
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

        repetir = 3;

        while (repetir != 1 && repetir != 0) {
            cout << "\nRealizar otra busqueda?\n<0> No\n<1> Si"<<endl;
            cin >> repetir;
            cin.ignore();
        }
        contador++;
    }

    return 0;
}

void leer(vector<Bitacora>& datos)
{
    ifstream archivo;
    string mesTemp;
    int mes;
    int dia;
    string hora;
    string IP;
    string razon;

    archivo.open("bitacora-1.txt",ios::in); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
        exit(1);
    }

    //while(!archivo.eof()){
    for (int i=0;i<16807;i++) { //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        archivo >> mesTemp >> dia >> hora >> IP;
        getline(archivo, razon);
        razon = razon.substr(1);
        mes = mesANum(mesTemp);
        Bitacora dato(mes, mesTemp, dia, hora, IP, razon);
        datos.push_back(dato);
    }
}

int mesANum(string mesTemp)
{
    unordered_map<string,int> meses={
    {"Jan",1}, {"Feb",2}, {"Mar",3}, {"Apr",4}, {"May",5}, {"Jun",6}, {"Jul",7}, {"Aug",8}, {"Sep",9}, {"Oct",10}, {"Nov",11}, {"Dec",12}
    };

    return meses[mesTemp];
}

void swapD(int i, int j, vector<Bitacora>& vec) {

    Bitacora aux=vec[i];
    vec[i]=vec[j];
    vec[j]=aux;
}

int particion(int ini, int fin, vector<Bitacora>& vec)
{
    int pivote=ini;
    int i=ini+1;

    for (int j=i;j<=fin;j++) {
        if (vec[j]<vec[pivote]) {
            swapD(i,j,vec);
            i+=1;
        }
    }

    swapD(ini,i-1,vec);

    return i-1;
}

void quickSort(vector<Bitacora>& vec)
{
    int sizeV=vec.size();
    quickSort(0,sizeV-1,vec);
}

void quickSort(int ini, int fin, vector<Bitacora>& vec)
{
    if (ini<fin) {
        int posPivote=particion(ini,fin,vec);
        quickSort(ini,posPivote-1,vec);
        quickSort(posPivote+1,fin,vec);
    }
}

void archivoOrdenado(vector<Bitacora>& datos)
{
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
