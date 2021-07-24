#include "input_file_exceptions.h"

using namespace std;

namespace gate_networks::parser {
	string InputFileException::format_error_message(int current_line_number, const std::string& error_type)
	{
		return "Line " + std::to_string(current_line_number) + ": " + error_type;
	}
}