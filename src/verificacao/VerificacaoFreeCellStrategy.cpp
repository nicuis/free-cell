/**
 * @file VerificacaoFreeCellStrategy.cpp
 * 
 * @author Carlos Sérgio Fernandes Júnior - 2157633 <carlos_fernandes.1@hotmail.com>
 * @author Matheus Paulino Ribeiro - 2143432 <mathpaulinor@gmail.com>
 * @author Nicolas Fagundes Scarpa - 2093087 <bkscarpa@gmail.com>
 * 
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/verificacao/VerificacaoFreeCellStrategy.h"

bool VerificacaoFreeCellStrategy::podeMovimentar(unsigned short int colunaInicial __attribute__((unused)),
        unsigned short int colunaFinal, const Mesa& mesa){

    return mesa.encontraUltimaCartaDaColuna(colunaFinal) == COLUNA_VAZIA;
}

std::string VerificacaoFreeCellStrategy::getMensagemErro() const {
    return this->mensagemErro;
}