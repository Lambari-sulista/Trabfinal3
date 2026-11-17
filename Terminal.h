#pragma once

#include <iostream>
#include <string>

struct impacto {
    int energia = 0;
    float nota = 0.0f;
};

class TerminalUI {
public:
    // Editor de texto (ANSI Escape Codes padrão POSIX/ISO)
    static constexpr const char* reset = "\033[0m";
    static constexpr const char* negri = "\033[1m";
    static constexpr const char* subli = "\033[4m";

    // Cores de texto
    static constexpr const char* red    = "\033[31m";
    static constexpr const char* green  = "\033[32m";
    static constexpr const char* yellow = "\033[33m";
    static constexpr const char* blue   = "\033[34m";
    static constexpr const char* white  = "\033[37m";

    // Cores de fundo
    static constexpr const char* bk_black = "\033[40m";
    static constexpr const char* bk_white = "\033[47m";

    // Limpa a tela usando apenas sequências ANSI padrão (funciona nativamente em Linux, macOS e VS Code)
    static void Limpar() {
        std::cout << "\033[2J\033[3J\033[1;1H" << std::flush;
    }

    static void pausar() {
        std::cout << "\n" << yellow << ">> Pressione ENTER para continuar..." << reset << std::flush;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    static std::string barraProgresso(int valor, int max = 100) {
        int blocos = (valor * 10) / max;
        const char* cor = (valor > 60) ? green : (valor > 30 ? yellow : red);

        std::string barra = std::string(cor) + "[";
        for (int i = 0; i < 10; ++i) {
            barra += (i < blocos) ? "#" : "-";
        }
        barra += "] " + std::to_string(valor) + "%" + reset;
        return barra;
    }

    // Imprime o extrato colorido do impacto de cada ação
    static void exibirDeltaImpacto(const impacto& imp) {
        auto formatar = [](const std::string& nome, float val, const std::string& suf = "") {
            if (val == 0) return;
            const char* cor = (val > 0) ? green : red;
            std::cout << cor << "  " << (val > 0 ? "[+]" : "[-]") << " "
                      << nome << ": " << (val > 0 ? "+" : "") << val << suf << reset << "\n";
        };

        formatar("Energia", static_cast<float>(imp.energia), "%");
        formatar("Nota", imp.nota, " pts");
    }
};