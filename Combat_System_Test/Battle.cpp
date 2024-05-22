#include "Battle.h"

int random_number_gen() {
	int random_number = rand() % 10 + 1; //from 1 to 10, seems to be fair.
	return random_number;
}

void Battle::Generate_Move_Order()
{
	//generate the array order. Depending on the speed of the individual characters.
	if (char1->get_speed() <= char2->get_speed()) {
		move_order_array[0] = char1;
		move_order_array[1] = char2;
	}
	else {
		move_order_array[0] = char2;
		move_order_array[1] = char1;
	}
}

std::vector<std::string> Battle::Fight() {
	if (!move_order_array) { //if we have not computed a move array order
		throw std::invalid_argument("Did not get a valid move_order_array!");
	}
	std::cout << "Fight Started" + '\n';
	int round_number = 0;
	while (true) {
		round_number +=1;
		std::string msg = "---------------------------------->ROUND_NUMBER " + std::to_string(round_number) + "<----------------------------------";
		message_array.push_back(msg);
		std::cout << msg << '\n';
		msg = char1->get_name() + " hp: " + std::to_string(char1->get_health_points());
		message_array.push_back(msg);
		std::cout << msg << '\n';
		msg = char2->get_name() + " hp: " + std::to_string(char2->get_health_points());
		message_array.push_back(msg);
		std::cout << msg << '\n';

		for (int i = 0; i < 2; ++i) { //iterate through array
			if (i == 0) { //TODO this is currently a shit implementation holy hell.
				int attack_speed = (*(move_order_array[0])).get_speed();
				int roll = random_number_gen();
				if (attack_speed > roll) {
					//there is a hit!
					Item attack_item = (*move_order_array[0]).get_offensive();
					int damage = (*(move_order_array[0])).attack(*(move_order_array[1])); //check to get the message and add it to the message array vector
					std::string msg = "---->" + (*move_order_array[0]).get_name() + " attacks " + (*move_order_array[1]).get_name() + " with " + attack_item.get_name() + ". Dealing " + std::to_string(damage) + " Damage" + '\n';
					message_array.push_back(msg);
					std::cout << msg << '\n';
				}
				else {
					//there is a miss
					std::string msg = "---->" + (*(move_order_array[0])).get_name() + " Misses!";
					message_array.push_back(msg);
					std::cout << msg << '\n';

				}
			}
			else {
				int attack_speed = (*(move_order_array[1])).get_speed();
				int roll = random_number_gen();
				if (attack_speed > roll) {
					//there is a hit!
					Item attack_item = (*move_order_array[1]).get_defensive();
					int damage = (*(move_order_array[1])).attack(*(move_order_array[0])); //check to get the message and add it to the message array vector
					std::string msg = "---->" + (*move_order_array[1]).get_name() + " attacks " + (*move_order_array[0]).get_name() + " with " + attack_item.get_name() + ". Dealing " + std::to_string(damage) + " Damage" + '\n';
					message_array.push_back(msg);
					std::cout << msg << '\n';
				}
				else {
					//there is a miss
					std::string msg = "---->" + (*(move_order_array[1])).get_name() + " Misses!";
					message_array.push_back(msg);
					std::cout << msg << '\n';
				}

			}
		}
		//check if anyone died in the last round
		if ((*move_order_array[0]).get_health_points() <= 0 || (*move_order_array[1]).get_health_points() <= 0) { //if either one of the characters is dead
			break; //end the fight
		} 
	}
	std::string msg = char1->get_name() + " hp: " + std::to_string(char1->get_health_points());
	message_array.push_back(msg);
	msg = char2->get_name() + " hp: " + std::to_string(char2->get_health_points());
	message_array.push_back(msg);

	//return the winning character
	Character* winner =  (*move_order_array[0]).get_health_points() < 0 ? move_order_array[0] : move_order_array[1];
	std::cout << winner->get_name() + " Wins!" + '\n';
	message_array.push_back(winner->get_name() + " Wins!");
	return message_array;
}
