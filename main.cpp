#include <iostream>
#include <limits>
#include "Terminal.h"
#include "main.h"







int main() {
    jogador jogador("henrique");
    jogador.getNome();
    jogador.getEnergia();

    std::cout<< TerminalUI::negri << jogador << std::endl;


    return 0;
}