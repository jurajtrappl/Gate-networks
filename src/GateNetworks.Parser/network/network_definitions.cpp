#include "network_definitions.h"
#include "container_extensions.h"
#include "../gate/simple_gate_prototype_factory.h"
#include "../input_file_exceptions.h"
#include "connection_parser.h"

using namespace std;
using namespace gate_networks::util;

namespace gate_networks::parser::network
{
	NetworkInputsDefinition::NetworkInputsDefinition(const vector<string>& tokens, int current_line_number)
	{
		if (tokens.size() < 1 || tokens[0] == "")
		{
			throw SyntaxException(current_line_number);
		}

		if (tokens.size() != ContainerExtensions<vector<string>>::count_distinct(tokens))
		{
			throw DuplicateException(current_line_number);
		}

		inputs_ = tokens;
	}

	void NetworkInputsDefinition::assign(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		for (auto&& i : inputs_)
		{
			gate_network->inputs().push_back(i);
		}
	}

	NetworkOutputsDefinition::NetworkOutputsDefinition(const vector<string>& tokens, int current_line_number)
	{
		if (tokens.size() < 1)
		{
			throw SyntaxException(current_line_number);
		}

		if (tokens.size() != ContainerExtensions<vector<string>>::count_distinct(tokens))
		{
			throw DuplicateException(current_line_number);
		}

		outputs_ = tokens;
	}

	void NetworkOutputsDefinition::assign(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		for (auto&& o : outputs_)
		{
			gate_network->outputs()->push_back(o);

			// each one is unconnected so far
			gate_network->unconnected_outputs().push_back(o);
		}
	}

	NetworkGateDefinition::NetworkGateDefinition(
		const vector<string>& tokens,
		core::components::Simple_gate_shared_ptrs_map& inner_gates,
		int current_line_number,
		gate::SimpleGatePrototypeFactory* prototypes)
	{
		if (tokens.size() != 2)
		{
			throw MissingKeywordException(current_line_number);
		}

		if (inner_gates.find(tokens[0]) != inner_gates.end())
		{
			throw DuplicateException(current_line_number);
		}

		name_ = tokens[0];
		type_ = tokens[1];
		current_line_number_ = current_line_number;
		prototypes_ = prototypes;
	}

	void NetworkGateDefinition::assign(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		if (prototypes_->contains(type_))
		{
			// unique pointer to the new type of a gate
			auto cloned_prototype = prototypes_->create(type_);

			// making the pointer shared since more inputs/outputs can be connected to this gate instance
			std::shared_ptr<core::components::SimpleGate> node = move(cloned_prototype);

			gate_network->add_inner_gate(name_, node);
			return;
		}

		throw SyntaxException(current_line_number_);
	}

	NetworkConnectionDefinition::NetworkConnectionDefinition(
		const vector<string>& connections,
		const string& line,
		const core::components::Simple_gate_shared_ptrs_map& inner_gates,
		int current_line_number)
	{
		if (inner_gates.size() == 0)
		{
			throw SyntaxException(current_line_number);
		}

		if (count(connections.begin(), connections.end(), line) >= 1)
		{
			throw DuplicateException(current_line_number);
		}

		current_line_number_ = current_line_number;
		connection_def = line;
	}

	void NetworkConnectionDefinition::assign(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		auto tokens = ArrowTokens(connection_def, current_line_number_);

		auto connection_parser = ConnectionParser(current_line_number_);
		connection_parser.set_strategy(
			Connection_type_key(
				tokens.left().size(),
				tokens.right().size()));
		connection_parser.configure_strategy(tokens);
		connection_parser.process(gate_network);
	}

	ArrowTokens::ArrowTokens(const string& line, int current_line_number)
	{
		std::vector<std::string> tokens;
		ContainerExtensions<vector<string>>::split(line, tokens, "->");

		tokens.erase(
			remove_if(
				tokens.begin(),
				tokens.end(),
				[](const string& s) { return s.size() == 0; }),
			tokens.end());

		if (tokens.size() != 2)
		{
			throw BindingRuleException(current_line_number);
		}

		ContainerExtensions<vector<string>>::split(tokens[0], left_, ".");
		ContainerExtensions<vector<string>>::split(tokens[1], right_, ".");
	}

	const std::vector<std::string>& ArrowTokens::left() const
	{
		return left_;
	}

	const std::vector<std::string>& ArrowTokens::right() const
	{
		return right_;
	}
}