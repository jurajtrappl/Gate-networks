#pragma once

#include "gate/simple_gate_prototype_factory.h"
#include "gate/simple_gate_parser.h"
#include "components/gate_network.h"

#include <string>
#include <vector>

namespace gate_networks::parser
{
	/// <summary>
	/// Definition of a gate prototype in the input file.
	/// </summary>
	class GatePrototypeDefinition {
	public:
		GatePrototypeDefinition(const std::vector<std::string>&, int&, gate::SimpleGatePrototypeFactory*);
		
		/// <summary>
		/// Processes gate prototype definition and parses a new gate prototype.
		/// </summary>
		/// <param name="is">the input file.</param>
		void assign(std::istream& is);
	private:
		int& current_line_number_;
		std::string name_;
		gate::SimpleGatePrototypeFactory* prototypes_;
	};

	/// <summary>
	/// Definition of a gate network in the input file.
	/// </summary>
	class GateNetworkDefinition {
	public:
		GateNetworkDefinition(int&, gate::SimpleGatePrototypeFactory*);

		/// <summary>
		/// Processes gate network definition and parses gate network.
		/// </summary>
		/// <param name="is">the input file.</param>
		/// <param name="gate_network">resulting gate network.</param>
		void assign(std::istream& is, std::shared_ptr<core::components::GateNetwork> gate_network);
	private:
		int& current_line_number_;
		gate::SimpleGatePrototypeFactory* prototypes_;
	};
}