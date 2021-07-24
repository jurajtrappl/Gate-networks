#include "simple_gate.h"
#include "container_extensions.h"

using namespace std;
using namespace gate_networks::util;

namespace gate_networks::core::components
{
	SimpleGate::SimpleGate(const SimpleGate& old)
	{
		name_ = old.name_;
		functions_ = old.functions_;
		inputs_ = old.inputs_;
		outputs_ = old.outputs_;
	}

	Functions& SimpleGate::functions() 
	{
		return functions_;
	}

	IOInstances& SimpleGate::inputs()
	{
		return inputs_;
	}

	IOInstances& SimpleGate::outputs() 
	{
		return outputs_;
	}

	const string& SimpleGate::name()
	{
		return name_;
	}

	bool SimpleGate::changed_in_previous() const
	{
		return changed_in_previous_;
	}

	void SimpleGate::compute()
	{
		vector<logic::Tri_state> input_values;
		inputs_.extract_values_to(input_values);

		if (functions_.contains(input_values))
		{
			outputs_.all_new_specified_states(functions_.get(input_values));
		}
		else
		{
			auto new_state = 
				inputs_.contains_undefined()
					? logic::Tri_state{ std::nullopt }
					: logic::Tri_state{ std::optional<bool>(false) };

			outputs_.all_new_unified_state(new_state);
		}

		changed_in_previous_ = false;
	}

	void SimpleGate::send() {
		for (auto&& c : connections())
		{
			if (inputs_.contains(c.instance_from()))
			{
				c.change_state(
					c.instance_to(),
					inputs_.instance_by_name(c.instance_from()));
			}
			else
			{
				c.change_state(
					c.instance_to(),
					outputs_.instance_by_name(c.instance_from()));
			}
		}
	}

	void SimpleGate::change_state(const std::string& instance_name, logic::Tri_state new_state)
	{
		logic::Tri_state previous_state;

		if (inputs_.contains(instance_name))
		{
			previous_state = inputs_.instance_by_name(instance_name);
			if (new_state != previous_state)
			{
				inputs_.new_state_for(instance_name, new_state);
				changed_in_previous_ = true;
			}
		}
		else
		{
			previous_state = outputs_.instance_by_name(instance_name);
			if (new_state != previous_state)
			{
				outputs_.new_state_for(instance_name, new_state);
				changed_in_previous_ = true;
			}
		}
	}

	std::unique_ptr<SimpleGate> SimpleGate::clone()
	{
		return std::make_unique<SimpleGate>(*this);
	}
}