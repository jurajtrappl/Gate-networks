#pragma once

#include "components/simple_gate.h"

#include <string>
#include <vector>

namespace gate_networks::parser::gate
{
	/// <summary>
	/// Definition of inputs in the simple gate definition block.
	/// </summary>
	class SimpleGateInputsDefinition {
	public:
		SimpleGateInputsDefinition(const std::vector<std::string>& tokens, int current_line_number);

		/// <summary>
		/// Adds inputs from the definition to the simple gate instance.
		/// </summary>
		/// <param name="gate">gate instance to which the inputs are added.</param>
		void assign(core::components::SimpleGate* gate);
	private:
		std::vector<std::string> inputs_;
	};

	/// <summary>
	/// Definition of outputs in the simple gate definition block.
	/// </summary>
	class SimpleGateOutputsDefinition {
	public:
		SimpleGateOutputsDefinition(const std::vector<std::string>& tokens, int current_line_number);

		/// <summary>
		/// Adds outputs from the definition to the simple gate instance.
		/// </summary>
		/// <param name="">gate instance to which the ouputs are added.</param>
		void assign(core::components::SimpleGate* gate);
	private:
		std::vector<std::string> outputs_;
	};

	/// <summary>
	/// Definition of a function in the simple gate definition block.
	/// </summary>
	class SimpleGateFunctionDefinition {
	public:
		SimpleGateFunctionDefinition(
			const std::string& line,
			int current_line_number,
			core::components::SimpleGate* gate);

		/// <summary>
		/// Adds function from the definition to the simple gate instance.
		/// </summary>
		/// <param name="gate">gate instance to which the function is added.</param>
		void assign(core::components::SimpleGate* gate);
	private:
		int current_line_number_;
		std::vector<core::logic::Tri_state> input_values_;
		std::vector<core::logic::Tri_state> output_values_;

		/// <summary>
		/// Converts string tokens to tri state values.
		/// </summary>
		/// <param name="tokens">string values to convert.</param>
		/// <param name="values">ref out tri state values.</param>
		void to_tri_state(const std::vector<std::string>& tokens, std::vector<core::logic::Tri_state>& values);

		/// <summary>
		/// Based on the inputs count, segment the definition to two sets of values. One is for inputs and the other
		/// is for outputs.
		/// </summary>
		/// <param name="f_def_as_values">function definition as tri state values to divide.</param>
		/// <param name="inputs_size">number of inputs in the gate.</param>
		void divide_to_inputs_and_outputs(const std::vector<core::logic::Tri_state>& f_def_as_values, size_t inputs_size);			
	};
}