#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

struct points{
    double x, y, angle;
};

bool compare(points a, points b){
    if(a.angle < b.angle)
        return 1;
    else
        return 0;
}

int main()
{
    points *collection;
    int collectionSize;

    //OPEN FILE

    fstream cordsFile;
    cordsFile.open("points1.txt", ios::in);

    if(cordsFile.is_open()){
        string temp, line;
        getline(cordsFile, temp);
        int numOfLines = stoi(temp);
        collectionSize = numOfLines;

        collection = new points[numOfLines];
        double *allCords = new double[numOfLines*2];
        int i = 0;


        while(getline(cordsFile, line)){
            stringstream s(line);
            string cordString;
            while(s >> cordString){
                allCords[i++] = stod(cordString);
            }
            int inner = 0;
            for(int j = 0; j < numOfLines; j++){
                collection[j].x = allCords[inner++];
                collection[j].y = allCords[inner++];
            }
        }
        cordsFile.close();
        delete[] allCords;
    }

    //FIND STARTING POINT


    /*
    double temp = 1;
    points* startingPoint;

    for(int i = 0; i < collectionSize; i++){
        if(collection[i].y < temp){
            temp = collection[i].y;
            startingPoint = &collection[i];
        }else if(collection[i].y == temp){
            if(collection[i].x < startingPoint->x){
                temp = collection[i].y;
                startingPoint = &collection[i];
            }
        }
    }
    */

    //SORT

    points sortingRef = {1, 0};
    points *collectionCopy = new points[collectionSize];
    vector<points> hull;


    for(int i = 0; i < collectionSize; i++){
        collectionCopy[i] = collection[i];
        collectionCopy[i].angle = sortingRef.y * collection[i].x - collection[i].y - sortingRef.x;
    }

    sort(collectionCopy, collectionCopy+collectionSize, compare);

    /*
    for(int i = 0; i < collectionSize; i++){
        cout << "x: " << collectionCopy[i].x << " y: " << collectionCopy[i].y << " angle: " << collectionCopy[i].angle << endl;
    }
    */

    //ASSIGN TO HULL

    hull.push_back(collectionCopy[collectionSize-1]);
    hull.push_back(collectionCopy[0]);

    for(int i = 1; i < collectionSize - 1; i++){
        int hs = hull.size();
        double head = hull[hs - 1].y * collectionCopy[i].y - collectionCopy[i].x * hull[hs - 1].x;
        double tail = hull[hs - 2].y * hull[hs - 1].y - hull[hs - 1].x * hull[hs - 2].x;
        //cout << result << endl;

    }

    delete[] collection;
    delete[] collectionCopy;

    return 0;
}
