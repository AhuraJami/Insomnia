#include <iostream>
#include <chrono>
#include <random>
#include <tuple>

#include "Insomnia/ToyText/Blackjack.h"

using namespace std;
using namespace insomnia::blackjack;

// TODO(Ahura): Move to a math library
// Set a random seed
auto Seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine Generator(Seed);

/**
 * A simple limit stochastic controller
 * @note You can name this class anything you want and you don't have to inherit from any other class.
 */
class Controller
{
	Agent* agent = GetAgent(); // insomnia::blackjack::GetAgent();

public:
	/**
	 * Called at the beginning of Game
	 * @note This method is optional, but if you were to implement this, it must have the same signature
	 * as following.
	 */
//	 void Begin() {}

	/**
	 * Called each iteration
	 * @note This method, with the exact sane signature as below, is required if you want your controller
	 * to Tick and be updated every iteration.
	 */
	void Tick()
	{
		// When this function is first called, we only have valid s1, a1 (there is no reward yet so it's 0)
		// At time step 1, we have s1, a1, r0
		// That's how you should store these values at the beginning of Tick() method
		// because The result of the action you choose in this iteration will become available
		// only in the next iteration. So, at time step 2, we will have s2, a2, r1
		auto observation = agent->GetObservation();

		// agent->GetFinalObservation(); /* No fatal error but calling this within Tick() is invalid and outputs an empty tuple */

		discrete_distribution<int> distribution;

		if (get<0>(observation) > 18)
			distribution = { 0.8, 0.2 };
		else
			distribution = { 0.2, 0.8 };

		if (int action = distribution(Generator); 0 == action)
		{
			agent->Hit();
		}
		else
		{
			agent->Stick();
		}
		// We will see the consequence of our action (observation), along with the reward of our action
		// in the next iteration (i.e., next time Tick() is called)
	}

	/**
	 * Called at the end of the game
	 * @note This method too is optional, but if you choose to implement this, it must have the same
	 * signature as below.
	 */
	void End()
	{
		// Get the final observation and reward at the end of this game
		auto observation = agent->GetFinalObservation();
		auto reward = agent->GetReward();

		// report or store them and done
		cout << boolalpha
		<< "Sum Cards: "   << get<0>(observation) << "\t"
		<< "Dealer Card: " << get<1>(observation) << "\t"
		<< "Usable Ace: "  << get<2>(observation) << "\t"
		<< "Dealer Sum: "  << get<3>(observation) << "\t"
		<< "Reward: "      << reward 			  << endl;
	}

	/**
	 * Resets the controller and prepares it for next run
	 * @note Neither Insomnia nor Pixie call this method. Fow now, it is up to you
	 * to implement this method and call it either at the beginning or at the end of
	 * the game.
	 * @note Since this method is not called by Insomnia or Pixie, the signature
	 * or name of this method doesn't have to be the same as below.
	 */
//	void Reset() { /* Reset the members you want for next run */ }
};

int main()
{
	insomnia::blackjack::Initialize();

	insomnia::blackjack::AttachController(Controller()); // Could've also passed it as a template argument, but going with this design for compatibility with Python
	int num_runs = 10;
	insomnia::Start(num_runs /* TODO(Ahura): more options */);

	/* TODO(Ahura): Other possibly useful methods to add to Insomnia */
	// auto env = insomnia::GetActiveEnvironment(); // Though what do we want to do with it?
	// insomnia::ReportActiveEnvironment(); // This can be a helpful method in Python
	// auto* ctrl = insomnia::blackjack::AttachController<Controller>()); // It probably wouldn't be possible to expose this method to Python
}