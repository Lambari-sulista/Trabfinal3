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

    // =========================================================================
    // 1. CRIACAO DOS NOS DA HISTORIA PRINCIPAL
    // =========================================================================
    auto* no3_Calourada = new NoDecisao(
        "SEMANA 1 - A CALOURADA OFICIAL",
        "A calourada oficial acontecera nessa sexta-feira, mas voce ainda nao fez a revisao de pre-calculo."
    );

    auto* no4_Listas = new NoDecisao(
        "SEMANA 2 - A REALIDADE BATEU",
        "A semana de integracao acabou e a ficha finalmente caiu.\n"
        "O professor de Calculo postou uma lista de 40 exercicios de limites e o de Programacao liberou os primeiros trabalhos praticos."
    );

    auto* no5_Equipe = new NoDecisao(
        "SEMANA 3 - EQUIPES DE COMPETICAO",
        "Hoje e o inicio da semana de processo seletivo das equipes de competicao da universidade.\n"
        "Voce tem a opcao de participar de uma das equipes, mas precisa decidir se vai se dedicar aos estudos ou se envolver com a competicao."
    );

    auto* no_Monitoria = new NoDecisao(
        "SEMANA 4 - CONSULTA COM O MONITOR",
        "Voce travou nos limites trigonometricos e na regra da cadeia.\n"
        "O horario de monitoria de Calculo 1 comeca agora, bem na janela do almoco."
    );

    auto* no_P1Calculo = new NoDecisao(
        "SEMANA 5 - A PRIMEIRA PROVA DE CALCULO 1 (P1)",
        "Amanha ja e o dia da temida P1! A sala esta em silencio absoluto, a prova tera questoes discursivas\n"
        "de limites e derivadas"
    );

    auto* no_Feriado = new NoDecisao(
        "SEMANA 6 - FERIADAO PROLONGADO",
        "Emendou quinta e sexta! Sao quatro dias seguidos sem aula no meio do semestre.\n"
        "Como voce vai aproveitar essa pausa?"
    );

    auto* no6_DiaLivre = new NoDecisao(
        "SEMANA 7 - UM RARO DIA LIVRE",
        "Voce finalmente tem um dia livre hoje no meio do semestre. O que pretende fazer?"
    );

    auto* no67_PrazoFinal = new NoDecisao(
        "SEMANA 8 - ENTREGA AS 23:59",
        "Voce se esqueceu completamente de um trabalho de Programacao que vale 20% da nota final.\n"
        "Prazo de entrega ate hoje as 23:59!"
    );

    auto* no_P2Calculo = new NoDecisao(
        "SEMANA 9 - A P2 DE CALCULO 1",
        "Reta final do semestre! A P2 de amanha cobra tecnicas de integracao e calculo de areas,\n"
        "e metade da turma esta fazendo contas de quanto precisa para fugir da REC."
    );

    auto* noFinal_Boletim = new NoFinal(
        "FIM DO PRIMEIRO SEMESTRE",
        "As provas terminaram e o sistema academico consolidou suas notas e frequencia."
    );

    // =========================================================================
    // 2. CRIACAO DOS NOS ALEATORIOS / IMPREVISTOS (Ramificacoes por escolha)
    // =========================================================================
    auto* noRand_Onibus = new NoImprevisto(
        "IMPREVISTO - ONIBUS LOTADO DE MANHA",
        "Voce dormiu demais depois da festa e pegou o onibus no horario de pico para a aula das 7h30!",
        "O transito travou na avenida e voce chegou exausto!",
        {-5, 0.0f}
    );

    auto* noRand1_RU = new NoImprevisto(
        "IMPREVISTO - DIA DE CHUVA NO RU",
        "Dia de chuva, a fila do Restaurante Universitario esta dando volta no predio e sua aula comeca em 30 minutos!",
        "Um onibus passou na poca d'agua e molhou sua mochila!",
        {-5, 0.0f}
    );

    auto* noRand2_DorCabeca = new NoImprevisto(
        "IMPREVISTO - DOR DE CABECA INSUPORTAVEL",
        "Voce esta com uma dor de cabeca insuportavel e precisa ir para a aula de Calculo, mas o professor esta atrasado.",
        "O barulho no corredor piorou sua enxaqueca enquanto esperava!",
        {-10, 0.0f}
    );

    auto* noRand_Oficina = new NoImprevisto(
        "IMPREVISTO - CURTO-CIRCUITO NA OFICINA",
        "Na sua primeira semana na equipe de competicao, uma placa queimou bem antes da apresentacao interna!",
        "Voce ficou ate tarde ajudando a soldar os componentes reservas!",
        {-10, +0.5f}
    );

    auto* noRand_Fome = new NoImprevisto(
        "IMPREVISTO - ESTOMAGO RONCANDO NA AULA",
        "Como voce pulou o almoco para ir na monitoria, sua pressao caiu no meio da aula da tarde!",
        "Voce mal conseguia prestar atencao no quadro de tanta fome!",
        {-10, -0.5f}
    );

    auto* noRand_Virose = new NoImprevisto(
        "IMPREVISTO - IMUNIDADE BAIXA POS-PROVA",
        "Depois de tanto estresse para a P1, voce acordou com a garganta inflamada e o corpo pesado!",
        "A mudanca brusca de tempo derrubou sua disposicao!",
        {-10, 0.0f}
    );

    auto* noRand_TransitoFeriado = new NoImprevisto(
        "IMPREVISTO - ENGARRAFAMENTO NA VOLTA DO FERIADO",
        "A estrada travou na volta do feriadao e voce chegou direto da rodoviaria para a aula!",
        "Voce passou horas preso no onibus com a mochila nas costas!",
        {-10, 0.0f}
    );

    auto* noRand3_Git = new NoImprevisto(
        "IMPREVISTO - CAOS NO REPOSITORIO",
        "Voce foi abrir seu notebook para revisar os codigos da disciplina e percebeu que esqueceram de dar push na branch principal!",
        "Voce perdeu horas recuperando o historico de commits!",
        {-10, 0.0f}
    );


    // Vetor com TODOS os nos para liberacao de memoria no final
    std::vector<NoEvento*> arvore = {
        no3_Calourada, no4_Listas, no5_Equipe, no_Monitoria, no_P1Calculo,
        no_Feriado, no6_DiaLivre, no67_PrazoFinal, no_P2Calculo, noFinal_Boletim,
        noRand_Onibus, noRand1_RU, noRand2_DorCabeca, noRand_Oficina,
        noRand_Fome, noRand_Virose, noRand_TransitoFeriado, noRand3_Git
    };

    // =========================================================================
    // 3. CONEXOES {Energia, Nota} - Cada escolha leva a caminhos distintos
    // =========================================================================

    // SEMANA 1 - CALOURADA
    no3_Calourada->addOpcao(
        "Estudar sozinho",
        "Voce revisou funcoes e trigonometria em silencio no quarto. Comecou o semestre com a base solida.",
        {-15, +3.5f},
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
        noRand_Onibus 
    );

    noRand_Onibus->addOpcao(
        "Correr do ponto ate o bloco",
        "Voce chegou ofegante na sala, mas conseguiu assinar a lista de presenca.",
        {-10, +0.5f},
        no4_Listas
    );
    noRand_Onibus->addOpcao(
        "Ir andando devagar e tomar um cafe no caminho",
        "Voce perdeu os primeiros 20 minutos de aula, mas nao se desgastou mais.",
        {+5, -0.5f},
        no4_Listas
    );

    // SEMANA 3 - LISTAS
    no4_Listas->addOpcao(
        "Fazer toda a lista de limites",
        "40 exercicios depois, voce domina indeterminacoes, mas sua mao e cerebro pedem socorro.",
        {-25, +2.0f},
        noRand2_DorCabeca 
    );
    no4_Listas->addOpcao(
        "Fazer o trabalho de Programacao",
        "Seu codigo compilou de primeira sem vazamento de memoria! O professor elogiou a logica.",
        {-20, +2.0f},
        no5_Equipe 
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
        no5_Equipe 
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

    noRand2_DorCabeca->addOpcao(
        "Ir para a aula mesmo com dor de cabeca",
        "Foi dificil concentrar no quadro, mas voce garantiu a presenca e copiou os exemplos da prova.",
        {-20, +1.0f},
        no5_Equipe
    );
    noRand2_DorCabeca->addOpcao(
        "Ir para casa e descansar",
        "Voce apagou na cama e acordou zerado no dia seguinte, pronto para a reta final.",
        {+30, -0.5f},
        no5_Equipe
    );

    // SEMANA 6 - EQUIPES DE COMPETICAO
    no5_Equipe->addOpcao(
        "Se dedicar somente aos estudos por enquanto",
        "Voce manteve o foco total nas disciplinas obrigatorias e garantiu boas notas nas provas parciais.",
        {-10, +2.0f},
        no_Monitoria 
    );
    no5_Equipe->addOpcao(
        "Se inscrever para a equipe de competicao",
        "Voce passou na selecao! Aprendeu muito na pratica na oficina, embora o tempo livre tenha sumido.",
        {-25, +1.0f},
        noRand_Oficina 
    );

    noRand_Oficina->addOpcao(
        "Ficar para ajudar a resolver o problema",
        "Os veteranos elogiaram sua dedicacao e voce aprendeu a usar o osciloscopio na marra!",
        {-15, +1.0f},
        no_Monitoria
    );
    noRand_Oficina->addOpcao(
        "Voltar para casa para nao perder a aula do dia seguinte",
        "Voce priorizou suas disciplinas e conseguiu dormir no horario.",
        {+10, 0.0f},
        no_Monitoria
    );

    // SEMANA 7 - CONSULTA COM O MONITOR
    no_Monitoria->addOpcao(
        "Ir direto para a monitoria e pular o almoco",
        "Voce tirou todas as duvidas com o veterano, mas saiu da sala com o estomago roncando.",
        {-20, +1.5f},
        noRand_Fome // Ramifica para imprevisto de fome na aula da tarde
    );
    no_Monitoria->addOpcao(
        "Almocar rapido no RU e pegar os ultimos 20 minutos",
        "Voce resolveu a duvida principal e ainda conseguiu comer antes da proxima aula.",
        {-5, +1.0f},
        no_P1Calculo // Segue direto para P1
    );
    no_Monitoria->addOpcao(
        "Ignorar a monitoria e estudar por videoaulas em casa",
        "Voce evitou a correria no campus, mas demorou o dobro do tempo para entender a materia.",
        {-10, +0.5f},
        no_P1Calculo // Segue direto para P1
    );

    noRand_Fome->addOpcao(
        "Comprar um salgado na cantina no intervalo",
        "Recuperou as forcas a tempo de copiar a revisao final para a P1.",
        {+15, +0.5f},
        no_P1Calculo
    );
    noRand_Fome->addOpcao(
        "Segurar a fome ate chegar em casa",
        "Voce economizou tempo, mas saiu completamente esgotado da universidade.",
        {-15, 0.0f},
        no_P1Calculo
    );

    // SEMANA 8 - PRIMEIRA PROVA DE CALCULO 1 (P1)
    no_P1Calculo->addOpcao(
        "Dar o sangue e revisar cada passo algebrico ate o fim",
        "No dia seguinte voce evitou erros bobos de sinal e fechou as questoes principais, mas saiu mentalmente esgotado.",
        {-30, +2.5f},
        noRand_Virose 
    );
    no_P1Calculo->addOpcao(
        "Revisar o essencial e dormir bem para a prova",
        "Estrategia segura: voce confiou no seu preparo, fez uma boa prova e preservou o psicologico para o resto da semana.",
        {-10, +1.5f},
        no_Feriado 
    );
    no_P1Calculo->addOpcao(
        "Apenas tem uma boa noite de sono",
        "Voce até entrega a prova antes do tempo acabar, mas deixou passar detalhes importantes.",
        {+5, 0.0f},
        no_Feriado // Segue direto para o feriado
    );

    noRand_Virose->addOpcao(
        "Tomar um cha, remedio e dormir cedo",
        "Voce cortou o mal pela raiz e chegou inteiro para aproveitar o feriado.",
        {+20, 0.0f},
        no_Feriado
    );
    noRand_Virose->addOpcao(
        "Ignorar os sintomas e continuar estudando",
        "Voce avancou na materia de Programacao, mas arrastou o cansaco por dias.",
        {-15, +1.0f},
        no_Feriado
    );

    // SEMANA 9 - FERIADAO PROLONGADO
    no_Feriado->addOpcao(
        "Ficar estudando e colocar toda a materia em dia",
        "Zero vida social no feriado, mas voce voltou para as aulas com tudo em dia.",
        {-20, +2.0f},
        no6_DiaLivre // Segue direto
    );
    no_Feriado->addOpcao(
        "Viajar para visitar a familia e desligar da faculdade",
        "Voce recuperou totalmente as energias, mesmo sem abrir um caderno nos quatro dias.",
        {+35, -0.5f},
        noRand_TransitoFeriado // Ramifica para imprevisto na volta da viagem
    );
    no_Feriado->addOpcao(
        "Dividir o tempo entre descanso e revisao leve",
        "Voce organizou seus resumos pela manha e aproveitou as tardes para descansar.",
        {+15, +1.0f},
        no6_DiaLivre // Segue direto
    );

    noRand_TransitoFeriado->addOpcao(
        "Revisar os slides no celular dentro do onibus",
        "Aproveitou o tempo parado no transito para relembrar os conceitos da semana.",
        {-5, +7.5f},
        no6_DiaLivre
    );
    noRand_TransitoFeriado->addOpcao(
        "Colocar fones de ouvido e tirar um cochilo",
        "Chegou descansado apesar do atraso na estrada.",
        {+10, 0.0f},
        no6_DiaLivre
    );

    // SEMANA 11 - UM RARO DIA LIVRE
    no6_DiaLivre->addOpcao(
        "Estudar para as provas futuras",
        "Voce transformou o dia livre em uma maratona de revisao e resumiu toda a materia.",
        {-20, +2.0f},
        no67_PrazoFinal 
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
        no67_PrazoFinal 
    );

    noRand3_Git->addOpcao(
        "Reescrever a parte perdida com calma",
        "Deu trabalho, mas o codigo ficou ainda mais limpo e bem documentado que antes.",
        {-15, +2.0f},
        no67_PrazoFinal
    );
    noRand3_Git->addOpcao(
        "Fazer um workaround rapido para entregar",
        "Funcionou na base da gambiarra, economizou energia, mas o professor vai notar.",
        {-5, -0.5f},
        no67_PrazoFinal
    );

    // SEMANA 13 - ENTREGA AS 23:59
    no67_PrazoFinal->addOpcao(
        "E o vibe e o codas",
        "Voce enviou o arquivo as 23:58! O codigo rodou, mas voce nao aprendeu muita coisa.",
        {+5, +2.0f},
        no_P2Calculo 
    );
    no67_PrazoFinal->addOpcao(
        "E la vamos nos... (fazer o possivel ate dar o horario e ir dormir)",
        "Voce entregou o projeto completo a custo da sua energia.",
        {-10, +2.0f},
        no_P2Calculo 
    );

    // SEMANA 14 - P2 DE CALCULO 1
    no_P2Calculo->addOpcao(
        "Virar a noite fazendo integrais a base de cafe",
        "Voce chegou sabendo resolver qualquer substituicao trigonometrica, mas quase dormindo na carteira.",
        {-30, +3.5f},
        noFinal_Boletim
    );
    no_P2Calculo->addOpcao(
        "Estudar questoes de maior dificuldade e gerenciar o tempo para nao se desgastar",
        "Voce manteve a cabeca fria e garantiu uma otima pontuacao sem se destruir.",
        {-15, +4.0f},
        noFinal_Boletim
    );
    no_P2Calculo->addOpcao(
        "Chutar os metodos de integracao e sair na metade da prova",
        "Voce desistiu antes mesmo da prova ter começado para ir descansar e esquecer a materia.",
        {+10, -1.0f},
        noFinal_Boletim
    );

    // LOOP PRINCIPAL, a unica parte que importa da main ta aqui
    NoEvento* noAtual = no3_Calourada;

    bool jogarNovamente = false;
    do{ 
        player = jogador(nome);
        NoEvento* noAtual = no3_Calourada;

    while (noAtual != nullptr) {
        TerminalUI::Limpar();
        std::cout << player << "\n";

        noAtual = noAtual->exe(player);

        if (noAtual != nullptr) {
            TerminalUI::pausar();
        }
        }
    if(player.getEnergia() <= 0) {
       TerminalUI::pausar(); // Pausa para ler o resultado da ultima acao antes de limpar
            TerminalUI::Limpar();
            std::cout << player << "\n";

            std::cout << TerminalUI::negri << TerminalUI::red
                      << "\n+--------------------------------------------------------------------+\n"
                      << "|                    GAME OVER - BURNOUT ACADEMICO!                  |\n"
                      << "+--------------------------------------------------------------------+\n"
                      << TerminalUI::reset
                      << "\nSua energia chegou a 0%! Voce levou seu corpo e mente ao limite,\n"
                      << "precisou trancar as disciplinas para cuidar da saude e nao concluiu o semestre.\n";
            std::string resposta;
            std::cout << TerminalUI::negri << TerminalUI::blue
                      << "\nDeseja jogar novamente? (s/n): "
                      << TerminalUI::reset
                      << std::flush;
            std::getline(std::cin, resposta);

            jogarNovamente = (!resposta.empty() && (resposta[0] == 's' || resposta[0] == 'S'));
        } 
      }  while (jogarNovamente);

    for (NoEvento* no : arvore) {
        delete no;
    } 

   
    return 0;
    
}  