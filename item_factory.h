#ifndef _ITEM_FACTORY_H_
#define _ITEM_FACTORY_H_

#include <string>
#include <vector>
#include <map>
#include "game.h"
#include "itype.h"
#include "item.h"
#include "color.h"
#include "picojson.h"
#include "catajson.h"
#include "item_group.h"
#include "iuse.h" 

typedef std::string Item_tag;
typedef std::vector<item> Item_list;
typedef void (iuse::*Use_function)(game*,player*,item*,bool);

//For the iuse arguments
class game;
class player;

class Item_factory
{
public:
    //Setup
    Item_factory();
    void init();
    void init(game* main_game);

    //Intermediary Methods - Will probably be removed at final stage
    itype* find_template(Item_tag id);
    itype* random_template();
    itype* template_from(Item_tag group_tag);
    const Item_tag random_id();
    const Item_tag id_from(Item_tag group_tag);

    //Production methods
    item create(Item_tag id, int created_at);
    Item_list create(Item_tag id, int created_at, int quantity);
    item create_from(Item_tag group, int created_at);
    Item_list create_from(Item_tag group, int created_at, int quantity);
    item create_random(int created_at);
    Item_list create_random(int created_at, int quantity);

private:
    std::map<Item_tag, itype*> m_templates;
    itype*  m_missing_item;
    std::map<Item_tag, Item_group*> m_template_groups;

    //json data handlers
    void load_item_templates();
    void load_item_templates_from(const std::string file_name);
    void load_item_groups_from(const std::string file_name);

    nc_color color_from_string(std::string color);
    Use_function use_from_string(std::string name);
    unsigned flags_from_json(catajson flags, std::string flag_type="");
    void set_material_from_json(Item_tag new_id, catajson mats);
    bool is_mod_target(catajson targets, std::string weapon);
    material material_from_tag(Item_tag new_id, Item_tag index);
    phase_id phase_from_tag(Item_tag name);
    ammotype ammo_from_string(std::string ammo);

    //two convenience functions that just call into set_bitmask_by_string
    void set_flag_by_string(unsigned& cur_flags, std::string new_flag, std::string flag_type);
    //sets a bitmask (cur_bitmask) based on the values of flag_map and new_flag
    void set_bitmask_by_string(std::map<Item_tag, unsigned> flag_map,
                               unsigned& cur_bitmask, std::string new_flag);

    //iuse stuff
    std::map<Item_tag, Use_function> iuse_function_list;
    //flags stuff
    std::map<Item_tag, unsigned> item_flags_list;
    //techniques stuff
    std::map<Item_tag, unsigned> techniques_list;
    //ammo stuff
    std::map<Item_tag, unsigned> ammo_flags_list;
};

extern Item_factory* item_controller;

#endif
