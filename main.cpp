#include "mixGraph.h"

int main()
{
    MixGraph mt22("net22g5.dat");
    //MixGraph mt22(2,2);
	//mt22.printNetwork(1);
	std::vector<std::vector<double>> data = mt22.calculateTimeFromEachNodToHub(50);
	mt22.exportRandomWalkResultToDataFile(data);
	//mt22.createHistogramFile();
	// for(int i=0; i < 5;i++)
    //     mt22.nextGenerationV2();
	// mt22.exportNetworkToFile();


}
