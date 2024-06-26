#include <iostream>
#include <fstream>
#include <algorithm>
#include "Character.h"
#include "Item.h"
#include "stdlib.h"
#include "time.h"
#include "Battle.h"
#include <dpp/dpp.h>
#include <thread>
#include <chrono>
#include "Serialize.h"

/*
int random_number_gen() {
	int random_number = rand() % 10 + 1; //from 1 to 10, seems to be fair.
	return random_number;
}
Character** create_characters() {
	//Character char_array[2]{ };

	Character* test = new Character("Conan the barbarian", 500, 4); //created on the heap
	Character* test2 = new Character("King Arthur", 350, 6);
	Character* temp_char_array[2]{ test, test2 };

	Item* weapon1 = new Item("Iron BattleAxe", 30);
	Item* armor1 = new Item("leather light armor", -10);
	Item* weapon2 = new Item("Excalibur", 20);
	Item* armor2 = new Item("Chain Mail Armor", -20);

	(*test).add_object_to_inventory(*weapon1);
	(*test).add_object_to_inventory(*armor1);
	(*test2).add_object_to_inventory(*weapon2);
	(*test2).add_object_to_inventory(*armor2);

	return temp_char_array;
}
*/

void write_to_file(Character char_to_write) {
	//TODO check implementation of this
	//std::cout << typeid(char_to_write).name();
	std::ofstream char_file;
	char_file.open("Created_Characters.txt", std::ofstream::app);
	
	char_file << char_to_write.serialize_to_file();

	char_file.close();
}

void load_characters() { //load characters from the created_file
	std::ifstream char_file;
	char_file.open("Created_Characters.txt");
	std::string read_string;
	while(!char_file.eof()) {
		std::string temp_str;
		std::getline(char_file, temp_str);
		read_string = read_string + temp_str;
	}
	std::cout << read_string;
	
}

void create_character(std::vector<Character*>& char_array, dpp::form_submit_t event) {
	/* For this simple example, we know the first element of the first row ([0][0]) is value type string.
	* In the real world, it may not be safe to make such assumptions!
	*/
	std::string name = std::get<std::string>(event.components[0].components[0].value);
	int strenght = std::stoi(std::get<std::string>(event.components[1].components[0].value));
	int endurance = std::stoi(std::get<std::string>(event.components[2].components[0].value));
	int agility = std::stoi(std::get<std::string>(event.components[3].components[0].value));
	Character* new_character = new Character(event.command.get_issuing_user(), name, 100, strenght, endurance, agility);
	
	Item wep {"Sword",10};
	Item arm {"Shield", -5};

	new_character->set_offensive(wep);//TODO this is not feasible, maybe add an unarmed weapon (fist)
	new_character->set_defensive(arm);

	char_array.push_back(new_character);
	
	//write to file
	write_to_file(*new_character);
}


int main() {
	/*
	Item* test = new Item("OBJETO DE PRUEBA", 10);
	Serial_Strategy* strat = new Item_Serializer(*test);
	std::ofstream char_file;
	char_file.open("Created_Characters.txt", std::ofstream::app);
	char_file << (*strat).Serialize() << '\n';
	*/
	dpp::user* discord_user = new dpp::user();
	discord_user->username = "Reborn675";
	Character* chara = new Character(*discord_user, "Character Test", 100, 5, 6, 7);
	
	Item wep{ "Sword",10 };
	Item arm{ "Shield", -5 };

	chara->set_offensive(wep);//TODO this is not feasible, maybe add an unarmed weapon (fist)
	chara->set_defensive(arm);

	Serial_Strategy* strat = new Character_Serializer(*chara);
	std::ofstream char_file;
	char_file.open("Created_Characters.txt", std::ofstream::app);
	char_file << (*strat).Serialize(1) << '\n';
}


/*
int main() {

	//create characters array
	std::vector<Character*> char_array;
	const dpp::slashcommand_map a;

	//load_characters();



	//******************************BOT SETUP********************************************
	dpp::cluster bot(BOT_TOKEN); //objeto cliente de la libreria de discord.

	bot.on_log(dpp::utility::cout_logger());
	
	bot.on_slashcommand([&bot, &char_array](const dpp::slashcommand_t& event) { //cuando se recibe un comando, se agrega &bot para poderlo referenciar dentro de la funcion lambda. TODO ESTO ES UNA FUNCION LAMBDA QUE SE PASA A 
		if (event.command.get_command_name() == "create_character") {
			dpp::interaction_modal_response modal_test("character_creation_form", "Please enter your characters information");

			modal_test.add_component(dpp::component().set_label("Name:")
				.set_id("Name_Field")
				.set_type(dpp::cot_text)
				.set_placeholder("Min: 5, Max: 100 Characters")
				.set_min_length(5)
				.set_max_length(100)
				.set_text_style(dpp::text_short));

			modal_test.add_row();
			modal_test.add_component(dpp::component().set_label("Strenght:")
				.set_id("strenght_id")
				.set_type(dpp::cot_text)
				.set_placeholder("Maximum 10")
				.set_min_length(1)
				.set_max_length(2)
				.set_text_style(dpp::text_short));

			modal_test.add_row();
			modal_test.add_component(dpp::component().set_label("Endurance:")
				.set_id("endurance_id")
				.set_type(dpp::cot_text)
				.set_placeholder("Maximum 10")
				.set_min_length(1)
				.set_max_length(2)
				.set_text_style(dpp::text_short));
			modal_test.add_row();
			modal_test.add_component(dpp::component().set_label("Agility:")
				.set_id("agility_id")
				.set_type(dpp::cot_text)
				.set_placeholder("Maximum 10")
				.set_min_length(1)
				.set_max_length(2)
				.set_text_style(dpp::text_short));

			event.dialog(modal_test);
			std::cout << "form sent" << '\n';
			
		}
		if (event.command.get_command_name() == "get_characters") {
			event.reply("");
			for (auto it = char_array.begin(); it != char_array.end(); ++it) {
				dpp::message msg(event.command.channel_id, (*(*it)).get_name());
				bot.message_create(msg);
			}
		}

		if (event.command.get_command_name() == "get_commands") {
			bot.guild_commands_get(1223089378717601793, [&bot,event](const dpp::confirmation_callback_t callback) {
				if (callback.is_error()) {
					std::cout << "Error getting the guild commands" << '\n';
					return;
				}
				std::vector<std::string> command_names();

				std::cout << "Get Command Called" << '\n';
				dpp::slashcommand_map commands = callback.get<dpp::slashcommand_map>();
				std::cout << commands.size() << '\n';
				for (auto it = commands.begin(); it != commands.end(); ++it) {
					//std::cout << "SnowFlake ID: " << std::get<0>(*it) << ', ' << "Command Name: " << std::get<1>(*it).name << '\n';
					dpp::message msg(event.command.channel_id, std::get<1>(*it).name);
					bot.message_create(msg);
				}
				event.reply(""); //this throws error, but acknowledges the event.
				});
		}
		if (event.command.get_command_name() == "fight") {
			//create battle object
			event.thinking("Command terminated");
			std::cout << "Fight command called." << '\n';
			Battle fight = Battle(char_array);
			std::cout << "start fight";
			std::vector<std::string> msg_array = fight.Fight(); //TEST YOUR MIGHT!
			//having the messages, send them to discord.
			dpp::snowflake fight_thread;
			bool thread_created = false;
			bot.thread_create(char_array[0]->get_name() + " VS " + char_array[1]->get_name(), 
				event.command.channel_id, 
				60, 
				dpp::channel_type::CHANNEL_PUBLIC_THREAD,
				true,
				0,
				[&fight_thread, &thread_created](const dpp::confirmation_callback_t callback){
					fight_thread = callback.get<dpp::thread>().id; //save snowflake id
					thread_created = true;
				});
			while (!thread_created){

			}
			std::cout << "THREAD CREATED";
			std::for_each(msg_array.begin(), msg_array.end(), [&event, &bot, &fight_thread](std::string &message) { //TODO sometimes the first message fails, thats because the create thread command takes a little bit, wait for confirmation
				dpp::message msg(fight_thread,message);
				bot.message_create(msg);
				std::cout << "Message sent" << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(1)); //TODO change rate of sent messages, check for optimal message rate to avoid 429
				});
			event.edit_original_response(dpp::message("Fight Ended!"));
			std::cout << "Fight Ended!" + '\n';
		}
		if (event.command.get_command_name() == "modal_test") {
			dpp::user usr = event.command.get_issuing_user();
			std::cout << usr.username;
		}
		});

	bot.on_form_submit([&char_array](const dpp::form_submit_t &event) {
		if (event.custom_id == "character_creation_form") {
			create_character(char_array, event);
			event.reply("Character Created");
			}
		});

	bot.on_ready([&bot](const dpp::ready_t& event) { //todo esto sucede cuando se conecta. 
		if (dpp::run_once<struct register_bot_commands>()) { //correr esto una sola vez por ejecucion.
			std::cout << "running configuration" << '\n';
			//bot.global_bulk_command_delete(); //borrar todos los comandos creados. de-registrarlos.
			bot.guild_command_create(dpp::slashcommand("create_character", "Create Character test", bot.me.id), 1223089378717601793); //registrar comando. 
			bot.guild_command_create(dpp::slashcommand("get_characters", "Get Created Characters", bot.me.id), 1223089378717601793);
			bot.guild_command_create(dpp::slashcommand("get_commands", "Get Registered Commands", bot.me.id), 1223089378717601793);
			bot.guild_command_create(dpp::slashcommand("fight", "start the fight!", bot.me.id), 1223089378717601793);
			//bot.guild_command_create(dpp::slashcommand("modal_test", "test for modal forms", bot.me.id), 1223089378717601793);
		}
		});
	bot.start(dpp::st_wait);
}*/