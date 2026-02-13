#include "domain/board.h"
#include "domain/player.h"
#include "ui/display.h"

void show_board(Board *b) {
    if (!b)
        return -1;

    printf("    ");
    for (int j = 0; j < b->cols; j++)
        printf(" %d  ", j + 1);
    printf("\n");

    printf(WHITE "   +" RESET);
    for (int j = 0; j < b->cols; j++)
        printf(WHITE "---+" RESET);
    printf("\n");

    for (int i = 0; i < b->rows; i++) {
        printf(" %d", i + 1);
        printf(WHITE " |" RESET);

        for (int j = 0; j < b->cols; j++) {
            char color = st_view_color(b->cells[i][j]);
            if (st_view_size(b->cells[i][j])) {
                color == 'v' ? printf(RED " %d" RESET, st_view_size(b->cells[i][j]))
                             : printf(BLUE " %d" RESET, st_view_size(b->cells[i][j]));
            } else {
                color == 'v' ? printf(RED " %c" RESET, TOKEN) : printf(BLUE " %c" RESET, TOKEN);
            }
            printf(WHITE " |" RESET);
        }
        printf("\n");

        printf(WHITE "   +" RESET);
        for (int j = 0; j < b->rows; j++)
            printf(WHITE "---+" RESET);
        printf("\n");
    }

    return 0;
}

void display_turn_start(Player* player) {
    printf("\nVez do jogador %s:\n", player->color);
}

void display_hand_size(int size) {
    printf("\nO tamanho da mao e de: %d\n", size);
}

void display_move_valid() {
    printf("\nJogada válida\n");
}

void display_current_score(Player* p1, Player* p2) {
    printf("Pontuacao atual dos jogadores:\n %s: %d\n %s: %d\n", 
           p1->color, st_view_size(p1->points),
           p2->color, st_view_size(p2->points));
}

void display_game_end_points(Player *winner, int points) {
    printf("Fim de jogo, o jogador %s ganhou com %d pontos!\n", winner->color, points);
}

void display_game_end_singletons(Player *winner, int points) {
    printf("Fim de jogo por singlestons, o jogador %s ganhou com %d pontos!\n", winner->color, points);
}

void display_game_end_withdrawal(Player *winner, int points) {
    printf("Fim de jogo por desistencia, o jogador %s ganhou com %d pontos!\n", winner->color, points);
}

void display_goodbye() {
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");
}