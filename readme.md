# So Long - Versão Corrigida com Raylib

Projeto de jogo 2D top-down desenvolvido em C com a biblioteca gráfica Raylib.

## 🔧 Correções Realizadas

### 1. **Headers Corrigidos**

- Substituído `mlx.h` por `raylib.h`
- Todas as estruturas e funções declaradas corretamente
- Tipos de dados consistentes (Position, Player, Enemy, Map, etc.)

### 2. **Ponteiros e Memória**

- Alocação e liberação de memória corrigida em `map.c`
- Ponteiros de string tratados adequadamente com `strdup()`
- Liberação de memória em `map_free()` e `game_free()`

### 3. **Makefile**

- Flags corrigidas para raylib
- Suporte para Linux e macOS
- Links de bibliotecas corretos

### 4. **Estrutura do Código**

- Separação clara entre módulos
- Funções bem definidas com protótipos no header
- Sistema modular (map, player, enemy, render, input, timer)

## 📦 Instalação

### Linux (Ubuntu/Debian)

```bash
# Instalar dependências
sudo apt update
sudo apt install build-essential git
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

# Instalar Raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
sudo make install
cd ../..
```

### macOS

```bash
# Instalar Homebrew se não tiver
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar Raylib
brew install raylib
```

### Windows (MinGW)

```bash
# Baixar Raylib pré-compilado
# https://github.com/raysan5/raylib/releases

# Extrair e adicionar ao PATH
```

## 🚀 Compilação

```bash
# Clonar o repositório
git clone [seu-repositório]
cd so_long_v2

# Criar diretório de mapas
mkdir -p maps

# Criar mapa de exemplo (level1.ber)
# Use o conteúdo fornecido no arquivo maps/level1.ber

# Compilar
make

# Executar
./so_long maps/level1.ber
```

## 🎮 Controles

| Tecla | Ação                |
| ----- | ------------------- |
| W / ↑ | Mover para cima     |
| S / ↓ | Mover para baixo    |
| A / ← | Mover para esquerda |
| D / → | Mover para direita  |
| R     | Reiniciar nível     |
| ESC   | Sair do jogo        |

## 🗺️ Formato do Mapa (.ber)

```
1111111
1P0C001
1000X01
1C00E01
1111111
```

**Legenda:**

- `1` - Parede
- `0` - Espaço vazio
- `P` - Posição inicial do jogador
- `C` - Coletável
- `E` - Saída
- `X` - Inimigo (opcional)

### Regras do Mapa:

- Deve ser retangular
- Cercado por paredes (`1`)
- Ter exatamente 1 jogador (`P`)
- Ter exatamente 1 saída (`E`)
- Ter pelo menos 1 coletável (`C`)

## 📁 Estrutura do Projeto

```
so_long/
├── includes/
│   └── so_long.h          # Header principal
├── src/
│   ├── main.c             # Ponto de entrada
│   ├── game.c             # Lógica principal
│   ├── map.c              # Carregamento e validação de mapas
│   ├── player.c           # Controle do jogador
│   ├── enemy.c            # IA dos inimigos
│   ├── render.c           # Sistema de renderização
│   ├── input.c            # Tratamento de entrada
│   └── timer.c            # Sistema de timer
├── maps/
│   └── level1.ber         # Mapa de exemplo
├── Makefile               # Script de compilação
└── README.md              # Este arquivo
```

## 🐛 Solução de Problemas

### Erro: "raylib.h not found"

```bash
# Linux
sudo ldconfig
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# macOS
brew reinstall raylib
```

### Erro: "undefined reference to 'InitWindow'"

```bash
# Verificar se raylib está instalada corretamente
pkg-config --libs raylib

# Se não funcionar, reinstalar raylib
```

### Erro ao carregar mapa

- Verifique se o arquivo .ber existe
- Confirme que o mapa segue as regras (retangular, cercado por paredes, etc.)
- Verifique permissões do arquivo

## 🎯 Objetivos do Jogo

1. Coletar todos os itens (`C`) no mapa
2. Evitar os inimigos (`X`)
3. Chegar à saída (`E`)
4. Completar no menor tempo e movimentos possíveis

## 📝 Notas Técnicas

- **Linguagem**: C (C99)
- **Biblioteca Gráfica**: Raylib 5.0+
- **FPS**: 60
- **Tamanho do Tile**: 64x64 pixels

## 🔄 Diferenças da versão MiniLibX

- Substituída MiniLibX por Raylib (mais portável)
- Sistema de renderização simplificado
- Melhor gerenciamento de texturas
- Suporte nativo para Windows, Linux e macOS

## 👨‍💻 Desenvolvimento

Para adicionar novos recursos:

1. **Novos tiles**: Edite `TileType` enum em `so_long.h`
2. **Nova lógica**: Adicione em `game.c` ou crie novo módulo
3. **Texturas**: Carregue em `game_load_textures()`
4. **Renderização**: Modifique `render_game()` em `render.c`

## 📄 Licença

Projeto educacional desenvolvido como parte do currículo da 42.

---

**Autor**: Leonardo Santander Nycz  
**GitHub**: @SantanderNycz
