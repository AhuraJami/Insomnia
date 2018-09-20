#ifndef INSOMNIA_TOY_TEXT_BLACKJACK_BLACKJACK_H
#define INSOMNIA_TOY_TEXT_BLACKJACK_BLACKJACK_H

#include <Pixie/Core/Core.h>
#include <Pixie/Core/ObjectInitializer.h>

#include "Insomnia/ToyText/Blackjack/GameManager.h"
#include "Insomnia/ToyText/Blackjack/Agent.h"
#include "Insomnia/Core/Insomnia.h"
#include "Insomnia/Core/Environments.h"

namespace insomnia::blackjack
{

INSOMNIA_EXPORT void Initialize()
{
	using namespace pixie;

	// Initialize pixie's core
	Core::Initialize();

	// Set insomnia's active environment to Blackjack
	Insomnia::Activate(Environments::Blackjack);

	// Add game_manager and the agents to pixie's scene
	auto* game_manager = ObjectInitializer::ConstructGameManager<BlackjackGameManager>();
	auto* player = ObjectInitializer::ConstructEntity<Agent>();

	// Note: Since this environment is very small, we use the same agent class even for the
	// AI (i.e., the dealer). This is fine because our simple Agent doesn't implement Tick()
	// concept, so no updates are made to the dealer.
	// You might ask why delegate the construction to Pixie? The answer is that the Agent
	// uses one of the Pixie's core objects (i.e. PObject) as a placeholder for the controller.
	// In order to register the controller for ticking, the Agent has to delegate the construction of
	// the controller placeholder to Pixie. Since, this is a dependant component of the Agent
	// who delegated its construction to Pixie, The Agent itself (and in general all of the
	// outer classes of a component) must delegate their construction to Pixie as well, so
	// Pixie can properly form their execution graph.
	auto* dealer = ObjectInitializer::ConstructEntity<Agent>();

	// Store a pointer to dealer and player in the game manager for game logic control
	game_manager->SetPlayer(player);
	game_manager->SetDealer(dealer);
}

INSOMNIA_EXPORT Agent* GetAgent()
{
	return pixie::ObjectInitializer::GetGameManager<BlackjackGameManager>()->GetPlayerAgent();
}

INSOMNIA_EXPORT void AttachController(pixie::PObject controller)
{
	GetAgent()->AttachController(std::move(controller));
}

} // namespace insomnia::blackjack

#endif // INSOMNIA_TOY_TEXT_BLACKJACK_BLACKJACK_H
