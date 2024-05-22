#pragma once
#include <string>
class Character; //forward declaration, if i use include it causes a forward 
class Item
{
	private:
		std::string name;
		int damage; //positive is offensive, negative is defensive

		//status effect: por ahora, solo manejarlo.  como o quita vida de un enemigo, o protege mi propia vida. 
		//ecuacion para calcular daño: daño arma equipada - armadura equipada por contrincante.
		//por ahora manejarlo como un int. daño positivo para un arma, daño negativo para una armadura.
		//que tal si el inventario de un personaje es una matriz 2 x n, 0 es armas, 1 es armaduras.

	public:
		Item() : name{}, damage{} {};
		Item(std::string pname, int pdamage) : name{ pname }, damage{pdamage} {};
		
		std::string get_name() { return name; }
		int get_damage() { return damage; }

		void set_name(std::string pname);
		void set_damage(int pdamage);

		std::string serialize_item();

};

 