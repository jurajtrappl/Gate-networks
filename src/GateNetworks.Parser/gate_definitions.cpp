#include "gate_definitions.h"
#include "container_extensions.h"
#include "string_extensions.h"
#include "input_file_exceptions.h"

using namespace std;

namespace gate_networks::parser::gate 
{
	SimpleGateInputsDefinition::SimpleGateInputsDefinition(const vector<string>& tokens, int current_line_number)
	{
		if (tokens.size() != util::ContainerExtensions<vector<string>>::count_distinct(tokens))
		{
			throw DuplicateException(current_line_number);
		}

		inputs_ = tokens;
	}

	void SimpleGateInputsDefinition::assign(core::components::SimpleGate* gate)
	{
		for (auto&& i : inputs_)
		{
			gate->inputs().push_back(i);
		}
	}

	SimpleGateOutputsDefinition::SimpleGateOutputsDefinition(const vector<string>& tokens, int current_line_number)
	{
		if (tokens.size() < 1)
		{
			throw SyntaxException(current_line_number);
		}

		if (tokens.size() != util::ContainerExtensions<vector<string>>::count_distinct(tokens))
		{
			throw DuplicateException(current_line_number);
		}

		outputs_ = tokens;
	}

	void SimpleGateOutputsDefinition::assign(core::components::SimpleGate* gate) 
	{
		for (auto&& o : outputs_)
		{
			gate->outputs().push_back(o);
		}
	}

	void SimpleGateFunctionDefinition::to_tri_state(const vector<string>& tokens, vector<core::logic::Tri_state>& values)
	{
		for (auto&& t : tokens)
		{
			if (!util::StringExtensions::is_tri_state(t)) 
			{
				throw SyntaxException(current_line_number_);
			}
			
			values.push_back(core::logic::Tri_state{ t });
		}
	}

	void SimpleGateFunctionDefinition::divide_to_inputs_and_outputs(
		const vector<core::logic::Tri_state>& f_def_as_values,
		size_t inputs_size)
	{
		int i = 0;
		for (; i < inputs_size; i++)
		{
			input_values_.push_back(f_def_as_values[i]);
		}
		for (; i < f_def_as_values.size(); i++)
		{
			output_values_.push_back(f_def_as_values[i]);
		}
	}

	SimpleGateFunctionDefinition::SimpleGateFunctionDefinition(
		const string& line,
		int current_line_number,
		core::components::SimpleGate* gate)
	{
		vector<string> tokens;
		util::ContainerExtensions<vector<string>>::split(line, tokens);

		// check size
		if ((tokens.size() != (gate->inputs().size() + gate->outputs().size())))
		{
			throw SyntaxException(current_line_number);
		}

		// check values
		current_line_number_ = current_line_number;

		// convert from strings to tri state
		vector<core::logic::Tri_state> values;
		to_tri_state(tokens, values);

		divide_to_inputs_and_outputs(values, gate->inputs().size());

		if (gate->functions().contains(input_values_))
		{
			throw DuplicateException(current_line_number);
		}		
	}

	void SimpleGateFunctionDefinition::assign(core::components::SimpleGate* gate)
	{
		gate->functions().add(input_values_, output_values_);
	}
}