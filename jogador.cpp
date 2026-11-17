#include "main.h"
#include "Terminal.h"

jogador:: jogador(std::string nome) : nome(nome), energia(100), nota(0.0f), grana(50.0f) {}
// costrutor parametrizado

void jogador::registroDecisao(const std::string& decisoes){
    Decisoes.adicionar(decisoes);
}// função para adicionar ao historico de decisão

void jogador::ajusteNota(float delta) {
    nota = nota + delta;
}// função que calcula nota

jogador& jogador::operator+=(const impacto& imp) {
    energia;
    nota;
    grana;
    return *this;
} // facilitador na hora da impressão da nota

std::ostream& operator<<(std::ostream& os, const jogador& j) {
    os << TerminalUI::negri << TerminalUI::blue
       << "=== ALUNO: " << j.nome
       << " | Energia: " << j.energia << "%"
       << " | Nota: " << std::fixed << j.nota
       << " | Saldo: R$ " <<  j.grana
       << " ===" << TerminalUI::reset;
    return os;
} // operator para dados do jogador