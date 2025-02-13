
class Player
{
	public :
		Player();
		float getMoney() const { return m_money; };
		void removeMoney(float _stolenMoney);
		void addMoney(float _moneyToAdd);
	private:
		float m_money;
};
