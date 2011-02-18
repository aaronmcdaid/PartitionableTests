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
	int numOrphanNodes() const {
		int numOrphans = 0;
		for(int n=0; n< this->N; n++) {
			if(this->nodeToCommunitiesMap.at(n).size()==0)
				numOrphans++;
		}
		return numOrphans;
	}
};

struct Coloring {
	const RandomCommunityAssignment * const rca;
	const int N;
	vector<int> colors;
	set<int> uncoloredCommunities;
	int componentsSoFar;
	Coloring(const RandomCommunityAssignment *_rca): rca(_rca), N(_rca->N), colors(N, -1), componentsSoFar(0) {
		for(int c=0; c<this->rca->C; c++)
			uncoloredCommunities.insert(c);
		assert(uncoloredCommunities.size() == this->rca->C);
	}
	void colorOneComm(const int commID, const int color) {
		const bool wasErased = uncoloredCommunities.erase(commID);
		assert(wasErased);
		const set<int> members = this->rca->communities.at(commID);
		forEach(const int n, amd::mk_range(members)) {
			if(this->colors.at(n) != color) {
				assert(this->colors.at(n) == -1);
				this->colors.at(n) = color;
			}
		}
	}
	int fixMiscolorings() {
		forEach(const int maybeColored, amd::mk_range(this->uncoloredCommunities)) { // the ID of a community that might just have been percolated into
			forEach(const int n, amd::mk_range(this->rca->communities.at(maybeColored))) { // the nodes in that community
				const int color = this->colors.at(n);
				if(color == -1) { // that's OK, this node is still, as expected, uncolored
				} else {
					// AHA. We must color this community and restart
					PP3(maybeColored, n, color);
					this->colorOneComm(maybeColored, color);
					return 1+this->fixMiscolorings();
				}
			}
		}
		return 0;
	}
	int percolateAnotherComponent() {
		const int newColor = componentsSoFar;
		// 1. take next uncoloured component
		// 2. color its nodes in
		// 3. find a miscoloured community.
		//   3a. if found, colors its nodes in and repeat
    // end
		if(uncoloredCommunities.empty())
			return -1; // all done!
		const int seedComm = *uncoloredCommunities.begin();
		PP2(seedComm, newColor);

		this->colorOneComm(seedComm, newColor);
		const int newlyColored = 1+this->fixMiscolorings();
		PP(newlyColored);

		++componentsSoFar;
		return newColor;
	}
};

void doExperiments(const int N, const int S, const int C) {
	const RandomCommunityAssignment rca(N,S,C);
	PP(rca.commsPerNodeAvg());
	PP(rca.numOrphanNodes());
	cout << endl;

	Coloring col(&rca);
	while(!col.uncoloredCommunities.empty()) {
		col.percolateAnotherComponent();
	}
	PP(col.componentsSoFar);
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
