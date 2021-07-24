#include "context_definitions.h"
#include "string_extensions.h"
#include "input_file_exceptions.h"
#include "gate/simple_gate_parser.h"
#include "network/gate_network_parser.h"

using namespace std;

namespace gate_networks::parser
{
	GatePrototypeDefinition::GatePrototypeDefinition(
		const vector<string>& tokens,
		int& current_line_number,
		gate::SimpleGatePrototypeFactory* prototypes)
		: current_line_number_(current_line_number)
	{
		if (tokens.size() != 1 || !util::StringExtensions::is_correct_name(tokens[0]))
		{
			throw SyntaxException(current_line_number);
		}

		if (prototypes->contains(tokens[0]))
		{
			throw DuplicateException(current_line_number);
		}

		name_ = tokens[0];
		prototypes_ = prototypes;
	}

	void GatePrototypeDefinition::assign(istream& is)
	{
		gate::SimpleGateParser parser(is, current_line_number_, name_);
		prototypes_->register_prototype(move(parser.process()));
	}

	GateNetworkDefinition::GateNetworkDefinition(
		int& current_line_number,
		gate::SimpleGatePrototypeFactory* prototypes)
		: current_line_number_(current_line_number)
	{
		if (prototypes->count() < 1)
		{
			throw SyntaxException(current_line_number);
		}

		prototypes_ = prototypes;
	}

	void GateNetworkDefinition::assign(istream& is, shared_ptr<core::components::GateNetwork> gate_network)
	{
		network::GateNetworkParser parser(is, current_line_number_, prototypes_, gate_network);
		parser.process();
	}
}