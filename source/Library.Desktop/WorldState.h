#pragma once

namespace Library
{
	class GameTime;

	class WorldState final
	{
	public:
		/**
		*@brief Constructor for WorldState.
		*/
		WorldState();

		/**
		*@brief Destructor for WorldState.
		*/
		~WorldState();

		/**
		*@brief Gets the current game time
		*@return GameTime& Reference to the current game time
		*/
		GameTime& GetGameTime();

		/**
		*@brief sets the current game time
		*@param time Reference to a GameTime object that will set the current game time
		*/
		void SetGameTime(GameTime& time);

		//Pointers to what is currently being processed during the game loop
		class World* mWorld;
		class Sector* mSector;
		class Entity* mEntity;
		class Action* mAction;

	private:
		GameTime mGameTime;
	};
}
