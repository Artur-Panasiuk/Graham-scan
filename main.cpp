#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

struct points{
    double x;
    double y;
};

int main()
{
    points *collection;
    int collectionSize;

    //open file

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

    points *collectionCopy = new points[collectionSize];

    for(int i = 0 ; i < collectionSize; i++){
        collectionCopy[i] = collection[i];
    }

    /*
    cout.precision(9);
    for(int i = 0; i < collectionSize; i++){
        cout << "x: " << collectionCopy[i].x << " y: " << collectionCopy[i].y << endl;
    }
    */


    //get starting point

    double temp = 1;
    points* startingPoint;

    for(int i = 0; i < collectionSize; i++){
        if(collectionCopy[i].y < temp){
            temp = collectionCopy[i].y;
            startingPoint = &collectionCopy[i];
        }else if(collectionCopy[i].y == temp){
            if(collectionCopy[i].x < startingPoint->x){
                temp = collectionCopy[i].y;
                startingPoint = &collectionCopy[i];
            }
        }
    }

    //cout << "x: " << startingPoint->x << " y: " << startingPoint->y << endl;

    delete[] collection;
    delete[] collectionCopy;

    return 0;
}
