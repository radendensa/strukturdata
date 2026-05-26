#include <iostream>
#include "RouteGraph.h"

RouteGraph::RouteGraph() {
    firstCity = nullptr;
    totalCities = 0;
}

RouteGraph::~RouteGraph() {
    CityNode* currentCity = firstCity;

    while (currentCity != nullptr) {
        EdgeNode* currentEdge = currentCity->firstEdge;
        while (currentEdge != nullptr) {
            EdgeNode* edgeToDelete = currentEdge;
            currentEdge = currentEdge->next;
            delete edgeToDelete;
        }

        CityNode* cityToDelete = currentCity;
        currentCity = currentCity->next;
        delete cityToDelete;
    }
}

CityNode* RouteGraph::findCityNode(const std::string& cityName) const {
    CityNode* current = firstCity;

    while (current != nullptr) {
        if (current->cityName == cityName) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

void RouteGraph::addCity(const std::string& cityName) {
    if (findCityNode(cityName) != nullptr) {
        return;
    }

    CityNode* newCity = new CityNode;
    newCity->cityName = cityName;
    newCity->firstEdge = nullptr;
    newCity->next = firstCity;
    firstCity = newCity;
    totalCities++;
}

void RouteGraph::addRoute(const std::string& fromCity, const std::string& toCity, int distance) {
    addCity(fromCity);
    addCity(toCity);

    CityNode* fromNode = findCityNode(fromCity);
    EdgeNode* newEdge = new EdgeNode;
    newEdge->destinationCity = toCity;
    newEdge->distance = distance;
    newEdge->next = nullptr;

    if (fromNode->firstEdge == nullptr) {
        fromNode->firstEdge = newEdge;
        return;
    }

    EdgeNode* current = fromNode->firstEdge;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newEdge;
}

bool RouteGraph::hasCity(const std::string& cityName) const {
    return findCityNode(cityName) != nullptr;
}

bool RouteGraph::isVisited(const std::string& cityName, std::string visitedCities[], int visitedCount) const {
    for (int i = 0; i < visitedCount; i++) {
        if (visitedCities[i] == cityName) {
            return true;
        }
    }

    return false;
}

bool RouteGraph::canReachDestination(const std::string& currentCity,
                                     const std::string& destinationCity,
                                     std::string visitedCities[],
                                     int& visitedCount) const {
    if (currentCity == destinationCity) {
        return true;
    }

    if (isVisited(currentCity, visitedCities, visitedCount)) {
        return false;
    }

    visitedCities[visitedCount] = currentCity;
    visitedCount++;

    CityNode* cityNode = findCityNode(currentCity);
    if (cityNode == nullptr) {
        return false;
    }

    EdgeNode* edge = cityNode->firstEdge;
    while (edge != nullptr) {
        if (canReachDestination(edge->destinationCity, destinationCity, visitedCities, visitedCount)) {
            return true;
        }
        edge = edge->next;
    }

    return false;
}

bool RouteGraph::findNextCity(const std::string& currentCity,
                              const std::string& destinationCity,
                              std::string& nextCity,
                              int& distance) const {
    CityNode* cityNode = findCityNode(currentCity);
    if (cityNode == nullptr) {
        return false;
    }

    EdgeNode* edge = cityNode->firstEdge;
    while (edge != nullptr) {
        if (edge->destinationCity == destinationCity) {
            nextCity = edge->destinationCity;
            distance = edge->distance;
            return true;
        }
        edge = edge->next;
    }

    edge = cityNode->firstEdge;
    while (edge != nullptr) {
        std::string* visitedCities = new std::string[totalCities];
        int visitedCount = 0;

        bool routeFound = canReachDestination(edge->destinationCity,
                                              destinationCity,
                                              visitedCities,
                                              visitedCount);
        delete[] visitedCities;

        if (routeFound) {
            nextCity = edge->destinationCity;
            distance = edge->distance;
            return true;
        }

        edge = edge->next;
    }

    return false;
}

void RouteGraph::displayGraph() const {
    CityNode* currentCity = firstCity;

    while (currentCity != nullptr) {
        std::cout << currentCity->cityName << " -> ";

        EdgeNode* currentEdge = currentCity->firstEdge;
        if (currentEdge == nullptr) {
            std::cout << "(tidak ada rute keluar)";
        }

        while (currentEdge != nullptr) {
            std::cout << currentEdge->destinationCity << " (" << currentEdge->distance << " km)";
            if (currentEdge->next != nullptr) {
                std::cout << ", ";
            }
            currentEdge = currentEdge->next;
        }

        std::cout << "\n";
        currentCity = currentCity->next;
    }
}

int RouteGraph::getTotalCities() const {
    return totalCities;
}
