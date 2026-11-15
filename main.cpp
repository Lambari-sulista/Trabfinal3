#include <iostream>
#include <limits>
#include "Terminal.h"
#include "main.h"

int main() {
    acao  player;
    int opcao = -1;
     while(opcao != 0){
        TerminalUI::Limpar();

            std::cout<< TerminalUI::green << "acao 1: ir para a balada" << TerminalUI::reset << std::endl;
            std::cout<< TerminalUI::green << "acaoo 0: dormir" << TerminalUI::reset << std::endl;

            std::cin >> opcao;

        switch(opcao){
            case 1:
            player.acao_HH();
            TerminalUI::pausar();
            break;
            
            case 0:
            opcao = 0;
            break;
            }
        }

    return 0;
}