#include "connection_parser.h"
#include "connection_definitions.h"
#include "../input_file_exceptions.h"

using namespace std;

namespace gate_networks::parser::network
{
	void ConnectionParser::configure_strategy(const ArrowTokens& tokens)
	{
		strategy_->configure(tokens, current_line_number_);
	}

	void ConnectionParser::set_strategy(Connection_type_key key)
	{
		if (types_.find(key) != types_.end())
		{
			strategy_ = types_[key];
		}
		else
		{
			throw BindingRuleException(current_line_number_);
		}
	}

	void ConnectionParser::process(std::shared_ptr<core::components::GateNetwork> gate_network)
	{
		strategy_->connect(gate_network);
	}
}