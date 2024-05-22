#pragma once
#include "Character.h" 
#include "time.h"
#include <iostream>
class Battle
{
	private:
		Character* char1;
		Character* char2;
		Character* move_order_array [2];

		std::vector<std::string> message_array;

	public:
		Battle() : char1{}, char2{}, move_order_array{ NULL }, message_array{ } {};
		Battle(Character* pchar1, Character* pchar2) : char1{ pchar1 }, char2{ pchar2 }, message_array{ } {
			//generate the array order. Depending on the speed of the individual characters.
			Generate_Move_Order();
		};
		Battle(std::vector<Character*> pchar_array) { //create a battle given an array of two combatants
			char1 = pchar_array[0];
			char2 = pchar_array[1];
			Generate_Move_Order();
		};

		void set_char1(Character* pchar1) { char1 = pchar1; };
		void set_char2(Character* pchar2) { char2 = pchar2; };

		Character* get_char1() { return char1; };
		Character* get_char2() { return char2; };

		std::vector<std::string> get_message_array() { return message_array; };

		void Generate_Move_Order();
		std::vector<std::string> Fight(); //returns the winning character
};

