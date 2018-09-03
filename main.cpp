#include "mixGraph.h"
#include <typeinfo>

int main(int argc,char* argv[])
{
    short u,v;
    std::string file;
    double probability;
    unsigned repetition;
    // for(int i = 1; i < argc; i++)
    // {
    //     std::cout << typeid(argv[i]).name() << "\n";
    // }
    try{
         u = std::stoi(argv[1]);
         v = std::stoi(argv[2]);
         probability = std::stod(argv[3]);
         repetition = std::stoi(argv[4]);
         MixGraph mtUV(u, v, probability);
         for(int i=0; i < 5; i++)
            mtUV.nextGenerationV2();
         std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition);
     	 mtUV.exportRandomWalkResultToDataFile(data);
         mtUV.exportNetworkToFile();
    }catch(...){
        file = argv[1];
        repetition = std::stoi(argv[2]);
        MixGraph mtUV(file);
        std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition);
        mtUV.exportRandomWalkResultToDataFile(data);
        std::cout << file;
    }

    // MixGraph mt22("net22g5iehr.dat");
    //MixGraph mt22(2,2);
	//mt22.printNetwork(1);
	// std::vector<std::vector<double>> data = mt22.calculateTimeFromEachNodToHub(200);
	// mt22.exportRandomWalkResultToDataFile(data);
	//mt22.createHistogramFile();
	// for(int i=0; i < 10;i++)
    //     mt22.nextGenerationV2();
    // mt22.createHistogramFile();
	//mt22.exportNetworkToFile();


}
