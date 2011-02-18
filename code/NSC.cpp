#include <iostream>
#include "aaron_utils.hpp"

using namespace std;

struct UsageMessage{};

int main(int argc, char **argv) {
	unless(argc==4) {
		throw UsageMessage();
	}
	const int N = atoi(argv[1]);
	const int S = atoi(argv[2]);
	const int C = atoi(argv[3]);
	PP3(N,S,C);
}
