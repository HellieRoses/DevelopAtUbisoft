#include <SFML/Graphics/Text.hpp>
#include "gameConstants.h"
class Player
{
	public :
		Player();
		float getMoney() const { return m_money; };
		void removeMoney(float _stolenMoney);
		void addMoney(float _moneyToAdd);
		void reset();
	private:
		float m_money;
};
