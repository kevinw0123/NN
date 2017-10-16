#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

class Layer {
public:
	Layer(){
		bias = 0.0;
	}
	class Neuron {
	public:
		struct Connection {
			Neuron* prevNeuron;
			double weight;
			double deltaWeight;	
		};
		Neuron(int index, Layer* prevLayer)
		{
			// initialize connections to the previous layer
            mIndex = index;
            mPrevLayer = prevLayer;
            // cout << "made a neuron" << endl;
		}
		
		void drawConnection(int toConnect) {
			// cout << "Connected " << mIndex << " to " << toConnect << endl;
			Connection *c = new Connection();
			c->prevNeuron = mPrevLayer->get(toConnect);
			c->weight = rand()/double(RAND_MAX);
			connections.push_back(c);
		}

		double sigmoid(double x) { 
			return 1.0/(1.0+exp(-x)); 
		}

		double sigmoidDerivative(double x) { 
			return sigmoid(x) * (1.0-sigmoid(x)); 
		}

		void setOutputVals(double x) {
			outputVal = x;
		}

		void updateOutputVals() {
			//apply activation function to the neuron for all connections
			double sum = 0.0;

			for(int i=0; i<connections.size(); i++) {
				sum += connections[i]->weight * connections[i]->prevNeuron->getOutputVal();
			}
			
			outputVal = sigmoid(sum);
		}

		double getOutputVal() {
			return outputVal;
		}

		void freeConnections() {
			for (int i=0; i<connections.size(); i++) {
				
			}
		}
	private:
	    Layer* mPrevLayer;
        int mIndex;
		double outputVal;
		vector<Connection*> connections;
	};

	void add(Neuron* n) { layerNeurons.push_back(n); }
	Neuron* get(int i) { return layerNeurons[i]; }
	unsigned int size() { return layerNeurons.size(); }
	void setBias(double x) { bias = x; }
	double getBias() { return bias;}
private:
	double bias;
	vector<Neuron*> layerNeurons;
};

#endif