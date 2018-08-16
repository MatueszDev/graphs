#include "mixGraph.h"

int main()
{
    MixGraph mt22("net22g4.dat");
	//mt22.printNetwork(1);
	std::vector<std::vector<double>> data = mt22.calculateTimeFromEachNodToHub(10);
	mt22.exportRandomWalkResultToDataFile(data);
	//mt22.createHistogramFile();
	// mt22.nextGenerationV2();
	// mt22.nextGenerationV2();
    // mt22.nextGenerationV2();
    // mt22.nextGenerationV2();
	// mt22.exportNetworkToFile();


}
