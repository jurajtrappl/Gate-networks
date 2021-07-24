#include "connection_definitions.h"
#include "../input_file_exceptions.h"

using namespace std;

namespace gate_networks::parser::network
{
	void InnerToInnerConnection::configure(const ArrowTokens& tokens, int current_line_number)
	{
		gate_to_name_ = tokens.left()[0];
		gate_to_input_name_ = tokens.left()[1];
		gate_from_name_ = tokens.right()[0];
		gate_from_output_name_ = tokens.right()[1];

		if (gate_from_output_name_.find('o') != string::npos
			&& gate_to_input_name_.find('o') != string::npos)
		{
			throw BindingRuleException(current_line_number);
		}

		if (gate_from_output_name_.find('i') != string::npos
			&& gate_to_input_name_.find('i') != string::npos)
		{
			throw BindingRuleException(current_line_number);
		}

		current_line_number_ = current_line_number;
	}

	void InnerToInnerConnection::connect(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		if (gate_network->contains_inner_gate(gate_from_name_)
			&& gate_network->contains_inner_gate(gate_to_name_))
		{
			auto from = gate_network->inner_gate_by_name(gate_from_name_);
			auto to = gate_network->inner_gate_by_name(gate_to_name_);

			if (from->outputs().contains(gate_from_output_name_) && to->inputs().contains(gate_to_input_name_))
			{
				core::components::Connection connection(gate_from_output_name_, to, gate_to_input_name_);
				from->add_connection(connection);
				return;
			}
		}

		throw SyntaxException(current_line_number_);
	}

	void InputToInnerConnection::configure(const ArrowTokens& tokens, int current_line_number)
	{
		gate_to_name_ = tokens.left()[0];
		gate_to_instance_name_ = tokens.left()[1];
		network_input_name_ = tokens.right()[0];
		current_line_number_ = current_line_number;
	}

	void InputToInnerConnection::connect(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		if (gate_network->inputs().contains(network_input_name_) &&
			gate_network->contains_inner_gate(gate_to_name_))
		{
			auto to = gate_network->inner_gate_by_name(gate_to_name_);

			if (to->inputs().contains(gate_to_instance_name_))
			{
				core::components::Connection connection(network_input_name_, to, gate_to_instance_name_);
				gate_network->inputs().add_connection(connection);
				return;
			}
		}

		throw SyntaxException(current_line_number_);
	}

	void InnerToOutputConnection::configure(const ArrowTokens& tokens, int current_line_number)
	{
		network_output_name_ = tokens.left()[0];
		gate_from_name_ = tokens.right()[0];
		gate_from_output_name_ = tokens.right()[1];

		if (gate_from_output_name_.find('i') != string::npos)
		{
			throw BindingRuleException(current_line_number);
		}

		current_line_number_ = current_line_number;
	}

	void InnerToOutputConnection::connect(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		if (gate_network->outputs()->contains(network_output_name_) &&
			gate_network->contains_inner_gate(gate_from_name_))
		{
			auto from = gate_network->inner_gate_by_name(gate_from_name_);

			if (from->outputs().contains(gate_from_output_name_))
			{
				core::components::Connection connection(
					gate_from_output_name_,
					gate_network->outputs(),
					network_output_name_);

				from->add_connection(connection);

				// delete unconnected
				gate_network->unconnected_outputs().erase(
					remove(
						gate_network->unconnected_outputs().begin(),
						gate_network->unconnected_outputs().end(), network_output_name_),
						gate_network->unconnected_outputs().end());

				return;
			}
		}

		throw SyntaxException(current_line_number_);
	}
}