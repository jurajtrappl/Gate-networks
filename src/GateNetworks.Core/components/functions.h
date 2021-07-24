#pragma once

#include "function_map_hasher.h"

#include <unordered_map>
#include <string>

namespace gate_networks::core::components
{
	/// <summary>
	/// Gate function definitions wrapper.
	/// </summary>
	struct Functions 
	{
	public:
		/// <summary>
		/// Adds a new function.
		/// </summary>
		/// <param name="input_values"></param>
		/// <param name="output_values"></param>
		void add(const std::vector<logic::Tri_state>& input_values, const std::vector<logic::Tri_state>& output_values);

		/// <param name="values">inputs values to find the function for.</param>
		/// <returns>indicator if there is a function with the same input values as specified.</returns>
		bool contains(const std::vector<logic::Tri_state>& values);		

		/// <returns>outputs values for the specified input values.</returns>
		const std::vector<logic::Tri_state>& get(const std::vector<logic::Tri_state>& values);
	private:
		std::unordered_map<std::vector<logic::Tri_state>, std::vector<logic::Tri_state>> functions_;
	};
}