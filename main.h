#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Terminal.h"

//historico acoes
template <typename T>
class historico {
private:
    std::vector<T> registros;

public:
    void adicionar(const T& item) {
        registros.push_back(item);
    }
    const std::vector<T>& obterTodos() const {
        return registros;
    }
    size_t tamanho() const {
        return registros.size();
    }
};
//jogador com energia, conhecimento e historico de decisoes
class jogador {
private:
    std::string nome;
    int energia;
    float conhecimento;
    historico<std::string> Decisoes;

public:
    jogador();
    jogador(std::string nome);

    std::string getNome() const { return nome; }
    int getEnergia() const { return energia; }
    float getNota() const { return conhecimento; }
    const historico<std::string>& getHistorico() const { return Decisoes; }

    void ajusteconhecimento(float delta);
    void registroDecisao(const std::string& decisoes);

    jogador& operator+=(const impacto& imp);
    friend std::ostream& operator<<(std::ostream& os, const jogador& j);
};
//classificação do jogador no final do semestre
class classificacao {
public:
    virtual ~classificacao() = default;
    virtual void resultado(const jogador& j) const = 0;
    static classificacao* avaliarcaoJ(const jogador& j);
};

class PerfilExemplar : public classificacao {
public:
    void resultado(const jogador& j) const override {
        std::cout << TerminalUI::green << TerminalUI::negri
                  << "\n[PERFIL EXEMPLAR] Parabens, " << j.getNome()
                  << "! Voce fechou o semestre com conhecimento " << std::fixed << std::setprecision(2) << j.getNota()
                  << " e energia de sobra!" << TerminalUI::reset << "\n";
    }
};

class PerfilSobrevivente : public classificacao {
public:
    void resultado(const jogador& j) const override {
        std::cout << TerminalUI::yellow << TerminalUI::negri
                  << "\n[PERFIL SOBREVIVENTE] Ufa, " << j.getNome()
                  << "! Voce passou raspando com conhecimento " << std::fixed << std::setprecision(2) << j.getNota()
                  << ". O semestre cobrou seu preco." << TerminalUI::reset << "\n";
    }
};

class PerfilJubilo : public classificacao {
public:
    void resultado(const jogador& j) const override {
        std::cout << TerminalUI::red << TerminalUI::negri
                  << "\n[PERFIL JUBILADO / EXAUSTO] Que pena, " << j.getNome()
                  << ". Com conhecimento " << std::fixed << std::setprecision(2) << j.getNota()
                  << " e energia em " << j.getEnergia() << "%, voce nao resistiu ao semestre."
                  << TerminalUI::reset << "\n";
    }
};

class PerfilExtraordinario : public classificacao {
public:
    void  resultado(const jogador& j) const override {
        std::cout << "\n";
        TerminalUI::imprimirRGB("====================================================================\n");
        TerminalUI::imprimirRGB("   [ EASTER EGG DESBLOQUEADO: PERFIL EXTRAORDINARIO - GOD MODE ]    \n");
        TerminalUI::imprimirRGB("====================================================================\n\n");
        
        TerminalUI::imprimirRGB("Parabens, " + j.getNome() + "! Voce transcendeu a grade curricular da Engenharia,\n");
        TerminalUI::imprimirRGB("gabaritou Calculo e Programacao por telepatia e zerou o semestre!\n");
    }
};

inline classificacao* classificacao::avaliarcaoJ(const jogador& j) {
    float score = (j.getNota() * 5.0f);

    if (j.getEnergia() <= 0 || j.getNota() < 10.0f) {
        return new PerfilJubilo();
    } else if (score >= 80.0f && j.getNota() >= 30.0f) {
        return new PerfilExemplar();
    } else {
        return new PerfilSobrevivente();
    }
}