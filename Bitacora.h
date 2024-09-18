#ifndef BITACORA_H
#define BITACORA_H
#include <iostream>

using namespace std;

class Bitacora{
    private:
        int mes;
        string mesS;
        int dia;
        string hora;
        string IP;
        string razon;

    public:
        Bitacora();
        Bitacora(int mes,string mesS,int dia,string hora,string IP,string razon);

        //gets
        string getMesS();
        int getDia();
        string getHora();
        string getIP();
        string getRazon();
        int getMes();

        bool operator<(Bitacora val);

        virtual ~Bitacora();

};

#endif 
