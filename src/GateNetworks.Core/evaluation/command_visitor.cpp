#include "command_visitor.h"
#include <iostream>

using namespace std;

namespace gate_networks::core::evaluation
{
	void CommandVisitor::visit(
		components::GateNetwork& gate_network,
		const std::vector<logic::Tri_state>& command_tokens)
	{
		gate_network.inputs().all_new_specified_states(command_tokens);
		send_initial(gate_network);

		bool found;
		gate_network.reset_tact_count();
		while (gate_network.tact_count() != max_tact) {
			found = false;

			compute_changed_gates(gate_network, found);

			send_computed(gate_network);

			if (!found) {
				return;
			}

			gate_network.increment_tact_count();
		}
	}

	void CommandVisitor::send_initial(components::GateNetwork& gate_network) {
		for (auto&& constant_gate : gate_network.constant_gates()) {
			constant_gate->send();
		}

		gate_network.implicit_inputs().send();
		gate_network.inputs().send();
	}

	void CommandVisitor::compute_changed_gates(components::GateNetwork& gate_network, bool& found) {
		for (auto&& inner_gate : gate_network.inner_gates()) {
			if (inner_gate.second->changed_in_previous()) {
				found = true;
				inner_gate.second->compute();
			}
		}
	}

	void CommandVisitor::send_computed(components::GateNetwork& gate_network) {
		for (auto&& inner_gate : gate_network.inner_gates()) {
			inner_gate.second->send();
		}
	}
}