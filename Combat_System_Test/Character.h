#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include <dpp/dpp.h>
class Character
{
	private:
	//TODO agregarle un campo que marque, para cada personaje, su dueño. Usando dpp::User.
		//esto me ayudara a identificar que personas empiezan a pelear, y traer sus personajes para crear el objecto fight.
		dpp::user owner;
		std::string name;
		int health_points;
		int speed; //for now only use is see who attacks first.
		Item offensive;
		Item defensive;
		//TODO implement inventory, do this later idk. probably a vector of items.

		//attributes
		int Strenght;
		int Endurance;
		int Agility;
	public: 
		Character() : name{ "default" }, health_points{ 1 }, speed{ 0 }, Strenght{ 0 }, Endurance{ 0 }, Agility{ 0 } {};
		Character(dpp::user powner, std::string pname, int phealth_points, int pstrenght, int pendurance, int pagility) :owner{powner}, name { pname }, health_points{ phealth_points }, Strenght{ pstrenght }, Endurance{ pendurance }, Agility{ pagility } {
			speed = Agility;
		};

		std::string get_name();
		int get_health_points();
		int get_speed();
		Item get_offensive();
		Item get_defensive();
		
		dpp::user get_owner();

		int get_str();
		int get_end();
		int get_agi();

		void set_name(std::string pname);
		void set_health_points(int php);
		void set_speed(int pspeed);
		void set_offensive(Item pitem);
		void set_defensive(Item pitem);
		void set_owner(dpp::user);
		
		void set_str(int pstr);
		void set_end(int pend);
		void set_agi(int pagi);

		//void add_object_to_inventory(Item& pobject);

		int get_offensive_value();
		int get_defensive_value();

		void reduce_hp(int pdamage);
		int attack(Character& foe);

		std::string serialize_to_file();
};

