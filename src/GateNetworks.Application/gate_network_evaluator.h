#pragma once

#include "components/gate_network.h"
#include "evaluation/command_visitor.h"
#include "command.h"

#include <memory>

namespace gate_networks::application
{
	/// <summary>
	/// Calculates output of the gate network according to the specified commands.
	/// </summary>
	class GateNetworkEvaluator
	{
	public:
		GateNetworkEvaluator(std::shared_ptr<core::components::GateNetwork> gate_network)
			: gate_network_(gate_network)
			, visitor(new core::evaluation::CommandVisitor())
		{
		}

		~GateNetworkEvaluator()
		{
			delete visitor;
		}

		/// <summary>
		/// Set every input and output to undefined.
		/// </summary>
		void reset();

		/// <summary>
		/// Computes the gate network setup for the specified command.
		/// </summary>
		/// <param name="command">input values for the gate network inputs.</param>
		void evaluate_for_command(Command command);

		/// <returns>tact count for computation and stringified outputs.</returns>
		std::pair<int, std::string> result();
	private:
		std::shared_ptr<core::components::GateNetwork> gate_network_;
		core::evaluation::CommandVisitor* visitor;
	};
}