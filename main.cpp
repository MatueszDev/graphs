#include "src\mixGraph.h"
#include <typeinfo>

std::string path = "D:\\agh\\semestr6\\pracaInz\\program\\sieci_1_5\\u1_v3p03\\";

int main(int argc,char* argv[])
{
    short u= 0, v= 0;
    std::string file= "";
    double probability= -1;
    unsigned repetition= 0;
    //std::string path= "";
    // for(int i = 1; i < argc; i++)
    // {
    //     std::cout << typeid(argv[i]).name() << "\n";
    // }
    for(size_t t = 1; t < argc; t+=2)
    {
        if(static_cast<std::string>(argv[t]) == "-u")
        {
            u = std::stoi(argv[t+1]);
        }
        if(static_cast<std::string>(argv[t]) == "-v")
        {
            v = std::stoi(argv[t+1]);
        }
        if(static_cast<std::string>(argv[t])== "-f")
        {
            file = argv[t+1];
        }
        if(static_cast<std::string>(argv[t]) == "-rep")
        {
            repetition = std::stoi(argv[t+1]);
        }
        if(static_cast<std::string>(argv[t]) == "-p")
        {
            probability = std::stod(argv[t+1]);
        }
    }
    try{
        if(u != 0 && v != 0 && repetition != 0 && probability != -1)
        {
            MixGraph mtUV(u, v, probability);
            for(size_t t = 0; t < 5; t++)
            {
                mtUV.nextGenerationV2();
                mtUV.generateFileToGraphVis(path);
            }
            mtUV.exportNetworkToFile(path);
        }// }else{
        //     std::cout << "Program starts with "<< u << " "<< v << " "<< probability <<" "<<repetition <<" parameters\n";
        //     MixGraph mtUV(u, v, probability);
        //     for(int i=0; i < 5; i++)
        //         mtUV.nextGenerationV2();
        //     std::vector<std::vector<unsigned>> traffic;
        //     std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic);
        //     mtUV.exportRandomWalkResultToDataFile(data, path);
        //     mtUV.exportNetworkToFile(path);
        //     std::cout << "Successfully ended program.\n";
        // }
    }catch(...){
        file = argv[1];
        repetition = std::stoi(argv[2]);
        MixGraph mtUV(file);
        std::vector<std::vector<unsigned>> traffic;
        std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic);
        mtUV.exportRandomWalkResultToDataFile(data, path);
        std::cout << file;
    }

}
