# roguelike text adventure Game

## Overview

A lightweight and modular role-playing game built in C using SQLite for persistent game data management.  
Inspired by classic text adventures and *The Elder Scrolls*, this engine lets you explore dynamically generated rooms, interact with items and engage enemies.

The game is in a **playable state**, although occasional crashes might occur as it’s still a work-in-progress.

## 🚀 How to Run the Game

### Prerequisites
Ensure you have these installed:
- GCC
- Make
- SQLite3

### Quick Start
```bash
git clone https://github.com/yourusername/Text-Based-RPG-Engine.git
cd Text-Based-RPG-Engine
make
./game

```

## 🎮 Game Controls

| Command           | Description                                  |
|-------------------|-------------------------------------         |
| `go north`        | Move your character north                    |
| `go east`         | Move east                                    |
| `go south`        | Move south                                   |
| `go west`         | Move west                                    |
| `look around`     | Examine the current room for items and exits |
| `inventory`       | List the items you are carrying              |
| `take <item>`     | Pick up an item from the room                |
| `drop <item>`     | Drop an item from your inventory             |
| `use <item>`      | Use an item in your inventory                |
| `stats`           | View your current player stats               |
| `engage <enemy>`  | Initiate combat with an enemy in the room    |
| `attack`          | cause damage to an enemy                     |
| `flee`            | attemp to flee from combat                   |

---

## 💡 Things I Have Learned

- Designing a modular game architecture in C with separation of concerns.
- Managing dynamic memory safely in C for strings and custom vector structures.
- Utilizing SQLite to store and query game data such as rooms, items, and enemies.
- Implementing game loops with text parsing for flexible player input.
- Handling dynamic room generation with exits and inventory mechanics.
- Using Makefiles for compiling multi-file C projects efficiently.
- Employing string manipulation and case normalization to handle user commands robustly.

---

## 📄 SQLite Database Schema (Summary)

The game uses SQLite to manage persistent data with the following key tables:

- **room_templates** — Defines room prefixes, core names, base descriptions, and optional features.
- **item_definitions** — Stores all possible items with names, descriptions, and values.
- **enemy_definitions** — Contains enemy stats including health, attack, defense, and XP rewards.
- **room_template_items** — Maps which items appear in which room templates.
- **room_template_enemies** — Maps which enemies appear in which room templates.

This schema supports dynamic room creation with variable items and enemies to enrich gameplay.
