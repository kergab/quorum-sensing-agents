#include "Generate.hpp"

int main() {
	Params params("params.xml");
	params.put("saveParams.xml");
	Generate g;
	return g.files(params);
}
