#ifndef PROJECT_INSOMNIA_H
#define PROJECT_INSOMNIA_H

#include <Pixie/Core/Core.h>

#include "Insomnia/Misc/InsomniaExports.h"
#include "Insomnia/Core/Environments.h"

namespace insomnia
{

class Insomnia
{
public:

	// This is to prevent user from adding another environment and
	// potentially polluting pixie's core without first deleting what's
	// already there.
	static void Activate(Environments type)
	{
		if (not status.is_active)
		{
			status.type = type;
			status.is_active = true;
		}
		else
		{
			// TODO(Ahura): Print a friendly warning
		}
	}

	static void Deactivate()
	{
		if (status.is_active)
		{
			status.is_active = false;
		}
		else
		{
			// TODO(Ahura): Print a friendly warning
		}
	}

	static bool IsActive()
	{
		return status.is_active;
	}

private:
	static EnvironmentStatus status;
};

EnvironmentStatus Insomnia::status{};



// TODO(Ahura): Add feature to automatically release resources of the active environment and
// initialize another environment
INSOMNIA_EXPORT void Start(int num_runs)
{
	// TODO(Ahura): Also check if a controller was attached, warn the user if not.
	if (not Insomnia::IsActive())
	{
		std::cout << "First set an active environment" << std::endl;
		return;
	}

	// TODO(Ahura): Report what active environment is
	while (num_runs--)
		pixie::Core::Start();
}

} // namespace insomnia

#endif //PROJECT_INSOMNIA_H
