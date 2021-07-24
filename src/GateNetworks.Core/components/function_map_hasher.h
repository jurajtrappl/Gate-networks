#pragma once

#include "../logic/tri_state.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace std
{
	typedef vector<gate_networks::core::logic::Tri_state> Tri_state_values;

	/// <summary>
	/// Custom hash for unordered map with key Tri_state_values.
	/// Unordered map holds function definitions as pairs, keys are
	/// input values and values are outputs values (both as Tri_state_values).
	/// </summary>
	template<>
	struct hash<Tri_state_values>
	{
		size_t operator()(const Tri_state_values& instances) const
		{
			size_t h = 0;
			for (auto&& s : instances)
			{
				h = h << 1;
				if (s.value)
				{
					h += 1;
				}
			}
			return h;
		}
	};
}