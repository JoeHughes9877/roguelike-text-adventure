# Text-Based RPG Engine in C

A dynamically generated text adventure game engine written in C with SQLite persistence.

## 🚀 Features

- ✨ **Procedural World Generation** – Unique rooms created from templates  
- 🗃️ **SQLite Database** – Save games, items, and world state  
- ⚔️ **Turn-Based Combat** – Battle enemies with stats and equipment  
- 🎒 **Inventory System** – Collect and use items  
- 📜 **Rich Descriptions** – Dynamically generated room narratives  
- 🔧 **Modular Design** – Easy to extend with new features  

## 🧪 Quick Start

### Requirements

- GCC or Clang  
- SQLite3 development libraries  
- GNU Make (optional)

### Installation

```bash
# Clone and build
git clone https://github.com/yourusername/text-rpg-engine.git
cd text-rpg-engine
make

# Run the game
./rpg
```

## 🎮 Game Commands

| Command         | Description                   |
|-----------------|-------------------------------|
| `go [direction]`| Move (north/south/east/west)  |
| `look`          | Examine current room          |
| `take [item]`   | Pick up an item               |
| `use [item]`    | Use an item from inventory    |
| `attack`        | Fight nearby enemies          |
| `inventory`     | View your items               |
| `save`          | Save game progress            |
| `quit`          | Exit the game                 |

## 🗂️ Project Structure

```
text-rpg-engine/
├── src/               # Source files
│   ├── main.c         # Game loop and entry point
│   ├── world.c        # Room generation and navigation  
│   ├── combat.c       # Battle system
│   ├── items.c        # Inventory management
│   └── db.c           # SQLite database interface
├── include/           # Header files
├── data/              # Game assets and database
├── Makefile           # Build configuration
└── README.md          # This file
```

## 🗃️ Database Schema

The SQLite database contains the following tables:

- `rooms` – Generated room instances  
- `templates` – Room blueprints for generation  
- `items` – All game items  
- `players` – Save game data  
- `world` – Global game state  

## 🛣️ Roadmap

- [ ] Quest system  
- [ ] Character progression  
- [ ] Magic/spell system  
- [ ] Better NPC interactions  
- [ ] World map visualization  
