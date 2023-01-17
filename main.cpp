#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

struct points{
    int i;
    double x, y, angle;
};

double vectorCalc(points p0, points p1){
    return p1.y*p0.x-p0.y*p1.x;
}

double calc(points p1, points p0){
    return sqrt(pow(p1.x-p0.x,2)+pow(p1.y-p0.y,2));
}

bool compare(points p0, points p1){
    return p0.angle > p1.angle;
}

double orientation(points p1, points p2, points p3){
    return (p3.y - p2.y)*(p2.x - p1.x) - (p2.y - p1.y)*(p3.x - p2.x);
}

int main()
{
    clock_t mainStart, mainEnd, sortStart, sortEnd, assignStart, assignEnd;

    mainStart = clock();

    points *collection;
    int collectionSize;

    //OPEN FILE-------------------------------------

    fstream cordsFile;
    cordsFile.open("points0.txt", ios::in);

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

    //FIND STARTING POINT-------------------------------------

    points *collectionCopy = new points[collectionSize];

    double temp = 1;
    int startIndex;
    for(int i = 0; i < collectionSize; i++){
        collectionCopy[i] = collection[i];
        collectionCopy[i].i = i; //DO WRZUCENIA NA SORTOWANIE
        if(collectionCopy[i].y < temp){
            temp = collectionCopy[i].y;
            startIndex = i;
        }else if(collectionCopy[i].y == temp){
            if(collectionCopy[i].x < collectionCopy[startIndex].x){
                temp = collectionCopy[i].y;
                startIndex = i;
            }
        }
    }

    swap(collectionCopy[0], collectionCopy[startIndex]);

    //SORT-----------------------------------------------------------

    sortStart = clock();

    vector<points> hull;

//    for(int i = 1; i < collectionSize; i++){
//        collectionCopy[i].angle =
//    }
//
//    sort(collectionCopy + 1, collectionCopy + collectionSize, compare);
//
    swap(collectionCopy[1], collectionCopy[7]);
    swap(collectionCopy[2], collectionCopy[5]);
    swap(collectionCopy[3], collectionCopy[4]);
    swap(collectionCopy[4], collectionCopy[6]);
    swap(collectionCopy[5], collectionCopy[6]);
    swap(collectionCopy[6], collectionCopy[7]);

    sortEnd = clock();

    //ASSIGN TO HULL----------------------------------------------------

    assignStart = clock();

    hull.push_back(collectionCopy[0]);
    hull.push_back(collectionCopy[1]);

    for(int i = 2; i < collectionSize; i++){
        if(orientation(hull[i-2], hull[-1], collectionCopy[i]) > 0){
            hull.pop_back();
        }
        hull.push_back(collectionCopy[i]);
    }

    assignEnd = clock();

    delete[] collection;
    delete[] collectionCopy;

    mainEnd = clock();

    cout << "Liczba punktow bioraca udzial w powloce: " << hull.size() << endl;
    cout << "Indeksy budujace powloke: " << endl;

    for(points i : hull){
        cout << "index: " << i.i << " x: " << i.x << " y: " << i.y << endl;
    }
    cout << endl;

    double time1 = ((double)(mainEnd-mainStart)) / CLOCKS_PER_SEC;
    double time2 = ((double)(sortEnd-sortStart)) / CLOCKS_PER_SEC;
    double time3 = ((double)(assignEnd-assignStart)) / CLOCKS_PER_SEC;

    cout << "Czas sortowania: " << time2 << "s" <<  endl;
    cout << "Czas przypisania: " << time3 << "s" <<  endl;
    cout << "Czas calego programu: " << time1 << "s" <<  endl;

    return 0;
}
