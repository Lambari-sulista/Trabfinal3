#pragma once 
#include<iostream>
#include<vector>
#include<string>
#include"Terminal.h"


struct impacto{
    int energia = 0;
    float nota = 0.0f;
    float dinheiro = 0.0f;

};


template< typename T>
    class historico{
        private:
        std::vector<T> registros;
        public:

        void adicionar(const T& item){ //capacidade de adicionar algo no historico de açoes
            registros.push_back(item);
        }
        const std::vector<T>& obterTodos() const { // vetor de registros
            return  registros;
        }
        size_t tamanho() const { // tamanho do vetor equivalente aos nos de história
        return registros.size();
    }
    };  

class jogador {
    private:
        std::string nome; //nome
        int energia; // variação da energia
        float nota; // nota semestral
        float grana; // saldo
        historico<std::string> Decisoes; // classe de armazenamento das ações
    public:
    jogador(std::string nome); // construtor por referência do jogador

    //getters
    std::string getNome() const { return nome; } // variaveis específicas para serem chamadas durante o jogo a fim de obter de maneira adequada e rápida
    int getEnergia() const { return energia; }
    float getNota() const { return nota; }
    float getGrana() const { return grana; }
    const historico<std::string>& getHistorico() const { return Decisoes; }

    //polimorfismo estatico
    void ajusteNota(float delta);
    void registroDecisao(const std::string& decisoes);

    jogador& operator+=(const impacto& imp);
    friend std::ostream& operator<<(std::ostream& os, const jogador& j);
};
    
class acao : public TerminalUI {};

class barra_energia {};
class No_historia {};