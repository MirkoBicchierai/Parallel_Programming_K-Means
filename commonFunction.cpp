//
// Created by mirko on 18/02/24.
//
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct Point{
    double x,y;
};

using namespace std;

vector<Point> loadDataset(const string& path){

    vector<Point> data;
    ifstream file(path);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Point p{};

        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');
        getline(ss, temp, ',');

        getline(ss, temp, ',');
        double latitude = stod(temp);
        p.x = latitude;

        getline(ss, temp, ',');
        double longitude = stod(temp);
        p.y = longitude;

        data.push_back(p);
    }

    return data;
}
