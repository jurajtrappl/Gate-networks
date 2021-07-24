#include "pch.h"
#include "CppUnitTest.h"
#include "command.h"
#include "command.cpp"
#include "gate_network_evaluator.h"
#include "gate_network_evaluator.cpp"
#include "input_parser.h"
#include "input_parser.cpp"
#include "input_file_exceptions.h"

#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gate_networks::application;
using namespace gate_networks::core::components;
using namespace std;

namespace GateNetworksApplicationTests
{
	TEST_CLASS(IncorrectInputTests)
	{
	public:
		TEST_METHOD(Binding_rule_inner_input_to_output)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingInnerInputToOutput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Binding_rule_input_to_input)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingInputToInput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Binding_rule__network_input_to_network_input)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingNetworkInputToNetworkInput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Binding_rule__network_output_to_network_output)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingNetworkOutputToNetworkOutput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Binding_rule__output_to_output)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingOutputToOutput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Binding_rule__unconnected_output)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "bindingUnconnectedOutput.in"); };
			Assert::ExpectException<gate_networks::parser::BindingRuleException>(func);
		}

		TEST_METHOD(Duplicate__connection)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "duplicateConnection.in"); };
			Assert::ExpectException<gate_networks::parser::DuplicateException>(func);
		}

		TEST_METHOD(Duplicate__function)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "duplicateFunctions.in"); };
			Assert::ExpectException<gate_networks::parser::DuplicateException>(func);
		}

		TEST_METHOD(Duplicate__gate_input)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "duplicateGateInput.in"); };
			Assert::ExpectException<gate_networks::parser::DuplicateException>(func);
		}

		TEST_METHOD(Duplicate__gate_output)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "duplicateGateOutput.in"); };
			Assert::ExpectException<gate_networks::parser::DuplicateException>(func);
		}

		TEST_METHOD(Duplicate__gate_type)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "duplicateGateType.in"); };
			Assert::ExpectException<gate_networks::parser::DuplicateException>(func);
		}

		TEST_METHOD(Missing__gate)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingGate.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__gate_definition)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingGateDefinition.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__gate_inputs)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingGateInputs.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__gate_outputs)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingGateOutputs.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__network)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingNetwork.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__network_inputs)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingNetworkInputs.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Missing__network_outputs)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "missingNetworkOutputs.in"); };
			Assert::ExpectException<gate_networks::parser::MissingKeywordException>(func);
		}

		TEST_METHOD(Syntax_gate_name)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "syntaxGateName.in"); };
			Assert::ExpectException<gate_networks::parser::SyntaxException>(func);
		}

		TEST_METHOD(Syntax_Nonexisting_input)
		{
			auto func = [this]() { this->parse_network(make_shared<GateNetwork>(), base_path + "syntaxNonexistingInput.in"); };
			Assert::ExpectException<gate_networks::parser::SyntaxException>(func);
		}
	private:
		const std::string base_path = "../../tests/data/";

		void parse_network(std::shared_ptr<gate_networks::core::components::GateNetwork> gate_network, const string& file_path)
		{
			ifstream input_file;
			input_file.open(file_path, ios::in);
			if (!input_file.good())
			{
				throw std::runtime_error("No such file!");
			}

			auto input_parser = new InputParser(input_file);
			input_parser->parse_network(gate_network);
		}
	};
}
