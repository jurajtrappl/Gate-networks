#include "simple_gate_parser.h"
#include "string_extensions.h"
#include "container_extensions.h"
#include "components/simple_gate.h"
#include "../input_file_exceptions.h"
#include "../gate_definitions.h"

using namespace std;
using namespace gate_networks::util;

namespace gate_networks::parser::gate
{
	Simple_gate_unique_ptr SimpleGateParser::process()
	{
		while (getline(is_, line_) && !StringExtensions::is_end(line_))
		{
			current_line_number_++;

			if (line_.empty() && !was_end_)
			{
				throw MissingKeywordException(current_line_number_);
			}

			if (StringExtensions::can_be_ignored(line_))
			{
				continue;
			}

			tokenize();

			// Missing keyword: inputs
			if (StringExtensions::is_outputs_definition(line_) && !inputs_loaded_)
			{
				throw MissingKeywordException(current_line_number_);
			}

			if (StringExtensions::is_inputs_definition(line_) && !inputs_loaded_)
			{
				auto inputs_def = new SimpleGateInputsDefinition(tokens_, current_line_number_);
				inputs_def->assign(gate_);

				inputs_loaded_ = true;
				continue;
			}

			if (StringExtensions::is_outputs_definition(line_) && inputs_loaded_)
			{
				auto outputs_def = new SimpleGateOutputsDefinition(tokens_, current_line_number_);
				outputs_def->assign(gate_);

				outputs_loaded_ = true;
				continue;
			}

			// Missing keyword: outputs
			if (!StringExtensions::is_end(line_) && !outputs_loaded_)
			{
				throw MissingKeywordException(current_line_number_);
			}

			// Functions
			if (!StringExtensions::is_end(line_) && outputs_loaded_)
			{
				auto f_defintion = new SimpleGateFunctionDefinition(line_, current_line_number_, gate_);
				f_defintion->assign(gate_);

				continue;
			}

			throw SyntaxException(current_line_number_);
		}

		current_line_number_++;
		auto unique_ptr_gate = unique_ptr<core::components::SimpleGate>(gate_);
		return move(unique_ptr_gate);
	}
}