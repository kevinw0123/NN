#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "network.h"

#define inputLayerSize 64
#define hiddenLayerSize 49
#define outputLayerSize 26

using namespace std;

void initInputs(vector<double> &inputLayer, vector<double> &targetLayer) {
	string s = "1011111010111001100000011000000110000001100000010100001000111100";
	for (int i=0; i<64; i++) {
		inputLayer.push_back(((int)s[i]-48));
	}
	targetLayer[3] = 1.0;
}

int main() {

	vector<int> topology;
	vector<double> inputLayer;
	vector<double> targetLayer(26, 0.0);

	initInputs(inputLayer, targetLayer);

	topology.push_back(inputLayerSize);
	topology.push_back(hiddenLayerSize);
	topology.push_back(outputLayerSize);
	
	Network network(topology);

	network.forwardPropagate(inputLayer);
	network.backPropagate(targetLayer);

	network.close();
	return 0;
}