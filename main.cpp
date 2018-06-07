#include "graphM"
#include "graphL"
#include "graphMT"

int main()
{

    std::cout << "List \n\n";
    GraphL graphL(1,2);
    for(int i =0; i < 5;i++)
        graphL.nextGeneration();
    graphL.createHistogramFile();


    std::cout << "Current number of edges from list " << graphL.sumAllEdges() << "\n";

    std::cout << "\ngraphM13 \n";

    GraphM graphM13(1,3);
    graphM13.nextGeneration();

    graphM13.makeSymmetry();
    graphM13.printNetwork(2);
    std::cout << graphM13.sumAllEdges() << " " << graphM13.calcualteNumberOfEdges(graphM13.getGeneration()) << "\n";

    std::cout << "\ngraphL13 \n";
    GraphL graphL13(1,3);
    for(int i =0; i <  10;i++)
        graphL13.nextGeneration();
    graphL13.createHistogramFile();


    std::cout << "\ngraphM22 \n";

    GraphM graphM22(2,2);
    for(int i =0; i < 5;i++)
        graphM22.nextGeneration();

    graphM22.makeSymmetry();
    //graphM22.printNetwork(2);
    graphM22.createHistogramFile();
    std::cout << "Fractal dimension "<< graphM22.fractalDimension() << std::endl;

    std::cout << graphM22.sumAllEdges() << " " << graphM22.calcualteNumberOfEdges(graphM22.getGeneration()) << "\n";

    std::cout << "\ngraphL22 \n";

    GraphL graphL22(2,2);
    for(int i =0; i <  10;i++)
        graphL22.nextGeneration();
    //graphL22.nextGeneration();
    //graphL22.printNetwork();

    graphL22.createHistogramFile();

    GraphMT graphMT12(1,2);
    graphMT12.nextGeneration();
    graphMT12.nextGeneration();
    graphMT12.makeSymmetry();
    graphMT12.printNetwork(2);

}
