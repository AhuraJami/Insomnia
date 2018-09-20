#ifndef PROJECT_GAMEMANAGER_H
#define PROJECT_GAMEMANAGER_H

#include <vector>
#include <Pixie/Core/Core.h>

#include "Insomnia/ToyText/Blackjack/Agent.h"

namespace insomnia::blackjack
{

class BlackjackGameManager
{
public: // These methods MUST have public accessor
	BlackjackGameManager();

	/** Called by Pixie at the beginning of the game (GameManager is the first whose Begin() method is called) */
	void Begin();

	/** Called by Pixie in each iteration (GameManager is the last one whose Tick() method is called) */
	void Tick();

	/** Called by Pixie at the end of the game (GameManager is the last one whose End() method is called)*/
	void End();

private:
	/** Resets the variables held by GameManager */
	void Reset();

public: // Accessed by player's agent
	/**
	 * Draws a single card from the deck
	 */
	int DrawCard();

	/**
	 * @return Dealer's face up card
	 */
	int GetDealerFaceUpCard() const { return dealer->GetFaceUpCard(); };

	/**
	 * @return Sum of the dealer's cards
	 * @note This value is available only after the game is ended
	 */
	int GetDealerSum() const { return has_ended ? dealer->GetSum() : 0; };

	/**
	 * Updated reward of the player agent after taking an action in current Tick()
	 * @return Updated reward of the player
	 * @note Remember that GameManager ticks last!
	 */
	float GetReward() const { return reward; }

	/**
	 * Sets the player/dealer agent
	 * @param agent A pointer to the agent entity created by Pixie
	 */
	void SetPlayer(Agent* agent) { player = agent; }
	void SetDealer(Agent* agent) { dealer = agent; }

	/**
	 * @return A pointer to the player agent
	 */
	Agent* GetPlayerAgent() const { return player; }

	// TODO(Ahura): Instead of keeping a separate boolean in GameManager,
	// add a feature to Pixie to get the engine status, i.e., output a boolean
	// indicating whether the main loop is still running or Shutdown is called.
	bool HasGameEnded() const { return has_ended; }

private:
	/// A pointer to dealer agent who's logic is controlled here by GameManager
	Agent* dealer;

	/// A pointer to player agent who needs a user implemented Controller
	Agent* player;

	/// Deck of the cards available to all parties
	std::vector<int> deck;

	/// Whether cards are drawn with replacement
	bool with_replacement = true;

	/// Iterator to keep track of the card that is drawn from the deck
	/// (Used when with_replacement is set to true)
	std::vector<int>::iterator deck_iterator;

	/// Running tally of player's reward
	float reward = 0.0f;

	/// Whether the game has ended or not (true after player chooses to Stick)
	bool has_ended = false;
};

} // namespace insomnia::blackjack

#endif //PROJECT_GAMEMANAGER_H
