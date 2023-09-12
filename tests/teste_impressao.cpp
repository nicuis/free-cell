#include "../include/Baralho.h"
#include "../include/Estrutura.h"
#include "../include/FreeCellGui.h"

int main() {
    Baralho baralho;
    baralho.embaralhar();
    Mesa estrutura(baralho.getCartas());
    FreeCellGui freeCellGui;
    freeCellGui.imprimeCartas(estrutura.getCartas());
}