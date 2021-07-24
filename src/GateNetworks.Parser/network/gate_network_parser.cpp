#include "gate_network_parser.h"
#include "../input_file_exceptions.h"
#include "string_extensions.h"
#include "connection_definitions.h"
#include "connection_parser.h"

using namespace std;
using namespace gate_networks::util;


namespace gate_networks::parser::network
{
	void GateNetworkParser::process()
	{
		// for duplicates
		vector<string> connections;

		while (getline(is_, line_) && !StringExtensions::is_end(line_))
		{
			current_line_number_++;

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
				auto inputs_def = NetworkInputsDefinition(tokens_, current_line_number_);
				inputs_def.assign(gate_network_);

				inputs_loaded_ = true;
				continue;
			}

			if (StringExtensions::is_outputs_definition(line_) && inputs_loaded_)
			{
				auto outputs_def = NetworkOutputsDefinition(tokens_, current_line_number_);
				outputs_def.assign(gate_network_);

				outputs_loaded_ = true;
				continue;
			}

			// Missing keyword: outputs
			if (StringExtensions::is_gate_definition(line_) && !outputs_loaded_)
			{
				throw MissingKeywordException(current_line_number_);
			}

			if (StringExtensions::is_gate_definition(line_))
			{
				auto gate_def =
					NetworkGateDefinition(
						tokens_,
						gate_network_->inner_gates(),
						current_line_number_,
						prototypes_);

				gate_def.assign(gate_network_);

				continue;
			}

			if (StringExtensions::is_connection_definition(line_))
			{
				auto connection_def =
					NetworkConnectionDefinition(
						connections,
						line_,
						gate_network_->inner_gates(),
						current_line_number_);
				connection_def.assign(gate_network_);

				connections.push_back(line_);

				continue;
			}

			throw SyntaxException(current_line_number_);
		}

		current_line_number_++;
		
		if (connections.size() == 0)
		{
			throw SyntaxException(current_line_number_);
		}

		if (gate_network_->unconnected_outputs().size() != 0)
		{
			throw BindingRuleException(current_line_number_);
		}
	}
}