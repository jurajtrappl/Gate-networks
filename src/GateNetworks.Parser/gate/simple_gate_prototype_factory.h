#pragma once

#include "components/simple_gate.h"

namespace gate_networks::parser::gate
{
	typedef std::unique_ptr<core::components::SimpleGate> Simple_gate_unique_ptr;

	/// <summary>
	/// Contains prototypes of defined simple gates from the input file.
	/// </summary>
	class SimpleGatePrototypeFactory
	{
	public:
		SimpleGatePrototypeFactory() : prototypes_()
		{
		}

		/// <returns>number of prototypes.</returns>
		int64_t count() const
		{
			return prototypes_.size();
		}

		/// <param name="name">name of the prototype.</param>
		/// <returns>inidicator if factory has a prototype with the specified name.</returns>
		bool contains(const std::string& name);

		/// <summary>
		/// Adds a new prototype to the factory.
		/// </summary>
		/// <param name="new_prototype">pointer to the new prototype.</param>
		void register_prototype(Simple_gate_unique_ptr new_prototype);

		/// <summary>
		/// Create a clone of the existing prototype with the specified name.
		/// </summary>
		/// <param name="name">name of the prototype.</param>
		/// <returns>shallow copy of the required prototype.</returns>
		Simple_gate_unique_ptr create(const std::string& name);
	private:
		typedef std::map<std::string, Simple_gate_unique_ptr> Simple_gate_prototypes_map;

		Simple_gate_prototypes_map prototypes_;
	};
}
