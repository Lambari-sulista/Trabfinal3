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
        static constexpr const char* blue = "\033[34m";
        static constexpr const char* white = "\033[37m";
    

        //Cores de fundo
        static constexpr const char* bk_black = "\033[40m";
        static constexpr const char* bk_white = "\033[47m";
        
};

