#include "main.h"
#include "Terminal.h"

jogador::jogador() : nome("Calouro"), energia(100), conhecimento(0.0) {}
jogador:: jogador(std::string nome) : nome(nome), energia(100), conhecimento(0.0){}
// costrutor parametrizado

void jogador::registroDecisao(const std::string& decisoes){
    Decisoes.adicionar(decisoes);
}// função para adicionar ao historico de decisão

//void jogador::ajusteconhecimento(float delta) {
//    conhecimento += delta;
//    if (conhecimento > 10.0f) conhecimento = 10.0f;
//    if (conhecimento < 0.0f) conhecimento = 0.0f;
//}

jogador& jogador::operator+=(const impacto& imp) {
    energia = limitarValor(energia + imp.energia, 0, 100);

    conhecimento = limitarValor(conhecimento + imp.conhecimento, 0.0f, 10.0f);

    return *this;
} // facilitador na hora da impressão do conhecimento

std::ostream& operator<<(std::ostream& os, const jogador& j) {
    os << TerminalUI::negri << TerminalUI::blue
       << "++\n"
       << "| ESTUDANTE: " << std::left << std::setw(18) << j.nome
       << "| CONHECIMENTO: " << std::fixed << std::setprecision(1) << j.conhecimento
       << "++\n"
       << TerminalUI::reset
       << "  ENERGIA: " << TerminalUI::barraProgresso(j.energia)
       << TerminalUI::blue
       << " ++\n"
       << TerminalUI::reset;
    return os;
} // operator para dados do jogador