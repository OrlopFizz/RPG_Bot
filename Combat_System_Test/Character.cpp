#include "Character.h"
#include <iostream>
#include <algorithm>

std::string Character::get_name() {
	return this->name;
}

int Character::get_health_points() {
	return this->health_points;
}

int Character::get_speed()
{
	return this->speed;
}

Item Character::get_offensive() {
	return this->offensive;
}

Item Character::get_defensive() {
	return this->defensive;
}

dpp::user Character::get_owner() {
	return this->owner;
}

int Character::get_str()
{
	return this->Strenght;
}

int Character::get_end()
{
	return this->Endurance;
}

int Character::get_agi()
{
	return this->Agility;
}

void Character::set_name(std::string pname)
{
	(*this).name = pname;
}

void Character::set_health_points(int php)
{
	(*this).health_points = php;
}

void Character::set_speed(int pspeed)
{
	(*this).speed = pspeed;
}

void Character::set_offensive(Item pitem) {
	(*this).offensive = pitem;
}

void Character::set_defensive(Item pitem) {
	(*this).defensive = pitem;
}

void Character::set_owner(dpp::user usr) {
	this->owner = usr;
}

void Character::set_str(int pstr)
{
	this->Strenght = pstr;
}

void Character::set_end(int pend)
{
	this->Endurance = pend;
}

void Character::set_agi(int pagi)
{
	this->Agility = pagi;
}

int Character::get_offensive_value()
{
	return (*this).get_offensive().get_damage();
}

int Character::get_defensive_value()
{
	return (*this).get_defensive().get_damage();
}

void Character::reduce_hp(int pdamage)
{
	int new_hp = get_health_points() - pdamage;
	(*this).set_health_points(new_hp);
}

int Character::attack(Character& foe)
{
	//std::string item_name = (*this).get_inventory()[0][0].get_name();

	int offensive = get_offensive_value();
	int defensive = foe.get_defensive_value();
	int damage = offensive + defensive; //TODO this sucks balls. a defensive value should just reduce the damage, not completely stop it. This happens when the offensive and defensive value are the same
	if (damage < 0) {
		damage = 0;
	}
	foe.reduce_hp(damage);
	return damage;
	//std::cout << (*this).get_name() << " attacks " << foe.get_name() << " with " << item_name << ". Dealing " << damage << " Damage" << '\n';
}

std::string Character::serialize_to_file(){
	std::string out {};
	
	out = out + "Class Character:" + '\n';
	out = out + '\t' + "Owner: " + (*this).owner.username + '\n';
	out = out + '\t' + "Name: " + (*this).get_name() + '\n';
	out = out + '\t' + "Health Points: " + std::to_string((*this).get_health_points()) + '\n';
	out = out + '\t' + "Speed: " + std::to_string((*this).get_speed()) + '\n';
	out = out + '\t' + "Offensive: " + (*this).get_offensive().serialize_item() + '\n';
	out = out + '\t' + "Offensive: " + (*this).get_defensive().serialize_item() + '\n';
	out = out + '\t' + "Strenght: " + std::to_string((*this).get_str()) + '\n';
	out = out + '\t' + "Endurance: " + std::to_string((*this).get_end()) + '\n';
	out = out + '\t' + "Agility: " + std::to_string((*this).get_agi()) + '\n';
	return out;
}