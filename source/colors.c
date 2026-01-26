#include "../include/colors.h"
#include <stdio.h>
#include <stdlib.h>

Colors *create_colors() {
    Colors *new_colors = (Colors *)malloc(sizeof(Colors));

    new_colors->colorLightSquares = WHITE;
    new_colors->colorDarkSquares = WHITE;
    new_colors->colorBoard = WHITE;

    return new_colors;
}
