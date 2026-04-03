#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct {
    int vida;
    int exp;
    int gold;
    int velocidade;
    int defesa;
    int defesa_temp;
    int dano_arma;
    int dano_extra;
    int level;
} Personagem;

typedef struct {
    int vida;
    int velocidade;
    int defesa;
    int defesa_temp;
    int dano;
} Inimigo;

void salvar_jogo(Personagem *player) {
    FILE *file = fopen("savegame.txt", "w");
    if (file) {
        fprintf(file, "%d %d %d %d %d %d %d %d\n", player->vida, player->exp, player->gold, player->velocidade, player->defesa, player->dano_arma, player->dano_extra, player->level);
        fclose(file);
        printf("Jogo salvo com sucesso!\n");
    } else {
        printf("Erro ao salvar o jogo.\n");
    }
}

void carregar_jogo(Personagem *player) {
    FILE *file = fopen("savegame.txt", "r");
    if (file) {
        fscanf(file, "%d %d %d %d %d %d %d %d", &player->vida, &player->exp, &player->gold, &player->velocidade, &player->defesa, &player->dano_arma, &player->dano_extra, &player->level);
        fclose(file);
        printf("Jogo carregado com sucesso!\n");
    } else {
        printf("Nenhum jogo salvo encontrado.\n");
    }
}

void exibir_status(Personagem *player) {
    printf("Status do Jogador:\n");
    printf("Vida: %d\n", player->vida);
    printf("EXP: %d\n", player->exp);
    printf("Gold: %d\n", player->gold);
    printf("Velocidade: %d\n", player->velocidade);
    printf("Defesa: %d\n", player->defesa);
    printf("Dano: %d\n", player->dano_arma + player->dano_extra);
    printf("Level: %d\n\n", player->level);
}

void inicializar_jogador(Personagem *player) {
    player->vida = 100;
    player->exp = 0;
    player->gold = 0;
    player->velocidade = 8;
    player->defesa = 4;
    player->defesa_temp = 0;
    player->dano_arma = 10;
    player->dano_extra = 0;
    player->level = 1;
}

Inimigo gerar_inimigo(int level_jogador) {
    Inimigo inimigo;
    inimigo.vida = 70 + level_jogador * 10;
    inimigo.velocidade = 6 + level_jogador * 2;
    inimigo.defesa = 4 + level_jogador * 2;
    inimigo.dano = 6 + level_jogador * 2;
    inimigo.defesa_temp = 0;
    return inimigo;
}

void realizar_acao_inimigo(Personagem *player, Inimigo *inimigo) {
    int escolha = rand() % 2;
    if (escolha == 0) {
        int dano = inimigo->dano - (player->defesa + player->defesa_temp);
        if (dano < 0) dano = 0;
        player->vida -= dano;
        printf("Inimigo te atacou e causou %d de dano! Voce possui %d de vida restante.\n", dano, player->vida);
        player->defesa_temp = 0;
    } else {
        printf("Inimigo decide se defender!\n");
        inimigo->defesa_temp = inimigo->defesa;
    }
}

void deletar_jogo() {
    if (remove("savegame.txt") == 0) {
        printf("Arquivo de salvamento deletado com sucesso.\n");
    } else {
        printf("Erro ao deletar o arquivo de salvamento.\n");
    }
}

void batalha(Personagem *player, Inimigo *inimigo) {
    printf("Voce encontrou um inimigo!\n");
    printf("Batalha iniciada!\n");
    while (player->vida > 0 && inimigo->vida > 0) {
        int jogador_ataca_primeiro = player->velocidade > inimigo->velocidade;

        if (jogador_ataca_primeiro) {
            char acao;
            printf("Escolha sua acao: (a)taque, (d)efesa: ");
            scanf(" %c", &acao);
            if (acao == 'a') {
                int dano = player->dano_arma + player->dano_extra - (inimigo->defesa + inimigo->defesa_temp);
                if (dano < 0) dano = 0;
                inimigo->vida -= dano;
                printf("Voce ataca e causa %d de dano! Inimigo tem %d de vida restante.\n", dano, inimigo->vida);
                inimigo->defesa_temp = 0;
            } else if (acao == 'd') {
                player->defesa_temp = player->defesa;
                printf("Voce se defendeu! Defesa aumentada temporariamente.\n");
            } else {
                printf("Acao invalida! Perdeu a vez.\n");
            }

            if (inimigo->vida > 0) {
                realizar_acao_inimigo(player, inimigo);
            }
        } else {
            realizar_acao_inimigo(player, inimigo);

            if (player->vida > 0) {
                char acao;
                printf("Escolha sua acao: (a)taque, (d)efesa: ");
                scanf(" %c", &acao);
                if (acao == 'a') {
                    int dano = player->dano_arma + player->dano_extra - (inimigo->defesa + inimigo->defesa_temp);
                    if (dano < 0) dano = 0;
                    inimigo->vida -= dano;
                    printf("Voce ataca e causa %d de dano! Inimigo tem %d de vida restante.\n", dano, inimigo->vida);
                    inimigo->defesa_temp = 0;
                } else if (acao == 'd') {
                    player->defesa_temp = player->defesa;
                    printf("Voce se defendeu! Defesa aumentada temporariamente.\n");
                } else {
                    printf("Acao invalida! Perdeu a vez.\n");
                }
            }
        }
    }

    if (player->vida > 0) {
        printf("Jogador venceu a batalha!\n");
        int ouro_ganho = rand() % 400 + 200;
        int exp_ganha = rand() % 150 + 100;
        printf("Voce ganhou %d de ouro e %d de EXP.\n", ouro_ganho, exp_ganha);
        player->exp += exp_ganha;
        player->gold += ouro_ganho;
    } else {
        printf("Jogador foi derrotado...\n");
        deletar_jogo();
        inicializar_jogador(player);
    }
}

void subir_de_nivel(Personagem *player) {
    if (player->exp >= 300) {
        player->level++;
        player->exp -= 300;
        printf("Voce subiu para o nivel %d!\n", player->level);

        int escolha;
        printf("Deseja aumentar sua Vida (1) ou Velocidade (2)? ");
        scanf("%d", &escolha);
        if (escolha == 1) {
            player->vida += 10;
            printf("Vida aumentada para %d.\n", player->vida);
        } else if (escolha == 2) {
            player->velocidade += 1;
            printf("Velocidade aumentada para %d.\n", player->velocidade);
        } else {
            printf("Escolha invalida.\n");
        }
    }
}

void loja(Personagem *player) {
    int escolha;
    printf("Bem-vindo a loja!\n");
    printf("Voce tem %d de gold.\n", player->gold);
    while (1) {
        int custo_defesa = 1000;
        int custo_dano = 1000;

        printf("Para melhorar a Armadura (Defesa) custa %d de gold.\n", custo_defesa);
        printf("Para melhorar a Espada (Dano) custa %d de gold.\n", custo_dano);
        printf("Escolha o que deseja fazer:\n");
        printf("1 - Melhorar armadura (Defesa)\n");
        printf("2 - Melhorar espada (Dano)\n");
        printf("3 - Sair da loja\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (player->gold >= custo_defesa) {
                    player->defesa++;
                    player->gold -= custo_defesa;
                    printf("Defesa aumentada para %d.\n", player->defesa);
                } else {
                    printf("Voce nao possui gold suficiente para melhorar sua armadura.\n");
                }
                break;
            case 2:
                if (player->gold >= custo_dano) {
                    player->dano_extra++;
                    player->gold -= custo_dano;
                    printf("Dano extra aumentado para %d.\n", player->dano_extra);
                } else {
                    printf("Voce nao possui gold suficiente para melhorar sua espada.\n");
                }
                break;
            case 3:
                printf("Saindo da loja...\n");
                return;
            default:
                printf("Escolha invalida.\n");
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");

    srand(time(NULL));
    Personagem player;
    inicializar_jogador(&player);
    carregar_jogo(&player);
    exibir_status(&player);

    char comando;
    while (1) {
        printf("Comandos: (b)atalha, (s)tatus, (l)oja, (q)uit: ");
        scanf(" %c", &comando);
        if (comando == 'b') {
            Inimigo inimigo = gerar_inimigo(player.level);
            batalha(&player, &inimigo);
            subir_de_nivel(&player);
            salvar_jogo(&player);
        } else if (comando == 's') {
            exibir_status(&player);
        } else if (comando == 'l') {
            loja(&player);
        } else if (comando == 'q') {
            salvar_jogo(&player);
            break;
        } else {
            printf("Comando invalido.\n");
        }
    }

    return 0;
}