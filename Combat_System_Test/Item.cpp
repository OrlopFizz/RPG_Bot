#include "Item.h"

void Item::set_name(std::string pname)
{
	(*this).name = pname;
}

void Item::set_damage(int pdamage)
{
	(*this).damage = pdamage;
}

std::string Item::serialize_item() {
	std::string out {};
	
	out = out + "Class Item:" + '\n';
	out = out + '\t' + "Name: " + (*this).get_name() + '\n';
	out = out + '\t' + "Damage: " + std::to_string((*this).get_damage());

	return out;
}