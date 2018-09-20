#include "Insomnia/ToyText/Blackjack/GameManager.h"

#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <Pixie/Core/Core.h>
#include <Insomnia/ToyText/Blackjack/GameManager.h>

#include "Insomnia/ToyText/Blackjack/Agent.h"

using namespace insomnia::blackjack;

BlackjackGameManager::BlackjackGameManager()
{
	// Create a deck of 4 suits, 13 cards each (52 total)
	deck.reserve(52);

	// Cards in a single suit are identified by their score in Blackjack
	std::vector<int> suit = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

	// populate the deck with 4 suits
	for (int i = 0; i < 4; ++i)
	{
		std::copy(suit.begin(), suit.end(), std::back_inserter(deck));
	}
}

void BlackjackGameManager::Reset()
{
	reward = 0;
	has_ended = false;

	if (with_replacement)
	{
		// obtain a time-based seed
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();

		// shuffle the cards
		std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

		// Set deck iterator to the beginning of the deck
		deck_iterator = deck.begin();
	}

	// Give two cards to each side
	for (int i = 0; i < 2; ++i)
	{
		player->Hit();
		dealer->Hit();
	}
}

void BlackjackGameManager::Begin()
{
	Reset();
}

void BlackjackGameManager::Tick()
{
	if(has_ended)
		return;

	// TODO(Ahura): Check if controller is working properly!
	// Check if user has passed in an empty class. If so,
	// shutdown Pixie. We can do this by observing if the
	// state of the environment changes after a while or not.
	if (player->IsPlaying())
	{
		if (player->GetSum() > 21) // Player busted
		{
			// Give negative reward and end the game
			reward = -1.0f;

			has_ended = true;
			pixie::Core::Shutdown();
		}
	}
	else // Player chose to Stick
	{
		// Play out the dealers hand, and calculate player's reward
		while(dealer->GetSum() < 17)
			dealer->Hit();

		// utility lambda to calculate score of each side
		auto Score = [](int sum) -> int
		{
			return sum > 21 ? 0 : sum;
		};

		int player_sum = player->GetSum();
		int dealer_sum = dealer->GetSum();

		reward = static_cast<float>(Score(player_sum) > Score(dealer_sum)) -
					   static_cast<float>(Score(player_sum) < Score(dealer_sum));

		// End the game
		has_ended = true;
		pixie::Core::Shutdown();
	}
}

void BlackjackGameManager::End()
{
}

int BlackjackGameManager::DrawCard()
{
	int card;

	if (with_replacement)
	{
		card = *deck_iterator;
		++deck_iterator;
	}
	else
	{
		// TODO(Ahura): Implement this
		card = 10;
	}
	return card;
}

