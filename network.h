#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include "layer.h"
using namespace std;

class Network {
	public:
		Network(vector<int> &topology) {
			networkLayers.push_back(new Layer());
			// cout << "Layer: " << 0 << " Nodes: " <<  topology[0] << endl;
			for (int j=0; j<topology[0]; j++) {
				networkLayers[0]->add(new Layer::Neuron(j, NULL));
			}
			//initialize neurons
			for (int i=1; i<topology.size(); i++) {
				networkLayers.push_back(new Layer());
				// cout << "Layer: " << i << " Nodes: " <<  topology[i] << endl;
				for (int j=0; j<topology[i]; j++) {
					networkLayers[i]->add(new Layer::Neuron(j, networkLayers[i-1]));
				}
			}

			//initialize connections
			//layer 0->1
			int k=0;
			for (int j=0; j<7; j++) {
				for (int i=0; i<7; i++) {
					networkLayers[1]->get(k)->drawConnection(i+8*j);
					networkLayers[1]->get(k)->drawConnection(i+8*j+1);
					networkLayers[1]->get(k)->drawConnection(i+8*j+8);
					networkLayers[1]->get(k)->drawConnection(i+8*j+9);	
					
					k++;
				}
			}

			for (int i=0; i<26; i++) {
				for (int j=0; j<49; j++) {
					networkLayers[2]->get(i)->drawConnection(j);
				}
			}
			mError = 0.0;
		}

		void forwardPropagate(vector<double> &inputVals) {
			//force input layer values to 0
			cout << "Set input layer outputVals" << endl;

			for (int i=0; i<networkLayers[0]->size(); i++) {
				networkLayers[0]->get(i)->setOutputVals(inputVals[i]);
				cout << networkLayers[0]->get(i)->getOutputVal() << " ";
			}

			//forward propagate layer 0 to layer 1
			cout << endl << "Forward propagate to layer 1" << endl;

			for (int i=0; i<networkLayers[1]->size(); i++){
				networkLayers[1]->get(i)->updateOutputVals();
				cout << networkLayers[1]->get(i)->getOutputVal() << " ";
			}

			//forward propagate layer 1 to layer 2
			cout << endl << "Forward propagate to layer 2" << endl;

			for (int i=0; i<networkLayers[2]->size(); i++){
				networkLayers[2]->get(i)->updateOutputVals();
				cout << networkLayers[2]->get(i)->getOutputVal() << " ";
			}
			cout << endl;
		}

		void backPropagate(vector<double> &targetVals) {
			cout << "Back Propagating" << endl;
			mError = 0.0;

			cout <<networkLayers[2]->size() << endl;
			for(unsigned n = 0; n < networkLayers[2]->size(); ++n)
			{
				mError += 0.5 * (targetVals[n] - networkLayers[2]->get(n)->getOutputVal()) * (targetVals[n] - networkLayers[2]->get(n)->getOutputVal());
				double delta = targetVals[n] - networkLayers[2]->get(n)->getOutputVal();
			}
			mError /= networkLayers[2]->size() - 1; // get average error squared
			mError = sqrt(mError); // RMS
			cout << mError << endl;

		}

		void close() {
			for (int i=0; i<topology.size(); i++) {
				for (int j=0; j<networkLayers[i]->layerNeurons.size(); j++) {
					
				}
			}
		}
	private:
		double mError;
		vector<Layer*> networkLayers;
};

#endif