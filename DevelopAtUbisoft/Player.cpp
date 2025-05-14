
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
	m_money = PLAYER_MONEY;
	m_moneyOut = 0.f;
}

void Player::removeMoneyOut(float _stolenMoney)
{
	m_moneyOut -= _stolenMoney;
}

void Player::addMoneyOut(float _moneyToAdd)
{
	m_moneyOut += _moneyToAdd;
}



