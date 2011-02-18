#include <iostream>
#include <set>
#include <vector>
#include "aaron_utils.hpp"

using namespace std;

struct RandomCommunityAssignment {
	const int N,S,C;
	vector< set<int> > communities;
	vector< set<int> > nodeToCommunitiesMap; // each node must also know which communities it is in
	RandomCommunityAssignment(const int _N, const int _S, const int _C) : N(_N),S(_S),C(_C), nodeToCommunitiesMap(this->N) {
		for(int c=0; c < this->C; c++) {
			set<int> community;
			while(community.size() < this->S) {
				const int randomNode = drand48() * this->N;
				community.insert(randomNode);
				this->nodeToCommunitiesMap.at(randomNode).insert(c);
			}
			communities.push_back(community);
		}
	}
	double commsPerNodeAvg() const {
		return double(S*C)/double(N);
	}
};

void doExperiments(const int N, const int S, const int C) {
	const RandomCommunityAssignment rca(N,S,C);
	PP(rca.commsPerNodeAvg());
}

struct UsageMessage{};

int main(int argc, char **argv) {
	unless(argc==4) {
		throw UsageMessage();
	}
	const int N = atoi(argv[1]);
	const int S = atoi(argv[2]);
	const int C = atoi(argv[3]);
	PP3(N,S,C);

	doExperiments(N,S,C);
}
