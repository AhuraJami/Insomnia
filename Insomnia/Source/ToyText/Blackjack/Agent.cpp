#include "Insomnia/ToyText/Blackjack/Agent.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>

#include <Pixie/Core/ObjectInitializer.h>
#include <Pixie/Misc/Placeholders.h>
#include <Insomnia/ToyText/Blackjack/Agent.h>


#include "Insomnia/ToyText/Blackjack/GameManager.h"

using namespace insomnia::blackjack;
using namespace pixie;

Agent::Agent()
{
	// Register a placeholder for the controller
	ObjectInitializer::ConstructPObject<ConceptPlaceHolder>(&controller);
}

void Agent::Reset()
{
	cards.clear();
	sum = 0;
	has_usable_ace = false;
	is_playing = true;
}

void Agent::End()
{
	Reset();
}

void Agent::Hit()
{
	auto* gm = ObjectInitializer::GetGameManager<BlackjackGameManager>();

	// draw a card from the unique deck held in GameManager
	cards.emplace_back(gm->DrawCard());

	// Sum up the cards that are in the hand while also considering
	// whether the we can use the ace or not (if any)
	sum = std::accumulate(cards.begin(), cards.end(), 0);
	if (has_usable_ace = CheckForUsableAce(sum); has_usable_ace)
		sum += 10;
}

void Agent::Stick()
{
	is_playing = false;
}

float Agent::GetReward() const
{
	return ObjectInitializer::GetGameManager<BlackjackGameManager>()->GetReward();
}

bool Agent::CheckForUsableAce(int sum) const
{
	if (std::find(cards.begin(), cards.end(), 1) != cards.end())
	{
		return sum + 10 <= 21;
	}
	return false;
}

std::tuple<int, int, bool> Agent::GetObservation() const
{
	auto gm = pixie::ObjectInitializer::GetGameManager<BlackjackGameManager>();
	int dealer_fu_card = gm->GetDealerFaceUpCard();
	return std::make_tuple(sum, dealer_fu_card, has_usable_ace);
}


std::tuple<int, int, bool, int> Agent::GetFinalObservation() const
{
	auto gm = pixie::ObjectInitializer::GetGameManager<BlackjackGameManager>();
	if (gm->HasGameEnded())
	{
		int dealer_sum = gm->GetDealerSum();
		return std::tuple_cat(GetObservation(), std::make_tuple(dealer_sum));
	}
	else
	{
		// TODO(Ahura): Move to a static class so we don't have to retype this message
		// for every single environment.
		std::cerr
		<< "WARNING: Invalid use of GetFinalObservation(). Game is not finished yet. "
		<< "You can only use this function in the End() method of your controller.\n";
		std::flush(std::cerr);

		return std::make_tuple(0, 0, false, 0);
	}
}
