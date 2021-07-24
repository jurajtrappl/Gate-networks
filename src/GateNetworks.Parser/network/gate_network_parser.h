#pragma once

#include "../reader_base.h"
#include "../gate/simple_gate_prototype_factory.h"
#include "network_definitions.h"
#include "components/gate_network.h"

namespace gate_networks::parser::network
{
	typedef std::vector<std::string> StringList;

	/// <summary>
	/// Contains logic for parsing a gate network.
	/// </summary>
	class GateNetworkParser : public ReaderBase
	{
	public:
		GateNetworkParser(
			std::istream& is,
			int& current_line_number,
			gate::SimpleGatePrototypeFactory* prototypes,
			std::shared_ptr<core::components::GateNetwork> gate_network)
			: ReaderBase(is)
			, current_line_number_(current_line_number)
			, gate_network_(gate_network)
			, inputs_loaded_(false)
			, outputs_loaded_(false)
			, prototypes_(prototypes)
		{
		}

		/// <summary>
		/// Reads gate network definition block.
		/// </summary>
		void process();
	private:
		int& current_line_number_;
		std::shared_ptr<core::components::GateNetwork> gate_network_;
		bool inputs_loaded_;
		bool outputs_loaded_;
		gate::SimpleGatePrototypeFactory* prototypes_;
	};
}