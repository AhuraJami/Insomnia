#ifndef PROJECT_ENVIRONMENTS_H
#define PROJECT_ENVIRONMENTS_H

enum class Environments
{
	Blackjack = 1
};

struct EnvironmentStatus
{
	bool is_active = false;
	Environments type{};
};

#endif //PROJECT_ENVIRONMENTS_H
