# So Long - Raylib Edition

Este é o projeto **So Long** convertido para utilizar a biblioteca **Raylib**, uma biblioteca simples e fácil de usar para jogos e aplicações multimídia. A conversão foi realizada mantendo a lógica original do jogo, mas otimizando o código para o ambiente da Raylib, substituindo as funções da MinilibX.

## Funcionalidades

*   **Renderização Otimizada:** Utiliza as funções de desenho e texturas da Raylib para uma renderização eficiente.
*   **Controle de Input:** O tratamento de eventos de teclado foi adaptado para o sistema de input da Raylib.
*   **Estrutura de Assets:** O carregamento e descarregamento de texturas (`Texture2D`) são gerenciados pela Raylib.
*   **Lógica de Jogo Original:** A mecânica de movimento, checagem de mapa, coletáveis e inimigos foi preservada.

## Como Compilar e Executar

### Pré-requisitos

Você precisará ter a biblioteca **Raylib** instalada no seu sistema.

**No Linux (Ubuntu/Debian):**

```bash
sudo apt install libraylib-dev
```

Você também precisará da biblioteca `Libft` (assumindo que ela está no diretório `Libft` e contém as funções necessárias, como `ft_strdup`, `ft_strrchr`, `ft_strncmp`, `ft_putstr_fd`, `ft_strjoin`, `get_next_line`, etc.).

### Compilação

1.  Certifique-se de que a `Libft` esteja compilada:
    ```bash
    make -C Libft
    ```
2.  Compile o projeto principal usando o `Makefile` fornecido:
    ```bash
    make
    ```

Isso criará o executável `so_long`.

### Execução

O jogo requer um arquivo de mapa no formato `.ber` como argumento.

```bash
./so_long <caminho/para/seu/mapa.ber>
```

## Controles

| Tecla | Ação |
| :---: | :--- |
| **W** ou **Seta para Cima** | Mover para Cima |
| **S** ou **Seta para Baixo** | Mover para Baixo |
| **A** ou **Seta para Esquerda** | Mover para Esquerda |
| **D** ou **Seta para Direita** | Mover para Direita |
| **ESC** | Sair do Jogo |

## Estrutura do Projeto

| Arquivo | Descrição |
| :--- | :--- |
| `so_long.h` | Arquivo de cabeçalho principal com definições, estruturas (`t_game`, `t_assets`) e protótipos. |
| `so_long.c` | Contém a função `main`, a inicialização da Raylib, o loop principal do jogo (`game_loop`, `update_game`, `draw_game`) e a função de fechamento (`close_program`). |
| `imgs.c` | Funções para carregar (`load_assets`) e descarregar (`unload_assets`) as texturas da Raylib. |
| `render.c` | Funções de desenho (`draw_tile`, `draw_map`) que utilizam as funções de renderização da Raylib. |
| `move.c` | Lógica de movimento do jogador e tratamento de input do teclado (`handle_input`, `move_check`). |
| `animation.c` | Lógica de animação (adaptada para o loop de tempo da Raylib). |
| `check.c` | Funções de checagem de validade do mapa (caracteres, paredes, integridade). |
| `check_solvability.c` | Função para verificar se o mapa é solucionável. |
| `enemy_funct.c` | Lógica de posicionamento e movimento dos inimigos. |
| `maps_funct.c` | Funções para carregar o mapa a partir do arquivo. |
| `Makefile` | Script de compilação adaptado para incluir as flags da Raylib. |
| `Libft/` | Diretório contendo a biblioteca `Libft` (necessária para funções utilitárias). |
| `assets/` | Diretório onde as imagens (`.png` ou outro formato suportado pela Raylib) devem ser colocadas. |

**Nota sobre Assets:** As imagens originais em formato `.xpm` devem ser convertidas para um formato mais moderno e suportado pela Raylib, como `.png`, e colocadas no diretório `assets/`. Os nomes dos arquivos devem corresponder aos utilizados em `imgs.c` (ex: `bg.png`, `chest.png`, `wall.png`, etc.).
