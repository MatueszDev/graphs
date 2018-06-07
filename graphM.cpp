#include "graphM"


GraphM::GraphM(short u, short v): Graph(u,v)
{
    net = {{0, 1},{1,0}};
}

void GraphM::printNetwork(int version) const
{
    if(version == 1)
    {
        for(const std::vector<unsigned>& row:net)
        {
            for(const unsigned& column:row)
            {
                std::cout << column << " ";
            }
            std::cout << "\n";
        }
    }
    /*for(const std::vector<unsigned>& row:net)
    {
        for(const unsigned& column:row)
        {
            if(column)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }*/
    if(version == 2)
    {
        size_t rows = net.size();
        for(size_t i = 0; i < rows; i++)
        {
            std::cout << i << " : ";
            for(size_t j = 0; j < rows; j++)
            {
                if(net[i][j])
                    std::cout << j << " ";

            }
            std::cout << "\n";
        }
    }
}

void GraphM::nextGeneration()
{
    size_t rows = net.size();
    //size_t columns = net[0].size();

    ++generation;
    unsigned nodes = calcualteNumberOfNodes(generation);

    net.resize(nodes);

    for(std::vector<unsigned>& row:net)
    {
        row.resize(nodes);
    }

    unsigned shift = rows;


    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < i; j++)
        {
            if(net[i][j])
            {

                net[shift][i] = 1;

                for(short node = 0; node < v - 2; node++)
                {
                    net[shift + 1][shift] = 1;
                    ++shift;
                }

                net[shift][j] = 1;
                ++shift;

                if(u > 1)
                {
                    net[i][j] = 0;
                    net[shift][i] = 1;

                    for(short node = 0; node < u - 2; node++)
                    {
                        net[shift + 1][shift] = 1;
                        ++shift;
                    }
                    net[shift][j] = 1;
                    ++shift;
                }
            }
        }

    }
}

void GraphM::makeSymmetry()
{
  size_t rows = net.size();

  for(size_t i = 0; i < rows; i++)
      for(size_t j = 0; j < i; j++)
          net[j][i] = net[i][j];
}

unsigned GraphM::sumAllEdges() const
{
    unsigned sum = 0;
    for(auto& row:net)
      for(auto& column:row)
          sum += column;
    return sum;
}

void GraphM::createHistogramFile() const
{
    std::vector<unsigned> values;
    unsigned max = 0;
    unsigned sum;

    for(auto& row:net)
    {
        for(auto& col:row)
            sum += col;
        if(sum > max)
            max = sum;
        values.push_back(sum);
        sum=0;
    }

    unsigned* counterTable = new unsigned[max + 1]{0};
    for(auto& el:values)
    {
        counterTable[el]++;
    }

    std::stringstream ss ;
    ss << "datFiles/graphM" <<  u << v << "g"<<generation << ".dat";
    std::string fileName = ss.str();

    std::ofstream file;
    file.open(fileName);
    file << generation << "\n";
    file << calculateTeoreticalExponent() << "\n";
    for(size_t t = 0; t < max + 1; t++)
    {
        file << t <<" "<< counterTable[t] << "\n";
    }
    file.close();

    delete [] counterTable;
}
