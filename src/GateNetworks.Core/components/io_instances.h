#pragma once

#include "connection.h"

#include <map>

namespace gate_networks::core::components
{
	typedef std::map<std::string, logic::Tri_state> IO_instances_map;

	/// <summary>
	/// Represents a collection of "boxes" that contain a tri state logic value.
	/// "Boxes" can be connected to any other AConnectible.
	/// </summary>
	class IOInstances : public AConnectible
	{
	public:
		IOInstances() : instances_()
		{
		}

		IOInstances(IO_instances_map states) : instances_(states)
		{
		}

		/// <summary>
		/// Adds a new instance with the specified name and value.
		/// </summary>
		/// <param name="">name of the state.</param>
		/// <param name="">value of the state.</param>
		void push_back(const std::string&, logic::Tri_state = logic::Tri_state{ std::nullopt });

		/// <param name="">name of the instance.</param>
		/// <returns>tri state logic value of the instance with the specified name.</returns>
		logic::Tri_state instance_by_name(const std::string&);

		/// <param name="">name of the instance.</param>
		/// <returns>indicator if the instance is present.</returns>
		bool contains(const std::string&) const;

		/// <returns>indicator if any instance value is undefined.</returns>
		bool contains_undefined() const;

		/// <summary>
		/// Sets a new value for the instance with the specified name.
		/// </summary>
		/// <param name="">name of the instance.</param>
		/// <param name="">new value for the instance.</param>
		void new_state_for(const std::string&, logic::Tri_state);

		/// <summary>
		/// Set the same value for each instance.
		/// </summary>
		/// <param name="">new value for all instances.</param>
		void all_new_unified_state(logic::Tri_state);

		/// <summary>
		/// Set values of the instances according to the specified values.
		/// </summary>
		/// <param name="">values for instances.</param>
		void all_new_specified_states(const std::vector<logic::Tri_state>&);

		/// <returns>values of the instances joined by the space.</returns>
		std::string stringify() const;

		/// <returns>number of instances.</returns>
		size_t size() const;

		/// <summary>
		/// Get values from instances as vector.
		/// </summary>
		void extract_values_to(std::vector<logic::Tri_state>& values);

		// AConnectible implementation
		void send();

		// AConnectible implementation
		void change_state(const std::string&, logic::Tri_state);
	private:
		IO_instances_map instances_;
	};
}
