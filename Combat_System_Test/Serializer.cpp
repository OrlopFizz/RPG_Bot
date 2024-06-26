#include "Tree_DS.cpp" //classes and objects to serialize get represented as a tree just before serialization 
#include "Character.h"
#include "Item.h"
#include "Serialize.h"

//TODO make every serialize a singleton? everytime we need to serialize an object, just call that single instance.

std::string Serial_Strategy::Serialize(int plevel) { //"Serial_Strategy" base class
	return "Base Class Serialize called";
}

std::string Item_Serializer::Serialize(int plevel) {
	//an item has a string with its name, and an int with its damage. 
	//every one if this values is a child node of a root node called called item:
	Node* root = new Node("Class Item:", plevel);
	Node* name_node = new Node("Name:" + (*this).item.get_name());
	Node* damage_node = new Node("Damage:" + std::to_string((*this).item.get_damage()));

	root->add_child(name_node);
	root->add_child(damage_node);
	std::string out{};
	root->get_tree(out);
	return out;
}

std::string Character_Serializer::Serialize(int plevel) {
	Node* root = new Node("Class Character:", plevel);
	Node* owner_node = new Node("Owner:" + ((*this).character.get_owner()).format_username());
	Node* name_node = new Node("Name:" + (*this).character.get_name());
	Node* health_points_node = new Node("Health Points:" + std::to_string((*this).character.get_health_points()));
	Node* speed_node = new Node("Speed:" + std::to_string((*this).character.get_speed()));

	Item_Serializer* temp_ser = new Item_Serializer((*this).character.get_offensive());
	Node* off_item_node = new Node("Offensive Item:" + (*temp_ser).Serialize(2));
	temp_ser->item = (*this).character.get_defensive();
	Node* def_item_node = new Node("Defensive Item:" + (*temp_ser).Serialize(2));

	Node* str_node = new Node("Strenght:" + std::to_string((*this).character.get_str()));
	Node* end_node = new Node("Endurance:" + std::to_string((*this).character.get_end()));
	Node* agi_node = new Node("Agility:" + std::to_string((*this).character.get_agi()));

	Node* children[9] = { owner_node, name_node, health_points_node, speed_node, off_item_node, def_item_node, str_node, end_node, agi_node };
	root->add_children(children, 9);

	std::string out{};
	root->get_tree(out);
	return out;
}