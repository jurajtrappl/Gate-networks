#include "input_parser.h"
#include "reader_context.h"

#include <stdexcept>

using namespace std;

namespace gate_networks::application
{
    void InputParser::parse_network(shared_ptr<core::components::GateNetwork> gate_network)
    {
        parser::ReaderContext reader(gate_network, is_);
        reader.read();
    }
}