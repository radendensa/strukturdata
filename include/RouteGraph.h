#ifndef ROUTE_GRAPH_H
#define ROUTE_GRAPH_H

#include <string>

struct EdgeNode {
    std::string destinationCity;
    int distance;
    EdgeNode* next;
};

struct CityNode {
    std::string cityName;
    EdgeNode* firstEdge;
    CityNode* next;
};

class RouteGraph {
private:
    CityNode* firstCity;
    int totalCities;

    CityNode* findCityNode(const std::string& cityName) const;
    bool isVisited(const std::string& cityName, std::string visitedCities[], int visitedCount) const;
    bool canReachDestination(const std::string& currentCity,
                             const std::string& destinationCity,
                             std::string visitedCities[],
                             int& visitedCount) const;

public:
    RouteGraph();
    ~RouteGraph();

    void addCity(const std::string& cityName);
    void addRoute(const std::string& fromCity, const std::string& toCity, int distance);
    bool hasCity(const std::string& cityName) const;
    bool findNextCity(const std::string& currentCity,
                      const std::string& destinationCity,
                      std::string& nextCity,
                      int& distance) const;
    void displayGraph() const;
    int getTotalCities() const;
};

#endif
