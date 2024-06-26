#pragma once
class Serial_Strategy {
	public:
		virtual std::string Serialize(int plevel);
};

class Item_Serializer : public Serial_Strategy {
public:
	Item item;
	std::string Serialize(int plevel);

	Item_Serializer(Item pitem) : item{ pitem } { };
};

class Character_Serializer : public Serial_Strategy {
public:
	Character character;
	std::string Serialize(int plevel);

	Character_Serializer(Character pchar) : character{ pchar } { };
};