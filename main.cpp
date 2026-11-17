#include <iostream>
#include <string>
#include <vector>
#include "Terminal.h"
#include "main.h"
#include "NoEvento.h"

int main() {
    TerminalUI::Limpar();

    std::string nome;
    std::cout << TerminalUI::negri << TerminalUI::blue
              << "+--------------------------------------------------------------------+\n"
              << "|                   EM BUSCA DO SEMESTRE PERFEITO!                   |\n"
              << "+--------------------------------------------------------------------+\n\n"
              << TerminalUI::reset;

    std::cout << "Voce e um estudante universitario que esta prestes a iniciar seu primeiro semestre.\n"
              << "Seu objetivo e organizar sua rotina de estudos, atividades extracurriculares e vida pessoal\n"
              << "para alcancar o melhor desempenho academico possivel.\n"
              << "Tome as melhores decisoes para alocar seu tempo e energia durante o semestre.\n\n";

    std::cout << "Digite o nome do seu estudante: " << std::flush;
    std::getline(std::cin, nome);

    if (nome.empty()) {
        nome = "Calouro";
    }

    jogador player(nome);

    // 1. CRIACAO DOS NOS
    auto* no3_Calourada = new NoDecisao(
        "SEMANA 1 - A CALOURADA OFICIAL",
        "A calourada oficial acontecera nessa sexta-feira, mas voce ainda nao fez a revisao de pre-calculo."
    );

    auto* no4_Listas = new NoDecisao(
        "SEMANA 3 - A REALIDADE BATEU",
        "A semana de integracao acabou e a ficha finalmente caiu.\n"
        "O professor de Calculo postou uma lista de 40 exercicios de limites e o de Programacao liberou os primeiros trabalhos praticos."
    );

    auto* noRand1_RU = new NoImprevisto(
        "IMPREVISTO - DIA DE CHUVA NO RU",
        "Dia de chuva, a fila do Restaurante Universitario esta dando volta no predio e sua aula comeca em 30 minutos!",
        "Um onibus passou na poca d'agua e molhou sua mochila!",
        {-5, 0.0f}
    );

    auto* no5_Equipe = new NoDecisao(
        "SEMANA 6 - EQUIPES DE COMPETICAO",
        "Hoje e o inicio da semana de processo seletivo das equipes de competicao da universidade.\n"
        "Voce tem a opcao de participar de uma das equipes, mas precisa decidir se vai se dedicar aos estudos ou se envolver com a competicao."
    );

    auto* noRand2_DorCabeca = new NoImprevisto(
        "IMPREVISTO - DOR DE CABECA INSUPORTAVEL",
        "Voce esta com uma dor de cabeca insuportavel e precisa ir para a aula de Calculo, mas o professor esta atrasado.",
        "O barulho no corredor piorou sua enxaqueca enquanto esperava!",
        {-10, 0.0f}
    );

    auto* no6_DiaLivre = new NoDecisao(
        "SEMANA 10 - UM RARO DIA LIVRE",
        "Voce finalmente tem um dia livre hoje no meio do semestre. O que pretende fazer?"
    );

    auto* noRand3_Git = new NoImprevisto(
        "IMPREVISTO - CAOS NO REPOSITORIO",
        "Voce foi abrir seu notebook para revisar os codigos da disciplina e percebeu que esqueceram de dar push na branch principal!",
        "Voce perdeu horas recuperando o historico de commits!",
        {-10, 0.0f}
    );

    auto* no67_PrazoFinal = new NoDecisao(
        "RETA FINAL - ENTREGA AS 23:59",
        "Voce se esqueceu completamente de um trabalho de Programacao que vale 20% da nota final.\n"
        "Prazo de entrega ate hoje as 23:59!"
    );

    auto* noFinal_Boletim = new NoFinal(
        "FIM DO PRIMEIRO SEMESTRE",
        "As provas terminaram e o sistema academico consolidou suas notas e frequencia."
    );

    std::vector<NoEvento*> arvore = {
        no3_Calourada, no4_Listas, noRand1_RU, no5_Equipe,
        noRand2_DorCabeca, no6_DiaLivre, noRand3_Git, no67_PrazoFinal, noFinal_Boletim
    };

    // 2. CONEXOES {Energia, Nota}
    no3_Calourada->addOpcao(
        "Estudar sozinho",
        "Voce revisou funcoes e trigonometria em silencio no quarto. Comecou o semestre com a base solida.",
        {-15, +1.5f},
        no4_Listas
    );
    no3_Calourada->addOpcao(
        "Estudar com novos amigos",
        "Voce revisou a materia e ainda formou um grupo de estudos para o resto do semestre!",
        {-10, +1.0f},
        no4_Listas
    );
    no3_Calourada->addOpcao(
        "Nao estudar e ir para a calourada",
        "A festa foi epica e voce conheceu metade do campus, mas perdeu o ritmo inicial.",
        {-25, -0.5f},
        no4_Listas
    );

    no4_Listas->addOpcao(
        "Fazer toda a lista de limites",
        "40 exercicios depois, voce domina indeterminacoes, mas sua mao e cerebro pedem socorro.",
        {-25, +2.0f},
        noRand1_RU
    );
    no4_Listas->addOpcao(
        "Fazer o trabalho de Programacao",
        "Seu codigo compilou de primeira sem vazamento de memoria! O professor elogiou a logica.",
        {-20, +2.0f},
        noRand1_RU
    );
    no4_Listas->addOpcao(
        "Se enturmar com a galera no Bloco C",
        "Voce jogou conversa fora, pegou dicas de veteranos sobre os professores e tomou um cafe.",
        {+5, +0.5f},
        noRand1_RU
    );
    no4_Listas->addOpcao(
        "Tirar o dia para descansar",
        "Voce dormiu a tarde inteira e recuperou o folego, embora as listas continuem acumuladas.",
        {+25, -0.5f},
        noRand1_RU
    );

    noRand1_RU->addOpcao(
        "Almocar na pressa e se atrasar para a aula",
        "Voce comeu rapido demais e chegou 15 minutos atrasado, pegando a explicacao pela metade.",
        {+10, +0.5f},
        no5_Equipe
    );
    noRand1_RU->addOpcao(
        "Pular o almoco e ir para a aula",
        "Voce assistiu a aula inteira e anotou tudo, mas seu estomago roncou ate o fim do turno.",
        {-20, +1.5f},
        no5_Equipe
    );
    noRand1_RU->addOpcao(
        "Pular a aula e almocar com calma",
        "Voce fez uma refeicao tranquila enquanto via a chuva cair, mas perdeu materia nova.",
        {+15, -1.0f},
        no5_Equipe
    );

    no5_Equipe->addOpcao(
        "Se dedicar somente aos estudos por enquanto",
        "Voce manteve o foco total nas disciplinas obrigatorias e garantiu boas notas nas provas parciais.",
        {-10, +2.0f},
        noRand2_DorCabeca
    );
    no5_Equipe->addOpcao(
        "Se inscrever para a equipe de competicao",
        "Voce passou na selecao! Aprendeu muito na pratica na oficina, embora o tempo livre tenha sumido.",
        {-25, +1.0f},
        noRand2_DorCabeca
    );

    noRand2_DorCabeca->addOpcao(
        "Ir para a aula mesmo com dor de cabeca",
        "Foi dificil concentrar no quadro, mas voce garantiu a presenca e copiou os exemplos da prova.",
        {-20, +1.0f},
        no6_DiaLivre
    );
    noRand2_DorCabeca->addOpcao(
        "Ir para casa e descansar",
        "Voce apagou na cama e acordou zerado no dia seguinte, pronto para a reta final.",
        {+30, -0.5f},
        no6_DiaLivre
    );

    no6_DiaLivre->addOpcao(
        "Estudar para as provas futuras",
        "Voce transformou o dia livre em uma maratona de revisao e resumiu toda a materia.",
        {-20, +2.0f},
        noRand3_Git
    );
    no6_DiaLivre->addOpcao(
        "Sair com os amigos",
        "Voce desligou a mente da faculdade por um dia inteiro e voltou renovado.",
        {+15, 0.0f},
        noRand3_Git
    );
    no6_DiaLivre->addOpcao(
        "Tirar o dia para descansar",
        "Dia de descanso absoluto. Sua energia voltou la para cima!",
        {+30, 0.0f},
        noRand3_Git
    );

    noRand3_Git->addOpcao(
        "Reescrever a parte perdida com calma",
        "Deu trabalho, mas o codigo ficou ainda mais limpo e bem documentado que antes.",
        {-15, +1.0f},
        no67_PrazoFinal
    );
    noRand3_Git->addOpcao(
        "Fazer um workaround rapido para entregar",
        "Funcionou na base da gambiarra, economizou energia, mas o professor vai notar.",
        {-5, -0.5f},
        no67_PrazoFinal
    );

    no67_PrazoFinal->addOpcao(
        "E o vibe e o codas (madrugar no cafe e energetico)",
        "Voce enviou o arquivo as 23:58! O codigo rodou, mas voce quase virou um zumbi no dia seguinte.",
        {-35, +1.5f},
        noFinal_Boletim
    );
    no67_PrazoFinal->addOpcao(
        "E la vamos nos... (fazer o possivel ate dar o horario e ir dormir)",
        "Voce entregou o projeto incompleto para preservar sua saude mental e dormir antes da prova.",
        {-10, -1.5f},
        noFinal_Boletim
    );

    // 3. LOOP PRINCIPAL
    NoEvento* noAtual = no3_Calourada;

    while (noAtual != nullptr) {
        TerminalUI::Limpar();
        std::cout << player << "\n";

        noAtual = noAtual->exe(player);

        if (noAtual != nullptr) {
            TerminalUI::pausar();
        }
    }

    for (NoEvento* no : arvore) {
        delete no;
    }

    return 0;
}