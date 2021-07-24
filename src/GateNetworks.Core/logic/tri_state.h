#pragma once

#include <optional>
#include <string>

namespace gate_networks::core::logic
{
	/// <summary>
	/// Representation of tri state logic.
	/// Values are true ('1'), false ('0') and undefined ('?').
	/// </summary>
	struct Tri_state
	{
		typedef std::optional<bool> Nullable_bool;

		Nullable_bool value;

		// Default constructor. (undefined value)
		Tri_state() : value(std::nullopt)
		{
		}

		// Init from std::optional<bool> value.
		Tri_state(Nullable_bool val) : value(val)
		{
		}

		// Init from std::string.
		Tri_state(const std::string&);

		friend std::ostream& operator<<(std::ostream&, Tri_state);
		bool operator==(const Tri_state&) const;
	};
}