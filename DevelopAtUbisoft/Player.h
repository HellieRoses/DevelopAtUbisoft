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
		float getMoneyOut() const { return m_moneyOut; };
		void removeMoneyOut(float _stolenMoney);
		void addMoneyOut(float _moneyToAdd);
	private:
		float m_money;
		float m_moneyOut;
};
