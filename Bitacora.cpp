#include "Bitacora.h"
#include <iostream>

Bitacora::Bitacora(){
    mes=0;
    mesS=" ";
    dia=0;
    hora=" ";
    IP=" ";
    razon=" ";

}

Bitacora::Bitacora(int mes,string mesS,int dia,string hora,string IP,string razon):Bitacora(){
    this->mes=mes;
    this->mesS=mesS;
    this->dia=dia;
    this->hora=hora;
    this->IP=IP;
    this->razon=razon;
}

string Bitacora::getMesS(){
    return mesS;
}

int Bitacora::getDia(){
    return dia;
}

string Bitacora::getHora(){
    return hora;
}

string Bitacora::getIP(){
    return IP;
}

string Bitacora::getRazon(){
    return razon;
}

int Bitacora::getMes(){
    return mes;
}

bool Bitacora::operator<(Bitacora val){
    //b1<b2 -> op(b2)

    if (mes==val.mes){
        if (dia<val.dia){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (mes<val.mes){
            return true;
        }
        else{
            return false;
        }
    }
}

Bitacora::~Bitacora(){
    //dtor
}
