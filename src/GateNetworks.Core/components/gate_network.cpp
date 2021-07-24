#include "gate_network.h"

using namespace std;

namespace gate_networks::core::components {
	GateNetwork::GateNetwork()
		: constant_gates_()
		, inner_gates_()
		, implicit_inputs_()
		, inputs_()
		, outputs__()
		, tact_count_(0)
		, unconnected_outputs_()
	{
		// add implicit gates
		implicit_inputs_.push_back("0", logic::Tri_state{ std::optional<bool>(false) });
		implicit_inputs_.push_back("1", logic::Tri_state{ std::optional<bool>(true) });
		outputs__ = make_shared<IOInstances>();
	}

	IOInstances& GateNetwork::implicit_inputs()
	{
		return implicit_inputs_;
	}

	IOInstances& GateNetwork::inputs()
	{ 
		return inputs_;
	}

	std::shared_ptr<IOInstances> GateNetwork::outputs()
	{
		return outputs__;
	}

	Simple_gate_shared_ptrs_map& GateNetwork::inner_gates()
	{
		return inner_gates_; 
	}

	Simple_gate_shared_ptrs_list& GateNetwork::constant_gates()
	{
		return constant_gates_;
	}

	int GateNetwork::tact_count() const
	{
		return tact_count_;
	}

	void GateNetwork::increment_tact_count()
	{
		tact_count_++;
	}

	void GateNetwork::reset_tact_count()
	{
		tact_count_ = 0;
	}

	std::vector<std::string>& GateNetwork::unconnected_outputs()
	{
		return unconnected_outputs_;
	}

	bool GateNetwork::contains_inner_gate(const string& name) const {
		return inner_gates_.find(name) != inner_gates_.end();
	}

	Simple_gate_shared_ptr GateNetwork::inner_gate_by_name(const string& name) {
		return inner_gates_[name];
	}

	void GateNetwork::compute(
		IVisitor* visitor,
		const vector<logic::Tri_state>& command_tokens)
	{
		visitor->visit(*this, command_tokens);
	}

	void GateNetwork::add_inner_gate(const string& name, Simple_gate_shared_ptr gate) {
		inner_gates_.emplace(pair<string, Simple_gate_shared_ptr>(name, gate));

		if (gate->inputs().size() == 0) {
			constant_gates_.push_back(gate);
		}
	}
}