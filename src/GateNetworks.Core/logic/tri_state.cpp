#include "tri_state.h"
#include <iostream>
#include <sstream>

namespace gate_networks::core::logic
{
	Tri_state::Tri_state(const std::string& val)
	{
		if (val == "?")
		{
			value = std::nullopt;
		}
		else
		{
			bool b;
			std::istringstream(val) >> b;
			value = b;
		}
	}

	bool Tri_state::operator==(const Tri_state& second) const
	{
		return value == second.value;
	}

	std::ostream& operator<<(std::ostream& os, Tri_state state)
	{
		if (state.value == std::nullopt)
		{
			os << '?';
		}
		else
		{
			os << std::noboolalpha << state.value.value();
		}

		return os;
	}
}