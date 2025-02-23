#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class GameStateManager
{
	public:	
		virtual void updateState(float _deltaTime) =0;
		virtual void drawState() =0;
		virtual void onEnterState() = 0;
		virtual void onExitState() = 0;

};

