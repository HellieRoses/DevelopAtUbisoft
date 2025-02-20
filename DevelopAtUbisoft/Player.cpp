
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <math.h>

Player::Player()
{
	reset();
}

void Player::removeMoney(float _stolenMoney)
{
	m_money -= _stolenMoney;
}

void Player::addMoney(float _moneyToAdd)
{
	m_money += _moneyToAdd;
}

void Player::reset()
{
	m_money = 200.f;
}



