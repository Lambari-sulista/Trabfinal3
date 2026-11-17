#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Terminal.h"

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

class jogador {
private:
    std::string nome;
    int energia;
    float nota;
    historico<std::string> Decisoes;

public:
    jogador(std::string nome);

    std::string getNome() const { return nome; }
    int getEnergia() const { return energia; }
    float getNota() const { return nota; }
    const historico<std::string>& getHistorico() const { return Decisoes; }

    void ajusteNota(float delta);
    void registroDecisao(const std::string& decisoes);

    jogador& operator+=(const impacto& imp);
    friend std::ostream& operator<<(std::ostream& os, const jogador& j);
};

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
                  << "! Voce fechou o semestre com nota " << std::fixed << std::setprecision(2) << j.getNota()
                  << " e energia de sobra!" << TerminalUI::reset << "\n";
    }
};

class PerfilSobrevivente : public classificacao {
public:
    void resultado(const jogador& j) const override {
        std::cout << TerminalUI::yellow << TerminalUI::negri
                  << "\n[PERFIL SOBREVIVENTE] Ufa, " << j.getNome()
                  << "! Voce passou raspando com nota " << std::fixed << std::setprecision(2) << j.getNota()
                  << ". O semestre cobrou seu preco." << TerminalUI::reset << "\n";
    }
};

class PerfilJubilo : public classificacao {
public:
    void resultado(const jogador& j) const override {
        std::cout << TerminalUI::red << TerminalUI::negri
                  << "\n[PERFIL JUBILADO / EXAUSTO] Que pena, " << j.getNome()
                  << ". Com nota " << std::fixed << std::setprecision(2) << j.getNota()
                  << " e energia em " << j.getEnergia() << "%, voce nao resistiu ao semestre."
                  << TerminalUI::reset << "\n";
    }
};

inline classificacao* classificacao::avaliarcaoJ(const jogador& j) {
    float score = (j.getNota() * 5.0f) + (j.getEnergia() * 0.5f);

    if (j.getEnergia() <= 0 || j.getNota() < 5.75f) {
        return new PerfilJubilo();
    } else if (score >= 80.0f && j.getNota() >= 7.5f) {
        return new PerfilExemplar();
    } else {
        return new PerfilSobrevivente();
    }
}