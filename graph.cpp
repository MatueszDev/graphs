#include "graph"

unsigned Graph::calcualteNumberOfNodes(unsigned gener) const
{
    unsigned nodes = double(u + v - 2)/(u + v - 1)*std::pow(u + v, generation) + double(u + v)/(v + u - 1);
    return nodes;
}

unsigned Graph::calcualteNumberOfEdges(unsigned gener) const
{
    unsigned edges = std::pow((u + v), generation);
    return edges;
}

double Graph::calculateTeoreticalExponent() const
{
    double exponent = 1 + std::log(u+v)/std::log(2);
    return exponent;
}

double Graph::fractalDimension() const
{
    if(u <= 1)
    {
        std::cout << "You can not compute fractal dimension" << std::endl;
        return 0;
    }

    double dimension = std::log(double(u+v))/std::log(u);
    return dimension;

}
