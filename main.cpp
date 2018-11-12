#include "src\mixGraph.h"
#include <typeinfo>

std::string path = "D:\\agh\\semestr6\\pracaInz\\program\\regular\\";

int main(int argc,char* argv[])
{
    short u= 0, v= 0;
    std::string file = "";
    double probability = -1;
    unsigned repetition = 0;
    std::string path= "";
    bool hubs = false;
    bool normal = false;
    unsigned generation = 0;
    // for(int i = 1; i < argc; i++)
    // {
    //     std::cout << typeid(argv[i]).name() << "\n";
    // }
    for(int t = 1; t < argc; t+=2)
    {
        if(static_cast<std::string>(argv[t]) == "-u")
        {
            u = std::stoi(argv[t+1]);
        }
        else if(static_cast<std::string>(argv[t]) == "-v")
        {
            v = std::stoi(argv[t+1]);
        }
        else if(static_cast<std::string>(argv[t])== "-f")
        {
            file = argv[t+1];
        }
        else if(static_cast<std::string>(argv[t]) == "-rep")
        {
            repetition = std::stoi(argv[t+1]);
        }
        else if(static_cast<std::string>(argv[t]) == "-p")
        {
            probability = std::stod(argv[t+1]);
        }
        else if(static_cast<std::string>(argv[t]) == "-path")
        {
            path = argv[t+1];
        }
        else if(static_cast<std::string>(argv[t]) == "-hubs")
        {
            hubs = true;
        }
        else if(static_cast<std::string>(argv[t]) == "-n")
        {
            normal = true;
        }
        else if(static_cast<std::string>(argv[t]) == "-g")
        {
            generation = std::stoi(argv[t+1]);
        }
    }

    if(u != 0 && v != 0 && repetition != 0 && probability != -1 && !normal)
    {
        MixGraph mtUV(u, v, probability);
        for(size_t t = 0; t < 5; t++)
        {
            mtUV.nextGenerationV2();
            mtUV.generateFileToGraphVis(path);
        }
        mtUV.exportNetworkToFile(path);
    }else if(u && v  && repetition && probability != -1 && normal && generation)
    {
        std::cout << "Program starts with "<< u << " "<< v << " "<< probability <<" "<<repetition <<" parameters\n";
        MixGraph mtUV(u, v, probability);
        for(size_t i=0; i < generation; i++)
            mtUV.nextGenerationV2();
        std::vector<std::vector<unsigned>> traffic;
        std::vector<std::vector<double>> sigma;
        std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic, sigma);
        mtUV.exportRandomWalkResultToDataFile(data, path);
        mtUV.generateDataFile<unsigned>(traffic, path, "traffic_");
        mtUV.generateDataFile<double>(sigma, path, "sigma_");
        mtUV.exportNetworkToFile(path);
        std::cout << "Successfully ended program.\n";
    }
    else if( hubs && repetition != 0 && u != 0 && v != 0 )
    {
        std::vector<std::vector<int>> table;
        table.resize(5);
        for(auto& el:table)
            el.resize(10,0);
        for(struct{double p; size_t i;} loop = {0,0}; loop.p < 1; loop.p+= 0.2, loop.i++)
        {

            for(unsigned rep = 0; rep < repetition; rep++)
            {
                MixGraph mix(u, v, loop.p);
                mix.nextGenerationV2();
                mix.nextGenerationV2();
                table[loop.i][mix.calculateHubs().size()] += 1;
            }
        }
        for(std::vector<int>& el:table)
        {
            for(int& value:el)
                std::cout << value <<" ";
            std::cout << std::endl;
        }
    }
    else if(file != "" && path != "" && repetition)
    {
        MixGraph mtUV(file);
        std::vector<std::vector<unsigned>> traffic;
        std::vector<std::vector<double>> sigma;
        std::vector<std::vector<double>> data = mtUV.calculateTimeFromEachNodToHub(repetition, traffic, sigma);
        mtUV.exportRandomWalkResultToDataFile(data, path);
        mtUV.generateDataFile<unsigned>(traffic, path, "traffic_");
    }

}
