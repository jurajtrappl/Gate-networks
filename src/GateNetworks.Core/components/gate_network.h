#pragma once

#include "simple_gate.h"

namespace gate_networks::core::components
{
	typedef std::shared_ptr<SimpleGate> Simple_gate_shared_ptr;
	typedef std::map<std::string, Simple_gate_shared_ptr> Simple_gate_shared_ptrs_map;
	typedef std::vector<Simple_gate_shared_ptr> Simple_gate_shared_ptrs_list;

	class GateNetwork;

	/// <summary>
	/// Declares a visiting method that correspond to the GateNetwork class.
	/// </summary>
	class IVisitor
	{
	public:
		virtual ~IVisitor()
		{
		}

		/// <summary>
		/// Compute algorithm for gate network.
		/// </summary>
		/// <param name="gate_network">gate network to compute.</param>
		/// <param name="command_tokens">input values for the gate network inputs.</param>
		virtual void visit(GateNetwork& gate_network, const std::vector<logic::Tri_state>& command_tokens) = 0;
	};

	/// <summary>
	/// Represents a collection of inter-connected simple gates, inputs and outputs.
	/// Can produce a result, stored in its outputs, based on specified input values.
	/// </summary>
	class GateNetwork
	{
	public:
		GateNetwork();

		/// <param name="name">name of the gate to check.</param>
		/// <returns>indicator if the network contains a gate with the specified name.</returns>
		bool contains_inner_gate(const std::string& name) const;

		/// <param name="name">name of the gate to return.</param>
		/// <returns>shared_ptr to the simple gate that has the specified name.</returns>
		Simple_gate_shared_ptr inner_gate_by_name(const std::string& name);

		/// <summary>
		/// Inserts the specified gate with the specified name to the network.
		/// </summary>
		/// <param name="name">name of the gate.</param>
		/// <param name="gate">gate to be inserted.</param>
		void add_inner_gate(const std::string& name, Simple_gate_shared_ptr gate);

		/// <summary>
		/// Evaluation of the gate network for the given command. (AComputable implementation)
		/// </summary>
		void compute(IVisitor* visitor, const std::vector<logic::Tri_state>& command_tokens);

		/// <summary>
		/// Increase tact number by 1.
		/// </summary>
		void increment_tact_count();

		/// <summary>
		/// Sets the tact count to 0.
		/// </summary>
		void reset_tact_count();

		/// <returns>implicit inputs of the gate network.</returns>
		IOInstances& implicit_inputs();
		
		/// <returns>inputs of the gate network.</returns>
		IOInstances& inputs();

		/// <returns>outputs of the gate network.</returns>
		std::shared_ptr<IOInstances> outputs();

		/// <returns>gate network inner gates.</returns>
		Simple_gate_shared_ptrs_map& inner_gates();

		/// <returns>gate network constant gates.</returns>
		Simple_gate_shared_ptrs_list& constant_gates();

		/// <returns>list of unconnected outputs.</returns>
		std::vector<std::string>& unconnected_outputs();

		/// <returns>number of the current tact.</returns>
		int tact_count() const;
	private:
		IOInstances implicit_inputs_;
		IOInstances inputs_;
		std::shared_ptr<IOInstances> outputs__;
		Simple_gate_shared_ptrs_map inner_gates_;
		Simple_gate_shared_ptrs_list constant_gates_;
		std::vector<std::string> unconnected_outputs_;
		int tact_count_;
	};
}