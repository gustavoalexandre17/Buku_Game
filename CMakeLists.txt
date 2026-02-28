cmake_minimum_required(VERSION 3.16)

project(Buku_Game C)

# Padrão da linguagem
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Executável do jogo
add_executable(buku_game
    source/main.c
    source/move.c
    source/domain/player.c
    source/domain/board.c
    source/domain/stack.c
    source/domain/hand.c
    source/domain/game_logic.c
    source/ui/display.c
    source/ui/input.c
)

# Diretório dos headers
target_include_directories(buku_game PRIVATE
    include
    include/domain
    include/ui
)

# Flags de compilação
target_compile_options(buku_game PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Colocar o binário dentro da pasta bin/
set_target_properties(buku_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
