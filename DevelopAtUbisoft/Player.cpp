
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <math.h>

Player::Player()
	: m_money(200.f)
{
}

void Player::removeMoney(float _stolenMoney)
{
	m_money -= _stolenMoney;
}

void Player::addMoney(float _moneyToAdd)
{
	m_money += _moneyToAdd;
}



