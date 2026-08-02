#include <iostream>
#include "Stack.h"
#include "Graph.h"
#include "Queue.h"

void Exercise2()
{
    // Cities of Vancouver
    // Add all the cities to a vector, add the cities to the graph, then link them all where applicable
    // print all the connections
    // find path between the cities

    // store all the indices
    Vector<std::string> cities;
    cities.PushBack("Vancouver");           // 0
    cities.PushBack("Burnaby");             // 1
    cities.PushBack("North_Vancouver");     // 2
    cities.PushBack("Delta");               // 3
    cities.PushBack("Richmond");            // 4
    cities.PushBack("New_West");            // 5
    cities.PushBack("Coquitlam");           // 6
    cities.PushBack("Victoria");            // 7
    cities.PushBack("Naniamo");             // 8
    cities.PushBack("Quiznel");             // 9
    cities.PushBack("Langley");             // 10
    cities.PushBack("Abbotsford");          // 11
    cities.PushBack("Maple_Ridge");         // 12
    cities.PushBack("Port_Coquitlam");      // 13
    cities.PushBack("Surrey");              // 14

    Graph<std::string> vancouverCities;
    for (int i = 0; i < cities.Size(); ++i)
    {
        vancouverCities.AddItem(&cities[i]);
    }

    // Vancouver
    vancouverCities.AddLink(0, 1);   // Burnaby
    vancouverCities.AddLink(0, 2);   // North Vancouver
    vancouverCities.AddLink(0, 4);   // Richmond

    // Burnaby
    vancouverCities.AddLink(1, 5);   // New Westminster
    vancouverCities.AddLink(1, 6);   // Coquitlam
    vancouverCities.AddLink(1, 2);   // North Vancouver

    // North Vancouver
    vancouverCities.AddLink(2, 6);   // Coquitlam (via Second Narrows)

    // Richmond
    vancouverCities.AddLink(4, 3);   // Delta
    vancouverCities.AddLink(4, 14);  // Surrey (via bridges)

    // Delta
    vancouverCities.AddLink(3, 14);  // Surrey

    // New Westminster
    vancouverCities.AddLink(5, 14);  // Surrey
    vancouverCities.AddLink(5, 6);   // Coquitlam

    // Surrey
    vancouverCities.AddLink(14, 10); // Langley
    vancouverCities.AddLink(14, 11); // Abbotsford
    vancouverCities.AddLink(14, 13); // Port Coquitlam

    // Coquitlam
    vancouverCities.AddLink(6, 13);  // Port Coquitlam
    vancouverCities.AddLink(6, 12);  // Maple Ridge

    // Port Coquitlam
    vancouverCities.AddLink(13, 12); // Maple Ridge

    // Maple Ridge
    vancouverCities.AddLink(12, 10); // Langley

    // Langley
    vancouverCities.AddLink(10, 11); // Abbotsford

    // Ilha de Vancouver
    vancouverCities.AddLink(7, 8);   // Victoria <-> Nanaimo

    // Interior
    vancouverCities.AddLink(11, 9);  // Abbotsford -> Quesnel

    vancouverCities.PrintGraph();


    Vector<const std::string*> pathDFS;
    Vector<const std::string*> pathBFS;
    std::cout << "Path from " << cities[0] << "-" << cities[4] << " (BFS):\n";
    if (vancouverCities.GetPathDFS(0, 10,pathDFS))
    {
        for (int i = pathDFS.Size() - 1; i >= 0; --i)
        {
            std::cout << (*pathDFS[i]) << "-";

        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Path couldn't be found!\n";
    }

}

struct Tile
{
    int x = 0;
    int y = 0;
    
    bool isInPath = false;
    void Draw() const
    {
        if (isInPath)
        {
            std::cout << "[0]";
        }
        else
        {
            std::cout << "[ ]";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Tile& t)
    {
        os << t.x << "-" << t.y;
        return os;
    }
};

void ClearMap(Vector<Tile>& map)
{
    for (int i = 0; i < map.Size(); i++)
    {
        map[i].isInPath = false;
    }
}
void DrawMap(int width, int height, const Vector<Tile>& tileMap)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = x + (y * width);
            tileMap[index].Draw();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Exercise3TileMap()
{
    Vector<Tile> tileMap;
    Graph<Tile> mapGraph;

    int width = 10;
    int height = 10;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Tile tile;
            tile.x = x;
            tile.y = y;
            tileMap.PushBack(tile);
        }
    }
    for (int i = 0; i < tileMap.Size(); ++i)
    {
        mapGraph.AddItem(&tileMap[i]);
    }
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = x + (y * width);
            if (x + 1 < width)
            {
                int rightIndex = (x + 1) + (y * width);
                mapGraph.AddLink(index, rightIndex);
            }
            if (y + 1 < height)
            {
                int downIndex = x + ((y + 1) * width);
                mapGraph.AddLink(index, downIndex);
            }
        }
    }

    DrawMap(width, height, tileMap);
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;
    std::cout << "Enter Start X: ";
    std::cin >> startX;
    std::cout << "Enter Start Y: ";
    std::cin >> startY;
    std::cout << "Enter End X: ";
    std::cin >> endX;
    std::cout << "Enter End Y: ";
    std::cin >> endY;

    Vector<const Tile*> pathDFS;
    Vector<const Tile*> pathBFS;
    int startIndex = startX + (startY * width);
    int endIndex = endX + (endY * width);
    mapGraph.GetPathDFS(startIndex, endIndex, pathDFS);
    mapGraph.GetPathBFS(startIndex, endIndex, pathBFS);
    system("cls");
    for (int i = 0; i < pathDFS.Size(); i++)
    {
        int index = pathDFS[i]->x + (pathDFS[i]->y * width);
        tileMap[index].isInPath = true;
    }
    DrawMap(width, height, tileMap);
    ClearMap(tileMap);
    std::cout << "\n";
    std::cout << "BFS Path: \n";
    for (int i = 0; i < pathBFS.Size(); ++i)
    {
        int index = pathBFS[i]->x + (pathBFS[i]->y * width);
        tileMap[index].isInPath = true;
    }
    DrawMap(width, height, tileMap);
    std::cout << "\n";
}



int main()
{
    std::cout << "Graph Example!\n";

    Graph<int> myGraph;
    Vector<int> graphData;
    for (int i = 0; i < 10; ++i)
    {
        graphData.PushBack(i);
    }

    for (int i = 0; i < graphData.Size(); ++i)
    {
        myGraph.AddItem(&graphData[i]);
    }

    myGraph.AddLink(0, 1);
    myGraph.AddLink(0, 2);
    myGraph.AddLink(1, 2);
    myGraph.AddLink(2, 3);
    myGraph.AddLink(3, 4);
    myGraph.AddLink(4, 5);
    myGraph.AddLink(5, 6);
    myGraph.AddLink(6, 7);
    myGraph.AddLink(7, 8);
    myGraph.AddLink(8, 9);
    myGraph.PrintGraph();

    Vector<const int*> dfsConnections;
    Vector<const int*> bfsConnections;
    myGraph.GetAllConnectionsBFS(0, bfsConnections);
    myGraph.GetAllConnectionsDFS(0, dfsConnections);

    std::cout << "Connections (DFS):\n";
    for (int i = 0; i < dfsConnections.Size(); ++i)
    {
        std::cout << (*dfsConnections[i]) << " ";
    }
    std::cout << "\n";
    std::cout << "Connections (BFS):\n";
    for (int i = 0; i < bfsConnections.Size(); ++i)
    {
        std::cout << (*bfsConnections[i]) << " ";
    }
    std::cout << "\n\n";


    int startIndex = 0;
    int endIndex = 9;
    Vector<const int*> pathDFS;
    Vector<const int*> pathBFS;
    std::cout << "Path from " << startIndex << "-" << endIndex << " (DFS):\n";
    if (myGraph.GetPathDFS(startIndex, endIndex, pathDFS))
    {
        for (int i = pathDFS.Size() - 1; i >= 0; --i)
        {
            std::cout << (*pathDFS[i]) << "-";

        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Path couldn't be found!\n";
    }

    std::cout << "Path from " << startIndex << "-" << endIndex << " (BFS):\n";
    if (myGraph.GetPathDFS(startIndex, endIndex, pathBFS))
    {
        for (int i = pathDFS.Size() - 1; i >= 0; --i)
        {
            std::cout << (*pathDFS[i]) << "-";

        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Path couldn't be found!\n";
    }

    Exercise2();
    Exercise3TileMap();
}

        

