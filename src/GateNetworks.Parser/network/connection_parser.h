#pragma once

#include "network_definitions.h"
#include "connection_type.h"
#include "connection_definitions.h"

#include <map>

namespace gate_networks::parser::network
{
	typedef std::pair<size_t, size_t> Connection_type_key;

	/// <summary>
	/// Contains logic for parsing connections.
	/// </summary>
	class ConnectionParser
	{
	public:
		ConnectionParser(int current_line_number)
			: current_line_number_(current_line_number)
			, strategy_()
			, types_()
		{
			types_.emplace(Connection_type_key(2, 2), new InnerToInnerConnection());
			types_.emplace(Connection_type_key(2, 1), new InputToInnerConnection());
			types_.emplace(Connection_type_key(1, 2), new InnerToOutputConnection());
		}

		~ConnectionParser()
		{
			for (auto&& t : types_)
			{
				delete t.second;
			}
		}

		/// <summary>
		/// Chooses connection type based on the connection definition.
		/// </summary>
		/// <param name="key">left and right side of connection sizes.</param>
		void set_strategy(Connection_type_key key);

		/// <summary>
		/// Adds the content of connection definition.
		/// </summary>
		/// <param name="tokens">left and right side of connection definition content.</param>
		void configure_strategy(const ArrowTokens& tokens);

		/// <summary>
		/// Connects inputs/outputs/gates in the gate network defined by the connection.
		/// </summary>
		/// <param name="gate_network">currently processed gate network.</param>
		void process(std::shared_ptr<core::components::GateNetwork> gate_network);
	private:
		int current_line_number_;
		std::map<Connection_type_key, AConnectionType*> types_;
		AConnectionType* strategy_;
	};
}