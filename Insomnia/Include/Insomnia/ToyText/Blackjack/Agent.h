#ifndef INSOMNIA_TOY_TEXT_BLACKJACK_AGENT_H
#define INSOMNIA_TOY_TEXT_BLACKJACK_AGENT_H

#include <vector>
#include <Pixie/Concepts/PObject.h>

namespace insomnia::blackjack
{

class Agent
{
public:
	/** Default constructor */
	Agent();

	/**
	 * Called by Pixie at the end of the Game (This is called after Controller's End())
	 */
	void End();

private:
	/**
	 * Resets all the agents' members
	 */
	void Reset();

public:

	/**
	 * Draws a card from the deck
	 */
	void Hit();

	/**
	 * Sticks and passes the round to the dealer, potentially ending the game
	 */
	void Stick();

	/**
	 * Attaches a user defined controller class to this Agent
	 * @param controller The user defined controller enclosed within
	 * a pixie PObject
	 * @note The controller must implement a Tick function so it can
	 * properly play the game.
	 */
	void AttachController(pixie::PObject controller)
	{
		this->controller = std::move(controller);
	}

public: // Accessor methods
	/**
	 * Whether the agent is still playing (hitting) or not
	 * @return A bool indicating whether the agent is still playing
	 */
	bool IsPlaying() const { return is_playing; }

	/**
	 * Returns the first card (i.e. face up card) of the agent
	 * @return The face up card
	 * @pre Each side must have received two cards at the beginning of the game
	 */
	int GetFaceUpCard() const { return !cards.empty() ? cards[0] : -1; }

	/**
	 * Returns the running tally of agent's reward
	 * @return Running tally of agent's reward
	 */
	float GetReward() const;

	/**
	 * Returns the sum of the cards held by the Agent (with consideration of
	 * usable ace)
	 * @return The sum of the cards held by the Agent
	 */
	int GetSum() const { return sum; }

	/**
	 * A Tuple containing agent's observation of the environment
	 * The tuple elements are:
	 * 	0 - int - Sum of the players cards
	 * 	1 - int - Dealer's face up card
	 * 	2 - bool - Whether the ace in hand (if any) is usable or not
	 * @return a tuple containing  agents observation
	 */
	std::tuple<int, int, bool> GetObservation() const;

	/**
	 * A Tuple containing agent's final observation of the environment
	 * The tuple elements are:
	 * 	0 - int - Sum of the players' cards
	 * 	1 - int - Dealer's face up card
	 * 	2 - bool - Whether the ace in hand (if any) is usable or not
	 * 	3 - int - Sum of the dealers' cards
	 * @return a tuple containing agents observation
	 */
	std::tuple<int, int, bool, int> GetFinalObservation() const;

private:
	/**
	 * Checks whether the hand has an ace and if it worth 11 points.
	 * @return true if the ace in hand [if present] worth 11 points,
	 * false otherwise.
	 */
	bool CheckForUsableAce(int sum) const;

private:
	/// Player controller that needs to be implemented by user of insomnia
	pixie::PObject controller{};

	/// Cards that this person currently holds in his hand
	std::vector<int> cards{}; /*= std::vector<int>(52);*/

	/// Running sum of the player's cards (considering usable or non-usable ace)
	int sum = 0;

	/// Whether the ace in hand (if any) is usable or not
	bool has_usable_ace = false;

	/// status (hitting or sticking)
	bool is_playing = true;
};

} // namespace insomnia


#endif //INSOMNIA_TOY_TEXT_BLACKJACK_AGENT_H
