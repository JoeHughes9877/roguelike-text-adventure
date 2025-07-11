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

-- Inserts for room_templates
INSERT INTO room_templates (name_prefix, name_core, base_description, possible_features) VALUES
('Damp', 'Prison Cell', 'A small, cramped stone cell, smelling of mildew and despair. A single, barred window offers a sliver of light.', 'Straw mat, Rusty bucket, Graffiti on walls, Shackles'),
('Dark', 'Dungeon Corridor', 'A long, narrow stone corridor, lit by flickering torchlight. The air is cold and heavy.', 'Iron grates, Cobwebs, Dripping water, Guard patrols'),
('Torture', 'Chamber', 'A grim chamber filled with various implements of pain and suffering. The air is thick with a metallic tang.', 'Rack, Iron maiden, Bloodstains, Chains'),
('Guard', 'Barracks', 'A utilitarian room with several cots and weapon racks, used by the Imperial Legion guards.', 'Unmade beds, Training dummies, Armor stands, Mess table'),
('Sewage', 'Tunnel', 'A foul-smelling, low-ceilinged tunnel, through which murky water flows sluggishly.', 'Grime, Rats, Broken pipes, Hidden alcoves'),
('Storage', 'Room', 'A dusty storage room, filled with forgotten crates and barrels. A faint smell of rot lingers in the air.', 'Empty crates, Broken tools, Old provisions, Loose floorboards'),
('Execution', 'Platform', 'A raised stone platform in a larger chamber, stained dark. The air feels heavy and final.', 'Executioner''s axe, Wooden block, Spectator area, Iron cage'),
('Secret', 'Passage', 'A hidden passage, barely wide enough for one person, leading away from the main dungeon.', 'Loose stones, Faint breeze, Whispering sounds, Hidden lever'),
('Underground', 'River Bank', 'A muddy bank beside a dark, underground river, its waters flowing swiftly into the unknown.', 'Slippery rocks, Waterlogged debris, Faint current, Mossy walls'),
('Collapsed', 'Section', 'A part of the dungeon where the ceiling has caved in, leaving a dangerous pile of rubble.', 'Broken timbers, Falling dust, Trapped bodies, Narrow crawlspace'),
('Ancient', 'Ayleid Vault', 'A surprisingly well-preserved Ayleid vault, hidden deep beneath the city, filled with strange energies.', 'Glowing runes, Pedestals, Elaborate carvings, Sealed sarcophagi'),
('Flooded', 'Sub-level', 'A lower section of the dungeon completely submerged in cold, dark water, accessible only by swimming.', 'Waterlogged chests, Skeletal remains, Murky visibility, Strong currents'),
('Kitchen', 'Pantry', 'A small, damp pantry used for storing meager prison rations, filled with the smell of stale bread.', 'Rotten food, Empty shelves, Vermin, Rusty knives'),
('Chapel', 'Remains', 'The ruined remains of a small chapel, perhaps used by prisoners in times long past. The air is surprisingly calm.', 'Broken altar, Faded frescoes, Empty pews, Fallen crucifix'),
('Abandoned', 'Guard Post', 'A small, deserted guard post, long forgotten, with a single, rusted lantern hanging precariously.', 'Rusted armor, Empty wine bottles, Crumpled maps, Dusty logbook'),
('Musty', 'Library Section', 'A section of the dungeon repurposed as a small, forgotten library, filled with decaying scrolls and books.', 'Rotten books, Crumbling shelves, Ancient maps, Ink stains'),
('Grim', 'Interrogation Room', 'A small, soundproofed room designed for questioning, with a heavy, bolted door.', 'Stained chair, Iron rings, Faint screams, Rusty instruments'),
('Waterlogged', 'Storage Cellar', 'A cellar filled with barrels and crates, now partially submerged in stagnant, cold water.', 'Floating debris, Slimy walls, Empty bottles, Waterlogged sacks'),
('Echoing', 'Well Chamber', 'A large, circular chamber dominated by a deep, dark well. The sound of dripping water echoes loudly.', 'Stone well, Mossy walls, Discarded ropes, Faint splashing'),
('Crumbling', 'Watchtower Base', 'The base of an old watchtower, now mostly rubble, offering a limited view through cracks in the stone.', 'Loose stones, Broken ladder, Bird nests, Cold drafts'),
('Makeshift', 'Infirmary', 'A crude infirmary set up by prisoners, with stained bandages and basic medical supplies.', 'Dirty cots, Rusty medical tools, Dried blood, Empty vials'),
('Collapsed', 'Tunnel Entrance', 'The blocked entrance to a tunnel, with debris making passage difficult or impossible.', 'Heavy rocks, Splintered wood, Fresh dirt, Faint light from beyond'),
('Smuggler''s', 'Cache', 'A hidden alcove used by smugglers, containing a few forgotten goods and the lingering scent of skooma.', 'Empty sacks, Hidden compartment, Illicit goods, Faint footprints'),
('Flooded', 'Passage', 'A narrow passage, completely filled with waist-deep, freezing water, making movement slow.', 'Slippery floor, Water stains, Algae, Murky depths'),
('Subterranean', 'Garden', 'A strange, small garden grown in the damp earth, lit by bioluminescent fungi.', 'Unusual plants, Glowing mushrooms, Damp soil, Strange insects'),
('Forgotten', 'Armory', 'A long-abandoned armory, most weapons rusted or broken, but a few might still be salvageable.', 'Rusted weapons, Broken armor, Empty weapon racks, Dust covers'),
('Dank', 'Holding Pen', 'A small, enclosed pen used for temporary holding, with straw and waste on the floor.', 'Iron bars, Foul odor, Scratches on walls, Discarded rags'),
('Mysterious', 'Shrine', 'A small, hidden shrine dedicated to an unknown deity, radiating a faint, unsettling aura.', 'Crude altar, Unlit candles, Strange symbols, Offerings'),
('Overgrown', 'Cell Block', 'A section of prison cells that has been abandoned for so long that vegetation has begun to reclaim it.', 'Vines, Cracked walls, Moss-covered bars, Broken doors'),
('Secret', 'Workshop', 'A clandestine workshop used by a clever prisoner, with tools and half-finished contraptions.', 'Work bench, Tools, Scraps of metal, Blueprints'),
('Grimy', 'Kitchen', 'A disused kitchen area, covered in layers of grease and dirt, with broken cooking implements.', 'Rusty pots, Broken stove, Food scraps, Vermin nests'),
('Chilling', 'Morgue', 'A cold, dark room used for storing the deceased, with stone slabs and a pervasive scent of death.', 'Stone slabs, Shrouded figures, Cold air, Faint whispers');


-- Inserts for item_definitions
INSERT INTO item_definitions (name, description, type, value) VALUES
('Iron Longsword', 'A standard, well-worn iron longsword. Good for basic combat.', 'Weapon', 50),
('Leather Cuirass', 'A simple leather chestpiece, offering basic protection.', 'Armor', 75),
('Potion of Healing', 'A small vial containing a shimmering red liquid. Restores health.', 'Consumable', 25),
('Lockpick', 'A slender piece of metal designed for picking locks.', 'Tool', 5),
('Gold Coin', 'A single, gleaming gold coin.', 'Currency', 1),
('Scroll of Fireball', 'A magical scroll that can unleash a burst of flame.', 'Scroll', 150),
('Rusty Key', 'A small, rusty key. It might open something nearby.', 'Quest Item', 0),
('Wolf Pelt', 'The hide of a wolf, useful for crafting or selling.', 'Misc', 10),
('Sweetroll', 'A delicious, sugary pastry. Restores a small amount of stamina.', 'Food', 2),
('Daedric Dagger', 'A wickedly curved dagger made of dark, otherworldly metal. Emits a faint hum.', 'Weapon', 500),
('Ayleid Welkynd Stone', 'A glowing blue crystal, once used by the Ayleids to restore magicka.', 'Misc', 200),
('Fine Steel Helmet', 'A well-crafted steel helmet, polished to a shine.', 'Armor', 120),
('Poison of Weakness', 'A dark, viscous liquid that weakens an enemy upon contact.', 'Consumable', 40),
('Prisoner''s Ragged Trousers', 'Torn and stained trousers, offering no protection.', 'Armor', 0),
('Shiv', 'A crude, sharpened piece of metal. Barely a weapon.', 'Weapon', 5),
('Moldy Bread', 'A hard, moldy piece of bread. Edible, but barely.', 'Food', 1),
('Imperial Guard Shield', 'A sturdy shield bearing the emblem of the Imperial Legion.', 'Armor', 100),
('Torch', 'A wooden stick with a burning rag, providing light.', 'Tool', 3),
('Empty Wine Bottle', 'A discarded glass bottle. Could be useful for something.', 'Misc', 0),
('Journal Entry', 'A torn page from a prisoner''s journal, detailing a secret.', 'Quest Item', 0),
('Iron Dagger', 'A basic, short blade, good for close quarters.', 'Weapon', 20),
('Leather Boots', 'Simple leather boots, offering minimal protection.', 'Armor', 15),
('Minor Healing Potion', 'A very small vial of red liquid. Restores a tiny bit of health.', 'Consumable', 10),
('Old Map Fragment', 'A piece of a torn map, showing a small section of the dungeon.', 'Quest Item', 0),
('Silver Ring', 'A plain silver ring, possibly valuable.', 'Jewelry', 30),
('Waterlogged Book', 'A book ruined by water, its pages unreadable.', 'Misc', 0),
('Lockpicking Guide', 'A small, worn book with diagrams on lockpicking.', 'Book', 10),
('Rusty Shovel', 'A heavy, rusty shovel. Could be used as a blunt weapon.', 'Tool', 8),
('Bag of Gold (Small)', 'A small pouch containing a few gold coins.', 'Currency', 10),
('Bone Meal', 'Ground bones, used in alchemy or necromancy.', 'Alchemy Ingredient', 5);


-- Inserts for enemy_definitions
INSERT INTO enemy_definitions (name, description, base_health, base_attack, base_defense, xp_reward) VALUES
('Bandit', 'A common highwayman, clad in leather and wielding a crude weapon.', 30, 8, 5, 15),
('Scamp', 'A small, mischievous Daedra from Oblivion, prone to cackling.', 20, 5, 3, 10),
('Zombie', 'The reanimated corpse of a fallen adventurer, slow but relentless.', 40, 7, 6, 20),
('Wolf', 'A wild canine, aggressive and territorial.', 25, 6, 4, 12),
('Clannfear', 'A reptilian Daedra with a sharp frill and powerful claws.', 50, 12, 8, 30),
('Skeleton', 'The skeletal remains of a warrior, animated by dark magic.', 35, 9, 7, 18),
('Goblin', 'A small, green-skinned creature known for its tribal behavior and crude weapons.', 28, 7, 4, 14),
('Ogre', 'A large, brutish creature with immense strength and thick hide.', 80, 15, 10, 50),
('Dremora Kynval', 'A lesser Daedra, but still a formidable warrior from Mehrunes Dagon''s legions.', 60, 10, 9, 40),
('Imperial Guard', 'A disciplined soldier of the Imperial Legion, armed with steel.', 45, 10, 8, 25),
('Dungeon Rat', 'A large, aggressive rat, common in the dark corners of the dungeon.', 15, 4, 2, 5),
('Feral Dog', 'A starving, wild dog that has found its way into the dungeon.', 22, 5, 3, 8),
('Ghostly Apparition', 'A translucent, ethereal spirit of a former prisoner or guard.', 30, 7, 5, 20),
('Fallen Imperial Mage', 'The reanimated corpse of an Imperial battlemage, still crackling with dark energy.', 55, 11, 7, 35),
('Giant Spider', 'A monstrous arachnid, its web-filled lair suggests a dangerous encounter.', 38, 9, 6, 22),
('Hungry Prisoner', 'A desperate, emaciated prisoner, driven to violence by starvation.', 25, 6, 4, 10),
('Sewer Croc', 'A large, aggressive crocodile dwelling in the dungeon''s murky waters.', 42, 10, 7, 28),
('Corrupted Sentry', 'An ancient Ayleid construct, now corrupted and hostile.', 65, 13, 11, 45);


-- Inserts for room_template_enemies (linking enemies to room templates)
-- Assuming room_template_id 1 is 'Damp Prison Cell', 2 is 'Dark Dungeon Corridor', etc.
-- Assuming enemy_def_id 1 is 'Bandit', 2 is 'Scamp', 3 is 'Zombie', 4 is 'Wolf', 5 is 'Clannfear', 6 is 'Skeleton', 7 is 'Goblin', 8 is 'Ogre', 9 is 'Dremora Kynval', 10 is 'Imperial Guard', 11 is 'Dungeon Rat', 12 is 'Feral Dog', 13 is 'Ghostly Apparition', 14 is 'Fallen Imperial Mage', 15 is 'Giant Spider', 16 is 'Hungry Prisoner', 17 is 'Sewer Croc', 18 is 'Corrupted Sentry'
INSERT INTO room_template_enemies (template_id, enemy_def_id) VALUES
(2, 1),   -- Dungeon Corridor: Bandit
(2, 6),   -- Dungeon Corridor: Skeleton
(2, 10),  -- Dungeon Corridor: Imperial Guard
(3, 3),   -- Torture Chamber: Zombie
(3, 16),  -- Torture Chamber: Hungry Prisoner
(4, 10),  -- Guard Barracks: Imperial Guard
(5, 7),   -- Sewage Tunnel: Goblin
(5, 4),   -- Sewage Tunnel: Wolf
(5, 11),  -- Sewage Tunnel: Dungeon Rat
(5, 17),  -- Sewage Tunnel: Sewer Croc
(6, 11),  -- Storage Room: Dungeon Rat
(6, 12),  -- Storage Room: Feral Dog
(7, 10),  -- Execution Platform: Imperial Guard
(10, 3),  -- Collapsed Section: Zombie
(10, 6),  -- Collapsed Section: Skeleton
(11, 13), -- Ancient Ayleid Vault: Ghostly Apparition
(11, 18), -- Ancient Ayleid Vault: Corrupted Sentry
(12, 3),  -- Flooded Sub-level: Zombie
(12, 17), -- Flooded Sub-level: Sewer Croc
(13, 11), -- Kitchen Pantry: Dungeon Rat
(14, 13), -- Chapel Remains: Ghostly Apparition
(15, 10), -- Abandoned Guard Post: Imperial Guard (patrolling nearby)
(16, 13), -- Musty Library Section: Ghostly Apparition
(17, 16), -- Grim Interrogation Room: Hungry Prisoner
(18, 11), -- Waterlogged Storage Cellar: Dungeon Rat
(19, 11), -- Echoing Well Chamber: Dungeon Rat
(20, 12), -- Crumbling Watchtower Base: Feral Dog
(21, 16), -- Makeshift Infirmary: Hungry Prisoner
(22, 1),  -- Collapsed Tunnel Entrance: Bandit
(23, 1),  -- Smuggler's Cache: Bandit
(24, 17), -- Flooded Passage: Sewer Croc
(25, 15), -- Subterranean Garden: Giant Spider
(26, 6),  -- Forgotten Armory: Skeleton
(27, 16), -- Dank Holding Pen: Hungry Prisoner
(28, 13), -- Mysterious Shrine: Ghostly Apparition
(29, 3),  -- Overgrown Cell Block: Zombie
(30, 16), -- Secret Workshop: Hungry Prisoner
(31, 11), -- Grimy Kitchen: Dungeon Rat
(32, 3),  -- Chilling Morgue: Zombie
(32, 13); -- Chilling Morgue: Ghostly Apparition