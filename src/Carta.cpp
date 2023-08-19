#include "../include/Carta.h"
#include <iostream>

Carta::Carta(Simbolo::Valor valor, Simbolo::Naipe naipe):
    valor(valor),
    naipe(naipe)
{}

void Carta::imprimeCarta() const {
    std::cout << "[ " <<
        static_cast<int>(this->valor) <<
        static_cast<char>(this->naipe) << 
        " ]" << std::endl;
}