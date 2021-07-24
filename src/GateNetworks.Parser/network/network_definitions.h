#pragma once

#include "components/gate_network.h"
#include "../gate/simple_gate_prototype_factory.h"

namespace gate_networks::parser::network
{
	/// <summary>
	/// Definition of inputs in the gate network definition block.
	/// </summary>
	class NetworkInputsDefinition
	{
	public:
		NetworkInputsDefinition(const std::vector<std::string>&, int);

		/// <summary>
		/// Adds inputs from the definition to the gate network instance.
		/// </summary>
		/// <param name="gate">gate network to which the inputs are added.</param>
		void assign(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::vector<std::string> inputs_;
	};

	/// <summary>
	/// Definition of outputs in the gate network definition block.
	/// </summary>
	class NetworkOutputsDefinition
	{
	public:
		NetworkOutputsDefinition(const std::vector<std::string>&, int);

		/// <summary>
		/// Adds outputs from the definition to the gate network instance.
		/// </summary>
		/// <param name="gate">gate network to which the outputs are added.</param>
		void assign(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::vector<std::string> outputs_;
	};

	/// <summary>
	/// Definition of gate instance in the gate network definition block.
	/// </summary>
	class NetworkGateDefinition
	{
	public:
		NetworkGateDefinition(
			const std::vector<std::string>&,
			core::components::Simple_gate_shared_ptrs_map&,
			int,
			gate::SimpleGatePrototypeFactory*);

		/// <summary>
		/// Adds gate from the definition to the gate network instance.
		/// </summary>
		/// <param name="gate">gate network to which the gate is added.</param>
		void assign(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::string name_;
		std::string type_;
		int current_line_number_;
		gate::SimpleGatePrototypeFactory* prototypes_;
	};

	/// <summary>
	/// Definition of connection in the gate network definition block.
	/// </summary>
	class NetworkConnectionDefinition
	{
	public:
		NetworkConnectionDefinition(
			const std::vector<std::string>& connections,
			const std::string& line,
			const core::components::Simple_gate_shared_ptrs_map& inner_gates,
			int current_line);

		/// <summary>
		/// Adds connections from the definition to the gate network instance.
		/// </summary>
		/// <param name="gate">gate network to which the connection is added.</param>
		void assign(std::shared_ptr<core::components::GateNetwork> gate_network);
	private:
		int current_line_number_;
		std::string connection_def;
	};

	/// <summary>
	/// Wrapper for connection definition content.
	/// </summary>
	class ArrowTokens
	{
	public:
		// for connections
		ArrowTokens()
		{
		}

		ArrowTokens(const std::string&, int);

		/// <returns>connection definition content on the left side of the arrow.</returns>
		const std::vector<std::string>& left() const;

		/// <returns>connection definition content on the right side of the arrow.</returns>
		const std::vector<std::string>& right() const;
	private:
		std::vector<std::string> left_;
		std::vector<std::string> right_;
	};
}