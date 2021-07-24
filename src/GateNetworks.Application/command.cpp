#include "command.h"
#include "command_exceptions.h"
#include "../GateNetworks.Util/container_extensions.h"
#include "../GateNetworks.Util/string_extensions.h"

using namespace std;

namespace gate_networks::application
{
	Command::Command(const string& line, size_t inputs_count)
	{
        vector<string> tokens;
        util::ContainerExtensions<vector<string>>::split(line, tokens);

        if (tokens.size() != inputs_count)
        {
            throw core::CommandException("Syntax error.");
        }
        
        for (auto&& t : tokens)
        {
            if (!util::StringExtensions::is_tri_state(t))
            {
                throw gate_networks::core::CommandException("Syntax error.");
            }

            values_.push_back(core::logic::Tri_state{ t });
        }
	}

    const vector<core::logic::Tri_state>& Command::values() const
    {
        return values_;
    }
}