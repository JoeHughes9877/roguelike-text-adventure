PRAGMA foreign_keys = ON;

-- 1. room_templates
-- Stores the blueprints for generating dynamic rooms.
CREATE TABLE IF NOT EXISTS room_templates (
    template_id INTEGER PRIMARY KEY,
    name_prefix TEXT NOT NULL,
    name_core TEXT NOT NULL,
    base_description TEXT NOT NULL,
    possible_features TEXT,
    possible_item_def_ids TEXT,
    possible_enemy_def_ids TEXT
);

-- 2. item_definitions
-- Defines all types of items available in the game.
CREATE TABLE IF NOT EXISTS item_definitions (
    item_def_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    description TEXT,
    type TEXT NOT NULL,
    value INTEGER DEFAULT 0
);

-- 3. enemy_definitions
-- Defines all types of enemies available in the game.
CREATE TABLE IF NOT EXISTS enemy_definitions (
    enemy_def_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    description TEXT,
    base_health INTEGER NOT NULL,
    base_attack INTEGER NOT NULL,
    base_defense INTEGER NOT NULL,
    xp_reward INTEGER DEFAULT 0
);

-- 4. filler_words
-- Stores dynamic phrases and words for generating varied room descriptions.
CREATE TABLE IF NOT EXISTS filler_words (
    word_id INTEGER PRIMARY KEY,
    type TEXT NOT NULL,
    word TEXT NOT NULL
);