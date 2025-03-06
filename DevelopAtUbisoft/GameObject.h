#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
	public:
		virtual ~GameObject() = default;
		virtual void update(float _deltaTime) =0;
		virtual void draw(sf::RenderWindow& _window) = 0;
		void setId(int _id) {
			id = _id;
		}
		int getId() {
			return id;
		}
		void setWantDestroy() {
			wantDestroy = true;
		}
		bool wantDestroy = false;
		int id;
};

