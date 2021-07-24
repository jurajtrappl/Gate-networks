#include "gate_network_evaluator.h"

using namespace std;

namespace gate_networks::application
{
	void GateNetworkEvaluator::reset()
	{
		core::logic::Tri_state undefined{ std::nullopt };

		// reset networks IO
		gate_network_->inputs().all_new_unified_state(undefined);
		gate_network_->outputs()->all_new_unified_state(undefined);

		// reset each inner gate IO
		for (auto&& inner_gate : gate_network_->inner_gates())
		{
			inner_gate.second->inputs().all_new_unified_state(undefined);
			inner_gate.second->outputs().all_new_unified_state(undefined);
		}
	}

	void GateNetworkEvaluator::evaluate_for_command(Command command)
	{
		gate_network_->compute(visitor, command.values());
	}


	pair<int, string> GateNetworkEvaluator::result()
	{
		return pair<int, string>(
			gate_network_->tact_count(),
			gate_network_->outputs()->stringify());
	}
}