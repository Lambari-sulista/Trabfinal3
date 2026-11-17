#pragma once
#include <string>
#include <vector> 
#include "main.h"

class NoEvento;

struct Opcao {
    std::string texto;
    std::string textoResultado;
    impacto consequencia;
    NoEvento* proximoNo;
};
//No base de escolhas
class NoEvento{
    protected:
        std::string titulo;
        std::string descricao;
        std::vector<Opcao> opcoes;

        NoEvento(const NoEvento&);
        NoEvento& operator=(const NoEvento&);
        void executarEasterEgg(jogador& j) const;
    public:
        
        NoEvento(std::string tit, std::string des);
        virtual ~NoEvento();

        void addOpcao(std::string texto,std::string resultado, impacto imp, NoEvento* destino);

        virtual NoEvento* exe(jogador& j) const = 0;
        virtual NoEvento* clonar() const = 0;

    protected:
    size_t LerEscolha() const;
};
//no de decisoes
class NoDecisao : public NoEvento {
    public:

    NoDecisao(std::string tit, std::string desc);
    NoEvento* exe(jogador& j) const override;
    NoEvento* clonar() const override { return new NoDecisao(*this); }
};
class NoImprevisto : public NoEvento {
    private:

        std::string textoImprevisto;
        impacto impactoImp;

    public:
        NoImprevisto(std::string tit, std::string desc, std::string imprevisto, impacto imp);
        NoEvento* exe(jogador& j) const override;
        NoEvento* clonar() const override { return new NoImprevisto(*this); }
       
};

class NoFinal : public NoEvento {
    public:

    NoFinal(std::string tit, std::string desc);
    NoEvento* exe(jogador& j) const override;
    NoEvento* clonar() const override { return new NoFinal(*this); }
};