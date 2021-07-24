#include "components/gate_network.h"
#include "reader_base.h"
#include "reader_context.h"
#include "input_file_exceptions.h"
#include "command_exceptions.h"
#include "evaluation/command_visitor.h"
#include "container_extensions.h"
#include "string_extensions.h"
#include "command.h"
#include "gate_network_evaluator.h"
#include "input_parser.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;
using namespace gate_networks::core;
using namespace gate_networks::parser;
using namespace gate_networks::util;

void evaluate_commands(shared_ptr<components::GateNetwork> gate_network)
{
    gate_networks::application::GateNetworkEvaluator evaluator(gate_network);
    string line;
    while (getline(cin, line))
    {
        if (StringExtensions::is_end(line))
        {
            exit(0);
        }

        try
        {
            if (StringExtensions::can_be_ignored(line))
            {
                throw gate_networks::core::CommandException("Syntax error.");
            }

            gate_networks::application::Command command(line, gate_network->inputs().size());
            evaluator.evaluate_for_command(command);
            auto result = evaluator.result();

            // print tact count and stringified outputs
            cout << result.first
                 << " "
                 << result.second
                 << endl;
        }
        catch (gate_networks::core::CommandException& ce)
        {
            cout << ce.what() << endl;
        }
    }
}

void run(const vector<string> args)
{
    if (args.size() != 2)
    {
        cout << "Argument error." << endl;
        exit(0);
    }

    auto gate_network = make_shared<components::GateNetwork>();
    
    try {
        ifstream input_file;
        input_file.open(args[1], ios::in);
        if (!input_file.good())
        {
            cout << "File error." << endl;
            exit(0);
        }

        // load
        auto input_parser = new gate_networks::application::InputParser(input_file);
        
        // parse
        input_parser->parse_network(gate_network);

        // execute
        evaluate_commands(gate_network);
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    run(args);
}