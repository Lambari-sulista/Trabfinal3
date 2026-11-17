#include "main.h"
#include "Terminal.h"


jogador:: jogador(std::string nome) : nome(nome), energia(100), nota(0.0){}
// costrutor parametrizado

void jogador::registroDecisao(const std::string& decisoes){
    Decisoes.adicionar(decisoes);
}// função para adicionar ao historico de decisão

void jogador::ajusteNota(float delta) {
    nota += delta;
    if (nota > 10.0f) nota = 10.0f;
    if (nota < 0.0f) nota = 0.0f;
}

jogador& jogador::operator+=(const impacto& imp) {
    energia += imp.energia;
    if (energia > 100) energia = 100;
    if (energia < 0) energia = 0;

    nota += imp.nota;
    if (nota > 10.0f) nota = 10.0f;
    if (nota < 0.0f) nota = 0.0f;

    return *this;
} // facilitador na hora da impressão da nota

std::ostream& operator<<(std::ostream& os, const jogador& j) {
    os << TerminalUI::negri << TerminalUI::blue
       << "+------------------------------------------------------------------+\n"
       << "| ESTUDANTE: " << std::left << std::setw(18) << j.nome
       << " | NOTA: " << std::fixed << std::setprecision(1) << j.nota
       << "+------------------------------------------------------------------+\n"
       << TerminalUI::reset
       << "  ENERGIA: " << TerminalUI::barraProgresso(j.energia)
       << TerminalUI::blue
       << "+------------------------------------------------------------------+\n"
       << TerminalUI::reset;
    return os;
} // operator para dados do jogador