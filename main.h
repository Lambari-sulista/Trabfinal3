#include<iostream>
#include<vector>
#include"Terminal.h"

#pragma once 


class acao : public TerminalUI {
    public:
    float x;

    void acao_dormir(){ 
    }
    void acao_estudar(){ 
    }
    void acao_RU(){ 
    }
    void acao_HH(){ 
        std::cout << this->red << this->negri << this ->subli << this->bk_white << "10 reais na marques"  << this->reset << std::endl;
    }
};

class barra_energia {};
class jogador {};
class No_historia {};