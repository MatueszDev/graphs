#include "src\mixGraph.h"
#include <typeinfo>

std::string path = "D:\\agh\\semestr6\\pracaInz\\13p03\\";

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
        if(static_cast<std::string>(argv[1]) == "i")
        {
            MixGraph mtUV(1, 3, 0.3);
            for(size_t t = 0; t < 5; t++)
            {
                mtUV.nextGenerationV2();
                mtUV.generateFileToGraphVis(path);
            }
            mtUV.exportNetworkToFile(path);
        }
        else if(static_cast<std::string>(argv[2]) == "p")
        {
            file = argv[1];
            MixGraph mtUV(file);
            mtUV.printHubsIndexes();
        }else{
            u = std::stoi(argv[1]);
            v = std::stoi(argv[2]);
            probability = std::stod(argv[3]);
            repetition = std::stoi(argv[4]);
            std::cout << "Program starts with "<< u << " "<< v << " "<< probability <<" "<<repetition <<" parameters\n";
            MixGraph mtUV(u, v, probability);
            for(int i=0; i < 5; i++)
                mtUV.nextGenerationV2();
            std::vector<std::vector<unsigned>> traffic;
            std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic);
            mtUV.exportRandomWalkResultToDataFile(data, path);
            mtUV.exportNetworkToFile(path);
            std::cout << "Successfully ended program.\n";
        }
    }catch(...){
        file = argv[1];
        repetition = std::stoi(argv[2]);
        MixGraph mtUV(file);
        std::vector<std::vector<unsigned>> traffic;
        std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic);
        mtUV.exportRandomWalkResultToDataFile(data, path);
        std::cout << file;
    }

    // MixGraph mm(2,2,0);
    // MixGraph ma(2,2,1);
    // mm.nextGenerationV2();
    // mm.nextGenerationV2();
    // ma.nextGenerationV2();
    // ma.nextGenerationV2();
    // mm.exportNetworkToFile();
    // ma.exportNetworkToFile();
}
