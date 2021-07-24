#include "reader_base.h"
#include "container_extensions.h"

using namespace std;

namespace gate_networks::parser
{
	void ReaderBase::tokenize()
	{
		tokens_.clear();
		util::ContainerExtensions<vector<string>>::split(line_, tokens_);
		tokens_.erase(tokens_.begin());
	}
}