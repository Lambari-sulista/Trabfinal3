#include "NoEvento.h"
#include "Terminal.h"
#include "main.h"
#include <iostream>
#include <limits>

NoEvento::NoEvento(std::string tit, std::string desc) : titulo(tit), descricao(desc) {}

// Inclui textoResultado para alimentar o feedback visual (atualize a assinatura no NoEvento.h também!)
void NoEvento::addOpcao(std::string texto, std::string resultado, impacto imp, NoEvento* destino) {
    opcoes.push_back({texto, resultado, imp, destino});
}

size_t NoEvento::LerEscolha() const {
    std::string entrada;
    while (true) {
        std::cout << "\nSua decisao (1-" << opcoes.size() << "): " << std::flush;
        std::getline(std::cin, entrada);
        try {
            size_t escolha = std::stoul(entrada);
            if (escolha >= 1 && escolha <= opcoes.size()) {
                return escolha - 1;
            }
        } catch (...) {
            // Ignora erro caso o usuário digite letras ou aperte Enter vazio
        }
        std::cout << TerminalUI::red << "Opcao invalida! Digite um numero valido." << TerminalUI::reset << "\n";
    }
}

// --- NoDecisao ---
NoDecisao::NoDecisao(std::string tit, std::string desc) : NoEvento(tit, desc) {}

NoEvento* NoDecisao::exe(jogador& j) const {
    std::cout << TerminalUI::negri << TerminalUI::yellow << "\n[ " << titulo << " ]\n" << TerminalUI::reset;
    std::cout << descricao << "\n\n";
    
    for (size_t i = 0; i < opcoes.size(); ++i) {
        std::cout << TerminalUI::green << "[" << (i + 1) << "] " << TerminalUI::reset
                  << opcoes[i].texto << "\n";
    }

    size_t idx = LerEscolha();
    const Opcao& escolhida = opcoes[idx];

    j += escolhida.consequencia;
    j.registroDecisao(titulo + " -> " + escolhida.texto);

    // Exibe o feedback claro antes de mudar de tela
    std::cout << "\n" << TerminalUI::negri << "--- RESULTADO DA SUA ESCOLHA ---\n" << TerminalUI::reset;
    std::cout << escolhida.textoResultado << "\n\n";
    TerminalUI::exibirDeltaImpacto(escolhida.consequencia);

    return escolhida.proximoNo;
}

// --- NoImprevisto ---
NoImprevisto::NoImprevisto(std::string tit, std::string desc, std::string imprevisto, impacto imp)
    : NoEvento(tit, desc), textoImprevisto(imprevisto), impactoImp(imp) {}

NoEvento* NoImprevisto::exe(jogador& j) const {
    std::cout << TerminalUI::negri << TerminalUI::red << "\n[ IMPREVISTO: " << titulo << " ]\n" << TerminalUI::reset;
    std::cout << textoImprevisto << "\n";
    TerminalUI::exibirDeltaImpacto(impactoImp); // Mostra o impacto do imprevisto na hora!
    j += impactoImp;

    std::cout << "\n" << descricao << "\n\n";
    for (size_t i = 0; i < opcoes.size(); ++i) {
        std::cout << TerminalUI::green << "[" << (i + 1) << "] " << TerminalUI::reset
                  << opcoes[i].texto << "\n";
    }

    size_t idx = LerEscolha();
    const Opcao& escolhida = opcoes[idx];

    j += escolhida.consequencia;
    j.registroDecisao(titulo + " -> " + escolhida.texto);

    std::cout << "\n" << TerminalUI::negri << "--- RESULTADO DA SUA ESCOLHA ---\n" << TerminalUI::reset;
    std::cout << escolhida.textoResultado << "\n\n";
    TerminalUI::exibirDeltaImpacto(escolhida.consequencia);

    return escolhida.proximoNo;
}

// --- NoFinal ---
NoFinal::NoFinal(std::string tit, std::string desc)
    : NoEvento(tit, desc) {}

NoEvento* NoFinal::exe(jogador& j) const {
    std::cout << TerminalUI::negri << TerminalUI::blue << "\n=== " << titulo << " ===\n" << TerminalUI::reset;
    std::cout << descricao << "\n";

    // Polimorfismo dinâmico: avalia e exibe uma das 3 categorias
    classificacao* resultado = classificacao::avaliarcaoJ(j);
    resultado->resultado(j);
    delete resultado;

    // Mostra o histórico de escolhas do jogador
    std::cout << "\n" << TerminalUI::negri << "--- Resumo da sua trajetoria ---\n" << TerminalUI::reset;
    for (const auto& passo : j.getHistorico().obterTodos()) {
        std::cout << " * " << passo << "\n";
    }

    TerminalUI::pausar(); // Garante que o jogador leia o diploma e o histórico antes de fechar!
    return nullptr;
}