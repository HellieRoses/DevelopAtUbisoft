#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"
#include "MainManager.h"
#include "GameObject.h"
#include "Animation.h"
#include "core.h"
class Game {
	public:
		Game();
		static Game& get();
		void init(const std::string _windowName);
		void run();
		sf::Texture& getTexture();
		sf::Texture& getThiefTexture();
		sf::Texture& getBaseTurretTexture();
		sf::Texture& getTurret1Texture();
		sf::Texture& getMissileTexture();
		sf::Texture& getTileTexture();
		sf::Texture& getPanelTexture();
		sf::Texture& getBrownPanelTexture();
		sf::Texture& getWhitePanelTexture();
		sf::Texture& getRedPanelTexture();
		sf::Texture& getBluePanelTexture();
		sf::Texture& getBackgroundTexture();

		Animation& getLeftThiefAnimation();
		Animation& getUpThiefAnimation();

		MainManager& getMainManager() {
			return m_mainManager;
		}

		sf::Font& getFont();
		sf::RenderWindow& getGameWindow();
		TileMap* getTileMap();
		template<typename T>
		void visit(std::function<bool(T&)> _visitor) {
			for (const auto& gameObject : m_gameObjects)
			{
				if (T* typedGameObject = dynamic_cast<T*>(gameObject.get())) {
					if (!_visitor(*typedGameObject))
						break;
				}
						
			}
		};
		template<typename T, typename... Args>
		T& addGameObject(Args... args) {
			m_gameObjectsToAdd.push_back(std::make_unique<T>(std::forward<Args>(args)...));
			m_gameObjectsToAdd.back()->setId(nextGOid);
			nextGOid++;
			return static_cast<T&>(*m_gameObjectsToAdd.back());
		};
		template<typename T>
		T* getGameObjectById(int _id) {
			auto it = std::find_if(
				m_gameObjects.begin(),
				m_gameObjects.end(),
				[_id](const std::unique_ptr<GameObject>& _go) {
					return _go->getId() == _id;
				});
			if (it != m_gameObjects.end()) {
				return dynamic_cast<T*>(it->get());
			}else {
				return nullptr;
			}
		};
		void clearGameObjects() {
			m_gameObjects.clear();
		}
		void eraseIfGameObjects(std::function<bool(const std::unique_ptr<GameObject>&)> _erasor) {
			m_gameObjects.erase(
				std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), _erasor),
				m_gameObjects.end()
			);
		}
		Player& getPlayer() {
			return m_player;
		}

		bool isDrawDebug() {
			return m_drawDebug;
		}

	private:
		std::string getTexturePath(const std::string _fileName);
		

		void update(float _deltaTime);
		void draw();

		void updateGameObjects(float _deltaTime);
		void drawGameObjects();
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<std::unique_ptr<GameObject>> m_gameObjectsToAdd;

		sf::RenderWindow m_window;
		std::unique_ptr<TileMap> m_tileMap;

		sf::Texture m_tileMapTexture;
		sf::Texture m_tileTexture;
		sf::Texture m_thiefTexture;
		std::unique_ptr<Animation> m_animationThiefLeft;
		std::unique_ptr<Animation> m_animationThiefUp;
		sf::Texture m_baseTurretTexture;
		sf::Texture m_turret1Texture;
		sf::Texture m_missileTexture;
		sf::Texture m_uiPanel;
		sf::Texture m_brownMiniPanel;
		sf::Texture m_whiteMiniPanel;
		sf::Texture m_blueMiniPanel;
		sf::Texture m_redMiniPanel;
		sf::Texture m_background;
		sf::Font m_gameFont;

		MainManager m_mainManager;

		Player m_player;

		int nextGOid = 0;

		bool m_drawDebug = false;
};