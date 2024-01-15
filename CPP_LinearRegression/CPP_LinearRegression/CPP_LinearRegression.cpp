#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Data structure to represent a point
struct Point {
    double x, y;
    std::string label;
};

// Function to calculate Euclidean distance between two points
double euclideanDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// K-Nearest Neighbors algorithm
std::string kNN(const std::vector<Point>& data, const Point& query, int k) {
    std::vector<std::pair<double, std::string>> distances;

    for (const Point& p : data) {
        double distance = euclideanDistance(query, p);
        distances.push_back(std::make_pair(distance, p.label));
    }

    // Sort distances in ascending order
    std::sort(distances.begin(), distances.end());

    // Count labels of k nearest neighbors
    int countA = 0, countB = 0;
    for (int i = 0; i < k; i++) {
        if (distances[i].second == "Class A") {
            countA++;
        }
        else {
            countB++;
        }
    }

    // Classify the query point based on majority vote
    return countA > countB ? "Class A" : "Class B";
}

int main() {
    // Example dataset
    std::vector<Point> data = {
        {1.0, 2.0, "Class A"},
        {2.0, 3.0, "Class A"},
        {4.0, 4.0, "Class B"},
        {5.0, 5.0, "Class B"}
    };

    Point query = { 3.0, 3.0, "" }; // Point to classify
    int k = 3; // Number of neighbors to consider

    query.label = kNN(data, query, k);
    std::cout << "Query point belongs to: " << query.label << std::endl;

    return 0;
}
