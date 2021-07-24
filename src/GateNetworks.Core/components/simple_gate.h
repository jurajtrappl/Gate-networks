#pragma once

#include "io_instances.h"
#include "functions.h"

namespace gate_networks::core::components
{
	/// <summary>
	/// Represents a gate with inputs, outputs and functions.
	/// Can produce a result based on the inputs and defined functions.
	/// (example "AND" gate)
	/// </summary>
	class SimpleGate final : public AConnectible
	{
	public:
		SimpleGate(const SimpleGate&);

		SimpleGate(const std::string& name)
			: AConnectible()
			, name_(name)
			, functions_()
			, inputs_()
			, outputs_()
			, changed_in_previous_()
		{
		}

		~SimpleGate()
		{
		}

		/// <returns>gate functions.</returns>
		Functions& functions();

		/// <returns>input instances.</returns>
		IOInstances& inputs();

		/// <returns>output instances.</returns>
		IOInstances& outputs();

		/// <returns>type name of the gate.</returns>
		const std::string& name();

		/// <returns>indicator if any of the states were changed in the previous iteration.</returns>
		bool changed_in_previous() const;

		/// <summary>
		/// Inserts a new function definition.
		/// </summary>
		/// <param name="">function to be inserted.</param>
		void add_function(const std::string&);

		/// <summary>
		/// Compute algorithm for the simple gate.
		/// </summary>
		void compute();

		// AConnectible implementation
		void send();

		// AConnectible implementation
		void change_state(const std::string&, logic::Tri_state);

		/// <summary>
		/// Creates a copy of this instance.
		/// </summary>
		/// <returns>shallow copy of this gate.</returns>
		std::unique_ptr<SimpleGate> clone();
	private:
		/// <summary>
		/// Name of the gate.
		/// </summary>
		std::string name_;

		/// <summary>
		/// Gate inputs.
		/// </summary>
		IOInstances inputs_;

		/// <summary>
		/// Gate outputs.
		/// </summary>
		IOInstances outputs_;

		/// <summary>
		/// Gate functions.
		/// </summary>
		Functions functions_;

		/// <summary>
		/// Indicates if any state has been changed in the previous tact.
		/// </summary>
		bool changed_in_previous_;
	};
}