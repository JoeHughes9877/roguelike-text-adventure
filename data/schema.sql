PRAGMA foreign_keys = ON;

-- Create tables
CREATE TABLE IF NOT EXISTS room_templates (
    template_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name_prefix TEXT NOT NULL,
    name_core TEXT NOT NULL,
    base_description TEXT NOT NULL,
    possible_features TEXT
);

CREATE TABLE IF NOT EXISTS item_definitions (
    item_def_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    description TEXT,
    type TEXT NOT NULL,
    value INTEGER DEFAULT 0
);

CREATE TABLE IF NOT EXISTS enemy_definitions (
    enemy_def_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    description TEXT,
    base_health INTEGER NOT NULL,
    base_attack INTEGER NOT NULL,
    base_defense INTEGER NOT NULL,
    xp_reward INTEGER DEFAULT 0
);

CREATE TABLE IF NOT EXISTS filler_words (
    word_id INTEGER PRIMARY KEY AUTOINCREMENT,
    type TEXT NOT NULL,
    word TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS room_template_items (
    template_id INTEGER NOT NULL,
    item_def_id INTEGER NOT NULL,
    PRIMARY KEY (template_id, item_def_id),
    FOREIGN KEY (template_id) REFERENCES room_templates(template_id) ON DELETE CASCADE,
    FOREIGN KEY (item_def_id) REFERENCES item_definitions(item_def_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS room_template_enemies (
    template_id INTEGER NOT NULL,
    enemy_def_id INTEGER NOT NULL,
    PRIMARY KEY (template_id, enemy_def_id),
    FOREIGN KEY (template_id) REFERENCES room_templates(template_id) ON DELETE CASCADE,
    FOREIGN KEY (enemy_def_id) REFERENCES enemy_definitions(enemy_def_id) ON DELETE CASCADE
);

-- Insert room templates
INSERT INTO room_templates (name_prefix, name_core, base_description, possible_features) VALUES
('Damp', 'Prison Cell', 'A small, dark cell with cold stone walls dampened by moisture seeping through the cracks. Rusty iron bars block the only exit.', 'moss patches,dripping water,rusted chains'),
('Collapsed', 'Sewers', 'Narrow tunnels filled with stagnant water and scattered debris. The stench of waste is overpowering.', 'rat droppings,broken pipes,echoing drips'),
('Echoing', 'Underground Cavern', 'A vast cavern beneath the city, lit faintly by glowing fungi clinging to the rocky walls.', 'glowing mushrooms,stalactites,underground stream'),
('Forgotten', 'Smuggler''s Hideout', 'A hidden room cluttered with crates, barrels, and makeshift beds — a remnant of illicit deals.', 'rusty locks,old maps,barrels of supplies'),
('Silent', 'Ancient Catacombs', 'Long-forgotten burial chambers lined with weathered sarcophagi and faded murals.', 'dusty bones,faded runes,cobwebbed corners');

-- Insert items
INSERT INTO item_definitions (name, description, type, value) VALUES
('Rusty Iron Key', 'A corroded key, possibly unlocking some forgotten door.', 'quest', 0),
('Cracked Healing Potion', 'A potion that restores a small amount of health, though some of it may have leaked.', 'consumable', 10),
('Dagger of Shadows', 'A slender blade that seems to absorb light.', 'weapon', 75),
('Torch', 'A wooden torch to light the dark tunnels.', 'utility', 5),
('Smuggler''s Pouch', 'A small pouch containing a few gold coins and odd trinkets.', 'misc', 30),
('Ancient Coin', 'A tarnished coin bearing the Imperial City crest, centuries old.', 'quest', 0);

-- Insert enemies
INSERT INTO enemy_definitions (name, description, base_health, base_attack, base_defense, xp_reward) VALUES
('Sewer Rat', 'A large, diseased rat scurrying through the tunnels.', 15, 3, 1, 5),
('Cave Spider', 'A venomous spider lurking in the dark corners.', 25, 6, 2, 15),
('Imperial Guard (Unconscious)', 'A fallen guard, still clutching his sword.', 40, 7, 4, 25),
('Smuggler', 'A desperate man armed with a rusty knife, hiding from the law.', 35, 5, 3, 20),
('Ancient Skeleton', 'Bones reanimated by forgotten magics, wielding a rusted sword.', 45, 8, 5, 30);

-- Link items to rooms
INSERT INTO room_template_items (template_id, item_def_id) VALUES
(1, 1),  -- Rusty Iron Key in Damp Prison Cell
(1, 4),  -- Torch in Damp Prison Cell
(2, 2),  -- Cracked Healing Potion in Collapsed Sewers
(3, 6),  -- Ancient Coin in Echoing Underground Cavern
(4, 5),  -- Smuggler's Pouch in Forgotten Smuggler's Hideout
(4, 4),  -- Torch in Forgotten Smuggler's Hideout
(5, 6);  -- Ancient Coin in Silent Ancient Catacombs

-- Link enemies to rooms
INSERT INTO room_template_enemies (template_id, enemy_def_id) VALUES
(1, 3),  -- Imperial Guard (Unconscious) in Damp Prison Cell
(2, 1),  -- Sewer Rat in Collapsed Sewers
(2, 2),  -- Cave Spider in Collapsed Sewers
(3, 5),  -- Ancient Skeleton in Echoing Underground Cavern
(4, 4),  -- Smuggler in Forgotten Smuggler's Hideout
