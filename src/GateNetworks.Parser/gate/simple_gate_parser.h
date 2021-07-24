#pragma once

#include "components/simple_gate.h"
#include "../reader_base.h"

namespace gate_networks::parser::gate
{
	typedef std::unique_ptr<core::components::SimpleGate> Simple_gate_unique_ptr;

	/// <summary>
	/// Contains logic for parsing a simple gate.
	/// </summary>
	class SimpleGateParser : public ReaderBase
	{
	public:
		SimpleGateParser(
			std::istream& is,
			int& current_line_number,
			const std::string& name)
			: ReaderBase(is)
			, gate_(new core::components::SimpleGate(name))
			, current_line_number_(current_line_number)
			, inputs_loaded_(false)
			, outputs_loaded_(false)
			, was_end_(false)
		{
		}

		/// <summary>
		/// Reads gate definition block.
		/// </summary>
		/// <returns>unique pointer on newly parsed gate.</returns>
		Simple_gate_unique_ptr process();
	private:
		int& current_line_number_;
		core::components::SimpleGate* gate_;
		bool inputs_loaded_;
		bool outputs_loaded_;
		bool was_end_;
	};
}