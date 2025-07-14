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
('damp', 'prison cell', 'a small, cramped stone cell, smelling of mildew and despair. a single, barred window offers a sliver of light.', 'straw mat, rusty bucket, graffiti on walls, shackles'),
('dark', 'dungeon corridor', 'a long, narrow stone corridor, lit by flickering torchlight. the air is cold and heavy.', 'iron grates, cobwebs, dripping water, guard patrols'),
('torture', 'chamber', 'a grim chamber filled with various implements of pain and suffering. the air is thick with a metallic tang.', 'rack, iron maiden, bloodstains, chains'),
('guard', 'barracks', 'a utilitarian room with several cots and weapon racks, used by the imperial legion guards.', 'unmade beds, training dummies, armor stands, mess table'),
('sewage', 'tunnel', 'a foul-smelling, low-ceilinged tunnel, through which murky water flows sluggishly.', 'grime, rats, broken pipes, hidden alcoves'),
('storage', 'room', 'a dusty storage room, filled with forgotten crates and barrels. a faint smell of rot lingers in the air.', 'empty crates, broken tools, old provisions, loose floorboards'),
('execution', 'platform', 'a raised stone platform in a larger chamber, stained dark. the air feels heavy and final.', 'executioner''s axe, wooden block, spectator area, iron cage'),
('secret', 'passage', 'a hidden passage, barely wide enough for one person, leading away from the main dungeon.', 'loose stones, faint breeze, whispering sounds, hidden lever'),
('underground', 'river bank', 'a muddy bank beside a dark, underground river, its waters flowing swiftly into the unknown.', 'slippery rocks, waterlogged debris, faint current, mossy walls'),
('collapsed', 'section', 'a part of the dungeon where the ceiling has caved in, leaving a dangerous pile of rubble.', 'broken timbers, falling dust, trapped bodies, narrow crawlspace'),
('ancient', 'ayleid vault', 'a surprisingly well-preserved ayleid vault, hidden deep beneath the city, filled with strange energies.', 'glowing runes, pedestals, elaborate carvings, sealed sarcophagi'),
('flooded', 'sub-level', 'a lower section of the dungeon completely submerged in cold, dark water, accessible only by swimming.', 'waterlogged chests, skeletal remains, murky visibility, strong currents'),
('kitchen', 'pantry', 'a small, damp pantry used for storing meager prison rations, filled with the smell of stale bread.', 'rotten food, empty shelves, vermin, rusty knives'),
('chapel', 'remains', 'the ruined remains of a small chapel, perhaps used by prisoners in times long past. the air is surprisingly calm.', 'broken altar, faded frescoes, empty pews, fallen crucifix'),
('abandoned', 'guard post', 'a small, deserted guard post, long forgotten, with a single, rusted lantern hanging precariously.', 'rusted armor, empty wine bottles, crumpled maps, dusty logbook'),
('musty', 'library section', 'a section of the dungeon repurposed as a small, forgotten library, filled with decaying scrolls and books.', 'rotten books, crumbling shelves, ancient maps, ink stains'),
('grim', 'interrogation room', 'a small, soundproofed room designed for questioning, with a heavy, bolted door.', 'stained chair, iron rings, faint screams, rusty instruments'),
('waterlogged', 'storage cellar', 'a cellar filled with barrels and crates, now partially submerged in stagnant, cold water.', 'floating debris, slimy walls, empty bottles, waterlogged sacks'),
('echoing', 'well chamber', 'a large, circular chamber dominated by a deep, dark well. the sound of dripping water echoes loudly.', 'stone well, mossy walls, discarded ropes, faint splashing'),
('crumbling', 'watchtower base', 'the base of an old watchtower, now mostly rubble, offering a limited view through cracks in the stone.', 'loose stones, broken ladder, bird nests, cold drafts'),
('makeshift', 'infirmary', 'a crude infirmary set up by prisoners, with stained bandages and basic medical supplies.', 'dirty cots, rusty medical tools, dried blood, empty vials'),
('collapsed', 'tunnel entrance', 'the blocked entrance to a tunnel, with debris making passage difficult or impossible.', 'heavy rocks, splintered wood, fresh dirt, faint light from beyond'),
('smuggler''s', 'cache', 'a hidden alcove used by smugglers, containing a few forgotten goods and the lingering scent of skooma.', 'empty sacks, hidden compartment, illicit goods, faint footprints'),
('flooded', 'passage', 'a narrow passage, completely filled with waist-deep, freezing water, making movement slow.', 'slippery floor, water stains, algae, murky depths'),
('subterranean', 'garden', 'a strange, small garden grown in the damp earth, lit by bioluminescent fungi.', 'unusual plants, glowing mushrooms, damp soil, strange insects'),
('forgotten', 'armory', 'a long-abandoned armory, most weapons rusted or broken, but a few might still be salvageable.', 'rusted weapons, broken armor, empty weapon racks, dust covers'),
('dank', 'holding pen', 'a small, enclosed pen used for temporary holding, with straw and waste on the floor.', 'iron bars, foul odor, scratches on walls, discarded rags'),
('mysterious', 'shrine', 'a small, hidden shrine dedicated to an unknown deity, radiating a faint, unsettling aura.', 'crude altar, unlit candles, strange symbols, offerings'),
('overgrown', 'cell block', 'a section of prison cells that has been abandoned for so long that vegetation has begun to reclaim it.', 'vines, cracked walls, moss-covered bars, broken doors'),
('secret', 'workshop', 'a clandestine workshop used by a clever prisoner, with tools and half-finished contraptions.', 'work bench, tools, scraps of metal, blueprints'),
('grimy', 'kitchen', 'a disused kitchen area, covered in layers of grease and dirt, with broken cooking implements.', 'rusty pots, broken stove, food scraps, vermin nests'),
('chilling', 'morgue', 'a cold, dark room used for storing the deceased, with stone slabs and a pervasive scent of death.', 'stone slabs, shrouded figures, cold air, faint whispers');


-- Inserts for item_definitions
INSERT INTO item_definitions (name, description, type, value) VALUES
('iron longsword', 'a standard, well-worn iron longsword. good for basic combat.', 'weapon', 50),
('leather cuirass', 'a simple leather chestpiece, offering basic protection.', 'armor', 75),
('potion of healing', 'a small vial containing a shimmering red liquid. restores health.', 'consumable', 25),
('lockpick', 'a slender piece of metal designed for picking locks.', 'tool', 5),
('gold coin', 'a single, gleaming gold coin.', 'currency', 1),
('scroll of fireball', 'a magical scroll that can unleash a burst of flame.', 'scroll', 150),
('rusty key', 'a small, rusty key. it might open something nearby.', 'quest item', 0),
('wolf pelt', 'the hide of a wolf, useful for crafting or selling.', 'misc', 10),
('sweetroll', 'a delicious, sugary pastry. restores a small amount of stamina.', 'food', 2),
('daedric dagger', 'a wickedly curved dagger made of dark, otherworldly metal. emits a faint hum.', 'weapon', 500),
('ayleid welkynd stone', 'a glowing blue crystal, once used by the ayleids to restore magicka.', 'misc', 200),
('fine steel helmet', 'a well-crafted steel helmet, polished to a shine.', 'armor', 120),
('poison of weakness', 'a dark, viscous liquid that weakens an enemy upon contact.', 'consumable', 40),
('prisoner''s ragged trousers', 'torn and stained trousers, offering no protection.', 'armor', 0),
('shiv', 'a crude, sharpened piece of metal. barely a weapon.', 'weapon', 5),
('moldy bread', 'a hard, moldy piece of bread. edible, but barely.', 'food', 1),
('imperial guard shield', 'a sturdy shield bearing the emblem of the imperial legion.', 'armor', 100),
('torch', 'a wooden stick with a burning rag, providing light.', 'tool', 3),
('empty wine bottle', 'a discarded glass bottle. could be useful for something.', 'misc', 0),
('journal entry', 'a torn page from a prisoner''s journal, detailing a secret.', 'quest item', 0),
('iron dagger', 'a basic, short blade, good for close quarters.', 'weapon', 20),
('leather boots', 'simple leather boots, offering minimal protection.', 'armor', 15),
('minor healing potion', 'a very small vial of red liquid. restores a tiny bit of health.', 'consumable', 10),
('old map fragment', 'a piece of a torn map, showing a small section of the dungeon.', 'quest item', 0),
('silver ring', 'a plain silver ring, possibly valuable.', 'jewelry', 30),
('waterlogged book', 'a book ruined by water, its pages unreadable.', 'misc', 0),
('lockpicking guide', 'a small, worn book with diagrams on lockpicking.', 'book', 10),
('rusty shovel', 'a heavy, rusty shovel. could be used as a blunt weapon.', 'tool', 8),
('bag of gold (small)', 'a small pouch containing a few gold coins.', 'currency', 10),
('bone meal', 'ground bones, used in alchemy or necromancy.', 'alchemy ingredient', 5);


-- Inserts for enemy_definitions
INSERT INTO enemy_definitions (name, description, base_health, base_attack, base_defense, xp_reward) VALUES
('bandit', 'a common highwayman, clad in leather and wielding a crude weapon.', 30, 8, 5, 15),
('scamp', 'a small, mischievous daedra from oblivion, prone to cackling.', 20, 5, 3, 10),
('zombie', 'the reanimated corpse of a fallen adventurer, slow but relentless.', 40, 7, 6, 20),
('wolf', 'a wild canine, aggressive and territorial.', 25, 6, 4, 12),
('clannfear', 'a reptilian daedra with a sharp frill and powerful claws.', 50, 12, 8, 30),
('skeleton', 'the skeletal remains of a warrior, animated by dark magic.', 35, 9, 7, 18),
('goblin', 'a small, green-skinned creature known for its tribal behavior and crude weapons.', 28, 7, 4, 14),
('ogre', 'a large, brutish creature with immense strength and thick hide.', 80, 15, 10, 50),
('dremora kynval', 'a lesser daedra, but still a formidable warrior from mehrunes dagon''s legions.', 60, 10, 9, 40),
('imperial guard', 'a disciplined soldier of the imperial legion, armed with steel.', 45, 10, 8, 25),
('dungeon rat', 'a large, aggressive rat, common in the dark corners of the dungeon.', 15, 4, 2, 5),
('feral dog', 'a starving, wild dog that has found its way into the dungeon.', 22, 5, 3, 8),
('ghostly apparition', 'a translucent, ethereal spirit of a former prisoner or guard.', 30, 7, 5, 20),
('fallen imperial mage', 'the reanimated corpse of an imperial battlemage, still crackling with dark energy.', 55, 11, 7, 35),
('giant spider', 'a monstrous arachnid, its web-filled lair suggests a dangerous encounter.', 38, 9, 6, 22),
('hungry prisoner', 'a desperate, emaciated prisoner, driven to violence by starvation.', 25, 6, 4, 10),
('sewer croc', 'a large, aggressive crocodile dwelling in the dungeon''s murky waters.', 42, 10, 7, 28),
('corrupted sentry', 'an ancient ayleid construct, now corrupted and hostile.', 65, 13, 11, 45);


-- Inserts for room_template_enemies (linking enemies to room templates)
-- Assuming room_template_id 1 is 'Damp Prison Cell', 2 is 'Dark Dungeon Corridor', etc.
-- Assuming enemy_def_id 1 is 'Bandit', 2 is 'Scamp', 3 is 'Zombie', 4 is 'Wolf', 5 is 'Clannfear', 6 is 'Skeleton', 7 is 'Goblin', 8 is 'Ogre', 9 is 'Dremora Kynval', 10 is 'Imperial Guard', 11 is 'Dungeon Rat', 12 is 'Feral Dog', 13 is 'Ghostly Apparition', 14 is 'Fallen Imperial Mage', 15 is 'Giant Spider', 16 is 'Hungry Prisoner', 17 is 'Sewer Croc', 18 is 'Corrupted Sentry'
INSERT INTO room_template_enemies (template_id, enemy_def_id) VALUES
(2, 1),
(2, 6),
(2, 10),
(3, 3),
(3, 16),
(4, 10),
(5, 7),
(5, 4),
(5, 11),
(5, 17),
(6, 11),
(6, 12),
(7, 10),
(10, 3),
(10, 6),
(11, 13),
(11, 18),
(12, 3),
(12, 17),
(13, 11),
(14, 13),
(15, 10),
(16, 13),
(17, 16),
(18, 11),
(19, 11),
(20, 12),
(21, 16),
(22, 1),
(23, 1),
(24, 17),
(25, 15),
(26, 6),
(27, 16),
(28, 13),
(29, 3),
(30, 16),
(31, 11),
(32, 3),
(32, 13);