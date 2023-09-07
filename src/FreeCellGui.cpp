#include "../include/FreeCellGui.h"
#include <iostream>

void FreeCellGui::imprimeCartas(Carta* cartas) {
    CLEAR_ALL;
    this->imprimeCabecalho(cartas);
    this->imprimeColunas(cartas);
}

void FreeCellGui::imprimeCabecalho(Carta* cartas) {
    // TODO: Implement me :)
}

void FreeCellGui::imprimeColunas(Carta* cartas) {
    for(int linha = 0; linha <= maiorColuna(cartas); linha++){
        for(int coluna = 1; coluna <= 8; coluna++){
            int posicaoCarta = buscaCarta(cartas, linha, coluna);
            std::cout << (posicaoCarta != COLUNA_VAZIA ? cartas[posicaoCarta].toString() : CARTA_VAZIA);
        }
        std::cout << std::endl;        
    }
    std::cout << "    1       2       3       4       5       6       7       8" << std::endl;
    std::cout << std::endl;
}

unsigned short int FreeCellGui::leColunaInicial(const Estrutura& estrutura,
        bool limpaErroPrimeiraLeitura) {
    const std::string mensagemLeitura = "Entre o valor da coluna inicial: ";
    unsigned short int colunaInicial;
    bool colunaValida = false;
    while (!colunaValida) {
        colunaInicial = this->leColuna(mensagemLeitura);
        if (limpaErroPrimeiraLeitura)
            CLEAR_LINE;
        this->trataErrosLeituraColunaInicial(colunaInicial, estrutura, colunaValida);
    }
    this->exibeEntrada("Coluna incial: ", colunaInicial);
    return colunaInicial;
}

void FreeCellGui::trataErrosLeituraColunaInicial(const unsigned short int colunaInicial, 
        const Estrutura& estrutura, bool& colunaValida) {
    if (colunaInicial == 0)
        this->trataLinhaErro("Não pode mover carta da saída, tente novamente. ");
    else if (estrutura.encontraUltimaCartaDaColuna(colunaInicial) == COLUNA_VAZIA)
        this->trataLinhaErro("Não pode movar de uma coluna vazia, tente novamente. ");
    else
        colunaValida = true;
}

unsigned short int FreeCellGui::leColunaFinal(unsigned short int colunaInicial) {
    const std::string mensagemLeitura = "Entre o valor da coluna final: ";
    unsigned short int colunaFinal;
    bool colunaValida = false;
    while (!colunaValida) {
        colunaFinal = this->leColuna(mensagemLeitura);
        colunaValida = colunaFinal != colunaInicial;
        if (!colunaValida)
            this->trataLinhaErro("Não pode mover a carta para a mesma coluna, tente novamente. ");
    }
    this->exibeEntrada("Coluna final: ", colunaFinal);
    return colunaFinal;
}

unsigned short int FreeCellGui::leColuna(const std::string mensagemLeitura) {
    std::string coluna;
    const std::string mensagemErro = "Coluna invalida, tente novamente. ";
    bool colunaValida = false;
    while(!colunaValida) {
        std::cout << mensagemLeitura;
        std::getline(std::cin, coluna);
        colunaValida = !coluna.empty() && this->somenteNumeros(coluna) &&
            std::stoi(coluna) >=0 && std::stoi(coluna) <= 12;
        if (!colunaValida)
            this->trataLinhaErro(mensagemErro);
    }
    return std::stoi(coluna);
}

bool FreeCellGui::somenteNumeros(std::string colunaString) {
    for (int i = 0; i < colunaString.length(); i++)
        if(!isdigit(colunaString[i]))
            return false;
    return true;
}


void FreeCellGui::trataLinhaErro(const std::string mensagemErro) {
    CLEAR_LINE;
    std::cout << mensagemErro;
}

void FreeCellGui::exibeEntrada(const std::string mensagemExibicao, const unsigned short int coluna) {
    CLEAR_LINE;
    std::cout << mensagemExibicao << coluna << std::endl;
}

int FreeCellGui::buscaCarta(Carta* cartas, int pos, int col){
    int p = 0;
    for (int i = 0; i < TAMANHO_BARALHO; i++) {
        if (cartas[i].getColuna() == col) {
            if(p == pos)
                return i;
            else
                p++;    
        }
    }
    return COLUNA_VAZIA;
}

int FreeCellGui::maiorColuna(Carta* cartas){
    int maiorColl = 0;
    for(int coluna = 1; coluna <= 8; coluna++){
        int countColl = 0;
        for(int i = TAMANHO_BARALHO-1; i >= 0; i--){
            if(cartas[i].getColuna() == coluna)
                countColl++;
        }
        if(countColl > maiorColl)
            maiorColl = countColl;
    }
    return maiorColl;
}

// ? Validar se será usado em outros pontos do código
void FreeCellGui::imprimeCarta(Carta* cartas, int i){
    std::cout << cartas[i].toString();
}

// ? Validar leitura via arquivo de texto
void FreeCellGui::imprimeRegras(){
    std::cout << "O jogador fará quantos movimentos quiser, entre as pilhas que quiser, respeitando as seguintes regras: " << std::endl
              << "Para uma free cell desocupada: qualquer carta do topo de uma pilha de jogo; " << std::endl
              << "Para uma das pilhas de saída: qualquer carta de uma free cell ou do topo de uma pilha de jogo. Movimentos para uma pilha de saída " << std::endl
              << "devem ser feitos em ordem do menor para o maior, sempre de mesmo naipe. Assim, temos uma pilha de saída para cada um dos 4 " << std::endl
              << "naipes. Ases sempre podem ser movidos para uma pilha de saída vazia; " << std::endl
              << "Para o topo de uma pilha de jogo: qualquer carta de uma das free cells ou do topo de uma outra pilha de jogo. Movimentos para uma " << std::endl
              << "pilha de jogo devem ser feitos em ordem do maior para o menor, alternando a cor do naipe. Por exemplo: se o topo de uma pilha de " << std::endl
              << "jogo contém um 4 de paus (que é preto), podemos mover para o topo dessa pilha um 3 de copas ou de ouro (que são vermelhos). " << std::endl
              << "O fim do jogo é alcançado quando todas as cartas forem movidas para as pilhas de saída ou quando não há movimento que permita mais alguma " << std::endl
              << "carta ser movida para uma das pilhas de saída." << std::endl;
    std::cout << std::endl;
}

void FreeCellGui::trataMovimentacaoProibida(std::string mensagemErro) const {
    CLEAR_LINE;
    CLEAR_LINE;
    std::cout << mensagemErro << std::endl;
}