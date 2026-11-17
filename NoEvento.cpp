#include "NoEvento.h"
#include "Terminal.h"
#include "main.h"
#include <iostream>
#include <limits>

NoEvento::NoEvento(std::string tit, std::string desc) : titulo(tit), descricao(desc) {}
NoEvento::~NoEvento() = default;
NoEvento::NoEvento(const NoEvento& outro) : titulo(outro.titulo), descricao(outro.descricao), opcoes(outro.opcoes) {}
NoEvento& NoEvento::operator=(const NoEvento& outro) {
    if (this != &outro) {
        titulo = outro.titulo;
        descricao = outro.descricao;
        opcoes = outro.opcoes;
    }
    return *this;
}
// Inclui textoResultado para alimentar o feedback visual (atualize a assinatura no NoEvento.h também)
void NoEvento::addOpcao(std::string texto, std::string resultado, impacto imp, NoEvento* destino) {
    opcoes.push_back({texto, resultado, imp, destino});
}

size_t NoEvento::LerEscolha() const {
    std::string entrada;
    while (true) {
        std::cout << "\nSua decisao (1-" << opcoes.size() << "): " << std::flush;
        std::getline(std::cin, entrada);
        try {

            if (entrada == "67") {
                return 67; 
            }

            size_t escolha = std::stoul(entrada);
            if (escolha >= 1 && escolha <= opcoes.size()) {
                return escolha - 1; // -1 para ajustar ao índice do vetor 
            }
        } catch (...) {
            // Ignora erro caso o usuário digite letras ou aperte Enter vazio
        }
        std::cout << TerminalUI::red << "Opcao invalida! Digite um numero valido." << TerminalUI::reset << "\n";
    }
}

void NoEvento::executarEasterEgg(jogador& j) const {
    j.registroDecisao(titulo + " -> [CODIGO SECRETO 67 ATIVADO]");
    TerminalUI::Limpar();
    std::cout << j << "\n";

    // Polimorfismo dinâmico usando sua classe base classificacao!
    classificacao* secreto = new PerfilExtraordinario();
    secreto->resultado(j);
    delete secreto;

    std::cout << "\n" << TerminalUI::negri << "--- Resumo da sua trajetoria ---\n" << TerminalUI::reset;
    for (const auto& passo : j.getHistorico().obterTodos()) {
        std::cout << " * " << passo << "\n";
    }

    TerminalUI::pausar();
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
    if (idx == 67) {
    executarEasterEgg(j);
    return nullptr; // Encerra a partida imediatamente como Perfil Extraordinário!
    }
    const Opcao& escolhida = opcoes[idx];

    j += escolhida.consequencia;
    j.registroDecisao(titulo + " -> " + escolhida.texto);

    // Exibe o feedback resultado 
    std::cout << "\n" << TerminalUI::negri << "--- RESULTADO DA SUA ESCOLHA ---\n" << TerminalUI::reset;
    std::cout << escolhida.textoResultado << "\n\n";
    TerminalUI::exibirDeltaImpacto(escolhida.consequencia);

     if(j.getEnergia() <= 0) {
        return nullptr; // Fim do jogo se energia zerar
    }
    return escolhida.proximoNo;
}

// --- NoImprevisto --- NAO MECHER SE NAO EXPLODE
NoImprevisto::NoImprevisto(std::string tit, std::string desc, std::string imprevisto, impacto imp)
    : NoEvento(tit, desc), textoImprevisto(imprevisto), impactoImp(imp) {}

NoEvento* NoImprevisto::exe(jogador& j) const {
    std::cout << TerminalUI::negri << TerminalUI::red << "\n[ IMPREVISTO: " << titulo << " ]\n" << TerminalUI::reset;
    std::cout << textoImprevisto << "\n";
    TerminalUI::exibirDeltaImpacto(impactoImp); // Mostra o impacto do imprevisto na hora
    j += impactoImp;

    if(j.getEnergia() <= 0) {
      j.registroDecisao(titulo + " -> Colapso por falta de energia");
      return nullptr; // Fim do jogo se energia zerar
    }

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

    if (j.getEnergia() <= 0) {
        return nullptr;
    }

    return escolhida.proximoNo;
}

// --- NoFinal ---
NoFinal::NoFinal(std::string tit, std::string desc)
    : NoEvento(tit, desc) {}

NoEvento* NoFinal::exe(jogador& j) const {
    std::cout << TerminalUI::negri << TerminalUI::blue << "\n=== " << titulo << " ===\n" << TerminalUI::reset;
    std::cout << descricao << "\n";

    classificacao* resultado = classificacao::avaliarcaoJ(j);
    resultado->resultado(j);
    delete resultado;

    // Mostra o histórico de escolhas da run
    std::cout << "\n" << TerminalUI::negri << "--- Resumo da sua trajetoria ---\n" << TerminalUI::reset;
    for (const auto& passo : j.getHistorico().obterTodos()) {
        std::cout << " * " << passo << "\n";
    }

    TerminalUI::pausar(); // para nao fechar o jogo automaticamente 
    return nullptr;
}