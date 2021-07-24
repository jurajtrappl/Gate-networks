#pragma once

#include "../components/gate_network.h"

namespace gate_networks::core::evaluation
{
	/// <summary>
	/// Gate network compute algorithm.
	/// </summary>
	class CommandVisitor : public components::IVisitor
	{
	public:
		/// <summary>
		/// Contains implementation of gate network compute algorithm.
		/// </summary>
		/// <param name="gate_network">gate network to compute.</param>
		/// <param name="command_tokens">input values of the gate network.</param>
		void visit(components::GateNetwork& gate_network, const std::vector<logic::Tri_state>& command_tokens);
	private:
		/// <summary>
		/// Maximum number of tacts during the computation.
		/// </summary>
		const int max_tact = 1000000;

		/// <summary>
		/// Sends values from every input gate and every constant gate through its connections.
		/// </summary>
		void send_initial(components::GateNetwork& gate_network);

		/// <summary>
		/// Evaluates the inputs of every gate in the network that had changed its inputs.
		/// </summary>
		void compute_changed_gates(components::GateNetwork& gate_network, bool& found);

		/// <summary>
		/// Send values from outputs to inputs.
		/// </summary>
		void send_computed(components::GateNetwork& gate_network);
	};
}