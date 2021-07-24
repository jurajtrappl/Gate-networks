#pragma once

#include "network_definitions.h"

#include <memory>

namespace gate_networks::parser::network
{
	/// <summary>
	/// Base class for connections defined in gate network definition.
	/// </summary>
	class AConnectionType
	{
	public:
		virtual ~AConnectionType()
		{
		}

		/// <summary>
		/// Fills specific information from the connection definition.
		/// </summary>
		/// <param name="tokens">pre-processed connection definition.</param>
		/// <param name="current_line_number">current line number in the reading file.</param>
		virtual void configure(const ArrowTokens& tokens, int current_line_number) = 0;

		/// <summary>
		/// Connects inputs/outputs/gates in the gate network defined by this connection.
		/// </summary>
		/// <param name="gate_network">currently processed gate network.</param>
		virtual void connect(std::shared_ptr<core::components::GateNetwork> gate_network) = 0;
	protected:
		AConnectionType() : current_line_number_()
		{
		}

		int current_line_number_;
	};
}