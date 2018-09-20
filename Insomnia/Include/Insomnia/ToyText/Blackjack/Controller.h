#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

class Controller
{
	void Tick()
	{
		// insomnia::blackjack::observe();

		// take action based on observation
		if (false)
		{
			// insomnia::blackjack::take_action(Blackjack::Actions::Hit);
			agent.Action(actions::Hit);
			agent.Hit();
		}
		else
		{
			// insomnia::blackjack::take_action(Blackjack::Actions::Stick);
			agent.Action(actions::Stick); // this is more general, easier to comprehend
			agent.Stick();
		}
	}
	void* agent = insomnia::GetAgent(insomnia::Environments::Blackjack);
	void* actions = insomnia::GetActions(insomnia::Environments::Blackjack);
//	void* player = insomnia::Blackjack::Player;
//	void* actions = insomnia::Blackjack::Player::Actions;
};

#endif //PROJECT_CONTROLLER_H
