#include "domain/board.h"
#include "ui/display.h"

int show_board(Board *b) {
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