#pragma once

#include "logic/tri_state.h"
#include <string>
#include <vector>

namespace gate_networks::application
{
	/// <summary>
	/// Wrapper over standard input user entered inputs for the gate network to evaluate for.
	/// </summary>
	class Command
	{
	public:
		Command(const std::string& tokens, size_t inputs_count);

		/// <returns>tri_state representation of command input.</returns>
		const std::vector<core::logic::Tri_state>& values() const;
	private:
		/// <summary>
		/// Processed tri state representation of command input.
		/// </summary>
		std::vector<core::logic::Tri_state> values_;
	};
}