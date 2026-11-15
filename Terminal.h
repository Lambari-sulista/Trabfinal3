#pragma once 

#include <iostream>
#include <string>

class TerminalUI{
    public:
        //editor de texto
        static constexpr const char* reset = "\033[0m";
        static constexpr const char* negri = "\033[1m";
        static constexpr const char* subli= "\033[4m";


        //cores de texto
        static constexpr const char* red = "\033[31m";
        static constexpr const char* green = "\033[32m";
        static constexpr const char* yellow = "\033[33m";
        static constexpr const char* blue = "\033[34m";
        static constexpr const char* white = "\033[37m";
    

        //Cores de fundo
        static constexpr const char* bk_black = "\033[40m";
        static constexpr const char* bk_white = "\033[47m";

        //Fase de jogo
        static void Limpar(){
            std::cout << "\033[2J\033[1;1H";
        }   
        static void pausar() {
    std::cout << "\nPressione ENTER para continuar..." << std::flush;

    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::string dummy;
    std::getline(std::cin, dummy);
    }
        

};

