# 🧩 So_long — A 2D Adventure Game in C

A minimalist top-down 2D game built entirely in **C** with the **MiniLibX** graphics library.  
Originally developed as part of the **42 curriculum**, this version includes extended features such as enemy AI, multiple levels, and a built-in timer system.

---

## 🚀 Features

- 🧍‍♂️ **Player Movement** — Smooth movement in four directions using arrow keys.
- 🪙 **Collectibles** — Gather all items to unlock the exit.
- 🧟 **Enemies** — Avoid moving enemies that chase or patrol around the map.
- ⏱️ **Timer System** — Displays elapsed time since the start of the level.
- 🌍 **Multiple Levels** — Automatically loads the next map when a level is completed.
- 🗺️ **Custom Map Parser** — Validates `.ber` map files for errors before loading.
- 💥 **Game Over & Victory Screens** — Dedicated scenes for win and loss conditions.
- 🧰 **Modular Structure** — Clean separation between rendering, input, game logic, and map handling.

---

## 🎮 Gameplay

Your goal is simple:  
Collect all items, avoid enemies, and reach the exit to move to the next level.

| Key     | Action                    |
| ------- | ------------------------- |
| `W / ↑` | Move Up                   |
| `A / ←` | Move Left                 |
| `S / ↓` | Move Down                 |
| `D / →` | Move Right                |
| `R`     | Restart the current level |
| `ESC`   | Quit the game             |

---

## 🗺️ Maps

Each level is defined in a `.ber` file located inside the `maps/` folder.  
Example:

```bash
	111111
	1P0C01
	1010E1
	100001
	111111
```

Legend:

- `1` → Wall
- `0` → Empty space
- `P` → Player start
- `C` → Collectible
- `E` → Exit
- `X` → Enemy _(optional)_

To create new levels, simply add more `.ber` files (e.g. `level1.ber`, `level2.ber`, …).

---

## 🧱 Building the Game

Clone the repository and compile with `make`:

````bash
git clone https://github.com/<yourusername>/so_long.git
cd so_long
make
./so_long maps/level1.ber

- Make sure MiniLibX is properly installed on your system.
-- For Linux:

```bash
	sudo apt install libmlx-dev libxext-dev libx11-dev
```

## 🧩 Project Structure

```bash
so_long/
├── includes/
│   └── so_long.h
├── src/
│   ├── main.c
│   ├── render.c
│   ├── input.c
│   ├── map.c
│   ├── enemy.c
│   ├── timer.c
│   └── level_manager.c
├── assets/
│   ├── player/
│   ├── enemy/
│   ├── tiles/
│   └── ui/
└── maps/
    ├── level1.ber
    ├── level2.ber
    └── ...
```

## 🧠 Technical Highlights

- Language: C

- Graphics: MiniLibX (X11)

- Paradigm: Event-driven rendering loop

- Memory Safety: Manual management with error handling for leaks

- Cross-map logic: Loads levels dynamically via array of file paths

## 🏁 Next Steps

- Planned or possible future upgrades:

-- 🎨 Animated tiles and smoother transitions between maps

-- 🧭 Dynamic minimap system

-- 🎵 Background music and sound effects

-- ⚙️ Map editor (CLI or graphical)

-- 🧮 Enemy pathfinding with BFS / A\*

## 👨‍💻 Author

- Leonardo Santander Nycz
  --🎓 Student at 42 Porto

- 💻 GitHub: SantanderNycz

- 🎶 Music Projects: Bemvirá
````
