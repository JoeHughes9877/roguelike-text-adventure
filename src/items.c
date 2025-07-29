#include "../include/items.h"
#include "../include/entity.h"
#include "../include/inventory.h"
#include <stdio.h>
#include <string.h>

static int found_item_index = -1;

void use_item(char *item_name) {
  for (int i = 0; function_map[i].name != NULL; i++) {
    if (strstr(item_name, function_map[i].name) != NULL) {
      if (check_if_in_inventory(item_name) == 1) {
        found_item_index = i;
        function_map[i].func();

        if (strstr(function_map[i].type, "consumable") != NULL ||
            strstr(function_map[i].type, "tool") != NULL ||
            strstr(function_map[i].type, "scroll") != NULL) {
          remove_item_from_inventory(item_name, false);
        }
        return;
      }
    }
  }
  printf("Thou hast no '%s'.\n", item_name);
  return;
}

void use_iron_longsword() {
  printf("You draw the iron longsword, its familiar weight a comfort as you "
         "prepare for the fray.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_iron_greatsword() {
  printf("You hoist the massive iron greatsword, feeling its immense power "
         "surge through your arms.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_shiv() {
  printf("You clutch the crude shiv, a desperate, last-resort weapon in the "
         "tight confines of combat.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_iron_dagger() {
  printf("You unsheathe the iron dagger, nimble and swift, perfect for a "
         "precise, silent strike.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_rusty_sword() {
  printf("You reluctantly grasp the heavily corroded sword, its rust flaking "
         "as you pray it holds true.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_steel_mace() {
  printf("You heft the heavy steel mace, its blunt force promising to shatter "
         "any defense.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void equip_leather_cuirass() {
  printf("You fasten the leather cuirass, its worn hide offering a basic, yet "
         "essential, layer of defense.\n");
  add_defense(&player, function_map[found_item_index].value);
  ;
}

void equip_fine_steel_helmet() {
  printf("You settle the fine steel helmet upon your head, its polished "
         "surface reflecting the dungeon's gloom.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void equip_prisoners_ragged_trousers() {
  printf("You pull on the prisoner's ragged trousers, surprisingly comfortable "
         "for a quick, unencumbered escape.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void equip_leather_boots() {
  printf("You slip on the leather boots, their soft soles perfect for silent "
         "movement through dark passages.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void equip_imperial_guard_shield() {
  printf("You raise the imperial guard shield, its sturdy form and proud "
         "emblem promising solid protection.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void equip_studded_leather_armor() {
  printf("You don the studded leather armor, the metal studs offering "
         "reinforced protection against blows.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void equip_wooden_shield() {
  printf("You brace yourself with the simple wooden shield, a humble barrier "
         "against the dangers ahead.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void drink_potion_of_healing() {
  printf("You uncork and drink the potion of healing, feeling a warm, "
         "restorative energy mend your wounds.\n");
  add_health(&player, function_map[found_item_index].value);
}

void drink_minor_healing_potion() {
  printf("You quickly quaff the minor healing potion, feeling a small but "
         "welcome surge of vitality.\n");
  add_health(&player, function_map[found_item_index].value);
}

void drink_grand_healing_potion() {
  printf("You gulp down the grand healing potion, a powerful elixir that "
         "revitalizes your very being.\n");
  add_health(&player, function_map[found_item_index].value);
}

void apply_poison_of_weakness() {
  printf("You carefully smear the dark poison of weakness onto your blade, "
         "preparing to debilitate your next foe.\n");
  add_attack(&player, function_map[found_item_index].value);
}

void eat_sweetroll() {
  printf("You bite into the soft, sugary sweetroll, a moment of simple "
         "pleasure that restores a touch of your vigor.\n");
  add_health(&player, function_map[found_item_index].value);
}

void eat_moldy_bread() {
  printf("You grimace as you chew the moldy bread, barely edible but enough to "
         "stave off the worst hunger pangs.\n");
  add_health(&player, function_map[found_item_index].value);
}

void use_welkynd_stone() {
  printf("You crush the welkynd stone in your hand, and its glowing energy "
         "flows into you.\n");
}

void use_lockpick() { printf("If only there was a lock to pick.\n"); }

void use_master_lockpick() { printf("If only there was a lock to pick.\n"); }

void use_torch() {
  printf("You ignite the torch, its warm flame pushing back the oppressive "
         "darkness of the dungeon.\n");
}

void use_rusty_shovel() {
  printf("You grip the rusty shovel with both hands, hoping it's enough to "
         "knock someone out.\n");
  replace_attack(&player, function_map[found_item_index].value);
}

void use_spyglass() {
  printf("You extend the spyglass and peer into the distance, bringing far-off "
         "details into sharp focus.\n");
}

void use_bear_trap() {
  printf("You carefully set the heavy bear trap, its menacing jaws ready to "
         "ensnare an unwary creature.\n");
}

void read_scroll_of_fireball() {
  printf("You unfurl the scroll of fireball, and as you read its ancient "
         "words, a scorching orb of flame erupts from your hand!\n");
}

void read_scroll_of_ice_storm() {
  printf("You recite the chilling incantation from the scroll of ice storm, "
         "summoning a tempest of razor-sharp ice shards!\n");
}

void read_scroll_of_fire_storm() {
  printf("You utter the devastating words from the scroll of fire storm, "
         "unleashing a cataclysmic inferno that engulfs all nearby foes!\n");
}

void read_scroll_of_lightning_bolt() {
  printf("You intone the crackling spell from the scroll of lightning bolt, "
         "and a focused, searing bolt of pure energy streaks forth!\n");
}

void read_scroll_of_healing_hands() {
  printf("You read the scroll of healing hands, and a warm, golden light "
         "emanates from your palms, mending wounds with divine grace.\n");
}

void read_scroll_of_detect_life() {
  printf("You read the scroll of detect life, and a faint, ethereal aura "
         "spreads, "
         "revealing the hidden presences of living creatures nearby.\n");
}

void examine_rusty_key() {
  printf("You turn the rusty key over in your hand, its age hinting at a "
         "forgotten lock it might open.\n");
}

void examine_journal_entry() {
  printf("You carefully unfold the torn journal entry, its faded ink revealing "
         "a cryptic secret or a forgotten truth.\n");
}

void examine_old_map_fragment() {
  printf("You scrutinize the old map fragment, its faded lines hinting at a "
         "small, unexplored section of the dungeon.\n");
}

void examine_worn_leather_map() {
  printf("You unroll the worn leather map, its intricate details promising a "
         "grander journey across the region.\n");
}

void pick_up_gold_coin() {
  printf("You pocket a gleaming gold coin, its weight a satisfying reminder of "
         "your growing wealth.\n");
}

void pick_up_bag_of_gold_small() {
  printf("You retrieve a small pouch, feeling the jingle of a few modest gold "
         "coins within.\n");
}

void pick_up_bag_of_gold_large() {
  printf("You heft the heavy sack of gold, a truly substantial reward for your "
         "perilous journey.\n");
}

void pick_up_ancient_coin() {
  printf("You inspect the ancient coin, its tarnished surface whispering tales "
         "of forgotten empires and bygone eras.\n");
}

void wear_silver_ring() {
  printf("You slip the plain silver ring onto your finger, a simple "
         "adornment.\n");
}

void wear_enchanted_amulet() {
  printf("You place the enchanted amulet around your neck, feeling a faint, "
         "mysterious hum against your skin.\n");
  add_defense(&player, function_map[found_item_index].value);
}

void read_lockpicking_guide() {
  printf("You open the lockpicking guide, poring over its intricate diagrams "
         "and mastering new techniques.\n");
}

void interact_waterlogged_book() {
  printf("You pick up the waterlogged book, its pages swollen and unreadable, "
         "smelling faintly of stagnant pond scum.\n");
}

void interact_empty_wine_bottle() {
  printf("You grab the empty wine bottle and smash it against the wall. The "
         "jagged glass might make a decent weapon.\n");
  add_attack(&player, function_map[found_item_index].value);
}

void interact_glowing_mushroom() {
  printf(
      "You examine the glowing mushroom. Its ethereal light casts soft, eerie "
      "shadows in the darkness... shame it tastes like cement powder.\n");
  add_health(&player, function_map[found_item_index].value);
}

void interact_broken_lantern() {
  printf("You pick up the broken lantern, its rusted shell a sad reminder that "
         "it can no longer banish the shadows.\n");
}

void interact_lucky_rabbits_foot() {
  printf("You rub the lucky rabbit's foot, a superstitious gesture, hoping it "
         "truly brings you good fortune in this perilous place.\n");
}

FunctionMap function_map[] = {
    // Weapons
    {"iron longsword", "weapon", 15, use_iron_longsword},
    {"iron greatsword", "weapon", 20, use_iron_greatsword},
    {"shiv", "weapon", 5, use_shiv},
    {"iron dagger", "weapon", 8, use_iron_dagger},
    {"rusty sword", "weapon", 7, use_rusty_sword},
    {"steel mace", "weapon", 18, use_steel_mace},
    {"rusty shovel", "weapon", 12, use_rusty_shovel},
    {"empty wine bottle", "weapon", 11, interact_empty_wine_bottle},

    // Armor
    {"leather cuirass", "armor", 12, equip_leather_cuirass},
    {"fine steel helmet", "armor", 10, equip_fine_steel_helmet},
    {"prisoner's ragged trousers", "armor", 5, equip_prisoners_ragged_trousers},
    {"leather boots", "armor", 7, equip_leather_boots},
    {"imperial guard shield", "armor", 20, equip_imperial_guard_shield},
    {"studded leather armor", "armor", 15, equip_studded_leather_armor},
    {"wooden shield", "armor", 8, equip_wooden_shield},

    // Consumables
    {"potion of healing", "consumable", 10, drink_potion_of_healing},
    {"minor healing potion", "consumable", 5, drink_minor_healing_potion},
    {"grand healing potion", "consumable", 20, drink_grand_healing_potion},
    {"poison of weakness", "consumable", 5, apply_poison_of_weakness},
    {"sweetroll", "consumable", 5, eat_sweetroll},
    {"moldy bread", "consumable", 2, eat_moldy_bread},
    {"welkynd stone", "consumable", 10, use_welkynd_stone},
    {"glowing mushroom", "consumable", 3, interact_glowing_mushroom},

    // Tools
    {"lockpick", "tool", 0, use_lockpick},
    {"master lockpick", "tool", 0, use_master_lockpick},
    {"torch", "tool", 0, use_torch},
    {"spyglass", "tool", 0, use_spyglass},
    {"bear trap", "tool", 0, use_bear_trap},

    // Scrolls
    {"scroll of fireball", "scroll", 0, read_scroll_of_fireball},
    {"scroll of ice storm", "scroll", 0, read_scroll_of_ice_storm},
    {"scroll of fire storm", "scroll", 0, read_scroll_of_fire_storm},
    {"scroll of lightning bolt", "scroll", 0, read_scroll_of_lightning_bolt},
    {"scroll of healing hands", "scroll", 0, read_scroll_of_healing_hands},
    {"scroll of detect life", "scroll", 0, read_scroll_of_detect_life},

    // Quest Items
    {"rusty key", "quest item", 0, examine_rusty_key},
    {"journal entry", "quest item", 0, examine_journal_entry},
    {"old map fragment", "quest item", 0, examine_old_map_fragment},
    {"worn leather map", "quest item", 0, examine_worn_leather_map},

    // Currency
    {"gold coin", "currency", 0, pick_up_gold_coin},
    {"bag of gold (small)", "currency", 0, pick_up_bag_of_gold_small},
    {"bag of gold (large)", "currency", 0, pick_up_bag_of_gold_large},
    {"ancient coin", "currency", 0, pick_up_ancient_coin},

    // Jewelry
    {"silver ring", "jewelry", 3, wear_silver_ring},
    {"enchanted amulet", "jewelry", 7, wear_enchanted_amulet},

    // Book
    {"lockpicking guide", "book", 0, read_lockpicking_guide},

    // Miscellaneous
    {"waterlogged book", "misc", 0, interact_waterlogged_book},
    {"empty wine bottle", "misc", 0, interact_empty_wine_bottle},
    {"broken lantern", "misc", 0, interact_broken_lantern},
    {"lucky rabbit's foot", "misc", 1, interact_lucky_rabbits_foot},

    {NULL, NULL, 0, NULL} // Null terminator
};
