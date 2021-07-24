#include "input_file_exceptions.h"
#include "reader_context.h"
#include "string_extensions.h"
#include "context_definitions.h"

using namespace std;
using namespace gate_networks::util;

namespace gate_networks::parser
{
	void ReaderContext::read()
	{
		while (getline(is_, line_))
		{
			current_line_number_++;

			if (StringExtensions::can_be_ignored(line_))
			{
				continue;
			}

			tokenize();

			if (StringExtensions::is_gate_definition(line_))
			{
				auto gate_prototype_def = 
					new GatePrototypeDefinition(
						tokens_,
						current_line_number_,
						prototypes_);
				gate_prototype_def->assign(is_);
				continue;
			}

			// inputs without network
			if (StringExtensions::is_inputs_definition(line_))
			{
				throw MissingKeywordException(current_line_number_);
			}

			if (StringExtensions::is_network_definition(line_) && enough_gate_prototypes())
			{
				auto gate_network_def =
					new GateNetworkDefinition(
						current_line_number_,
						prototypes_);
				gate_network_def->assign(is_, gate_network_);

				increment_networks_count();
				continue;
			}

			// missing gate keyword
			if (tokens_.size() == 0)
			{
				throw MissingKeywordException(current_line_number_);
			}
		}

		if (!enough_networks_parsed())
		{
			throw SyntaxException(current_line_number_);
		}
	}

	int ReaderContext::enough_gate_prototypes() const
	{ 
		return prototypes_->count() >= 1;
	}

	bool ReaderContext::enough_networks_parsed() const
	{
		return networks_count_ == 1;
	}

	void ReaderContext::increment_networks_count()
	{ 
		networks_count_++;
	}
}