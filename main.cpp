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

struct points {
    int i;
    double x, y, angle;
};

int ori(const void *pp1, const void *pp2) {
    points* p1 = (points*)pp1;
    points* p2 = (points*)pp2;
    double temp = p2->x * p1->y - p1->x * p2->y;
    if (temp > 0) 
        return 1;
    else if (temp < 0) 
        return -1;
    return 0;
}


double orientation(points p1, points p2, points p3) {
    points v1;
    v1.x = p2.x - p1.x;
    v1.y = p2.y - p1.y;
    points v2;
    v2.x = p3.x - p2.x;
    v2.y = p3.y - p2.y;
    return v2.x * v1.y - v1.x * v2.y;
}


int main()
{
    clock_t mainStart, mainEnd, sortStart, sortEnd, assignStart, assignEnd;

    mainStart = clock();

    points* collection;
    double collectionSize;

    //OPEN FILE-------------------------------------

    fstream cordsFile;
    cordsFile.open("points5.txt", ios::in);

    if (cordsFile.is_open()) {
        string temp, line;
        getline(cordsFile, temp);
        int numOfLines = stoi(temp);
        collectionSize = numOfLines;

        collection = new points[numOfLines];
        double* allCords = new double[numOfLines * 2];
        int i = 0;


        while (getline(cordsFile, line)) {
            stringstream s(line);
            string cordString;
            while (s >> cordString) {
                allCords[i++] = stod(cordString);
            }
            int inner = 0;
            for (int j = 0; j < numOfLines; j++) {
                collection[j].x = allCords[inner++];
                collection[j].y = allCords[inner++];
            }
        }
        cordsFile.close();
        delete[] allCords;
    }
    else {
        cout << "UNABLE TO OPEN FILE" << endl;
        return 0;
    }

    //FIND STARTING POINT-------------------------------------

    points* collectionCopy = new points[collectionSize];

    int startIndex = 0;
    double temp = collection[startIndex].y;
    for (int i = 0; i < collectionSize; i++) {
        collectionCopy[i] = collection[i];
        collectionCopy[i].i = i; //DO WRZUCENIA NA SORTOWANIE
        if (collectionCopy[i].y < temp) {
            temp = collectionCopy[i].y;
            startIndex = i;
        }
        else if (collectionCopy[i].y == temp) {
            if (collectionCopy[i].x < collectionCopy[startIndex].x) {
                temp = collectionCopy[i].y;
                startIndex = i;
            }
        }
    }

    swap(collectionCopy[0], collectionCopy[startIndex]);

    //SORT-----------------------------------------------------------

    sortStart = clock();

    vector<points> hull;

    qsort(collectionCopy + 1, collectionSize - 1, sizeof(points), ori);

    sortEnd = clock();

    //ASSIGN TO HULL----------------------------------------------------

    assignStart = clock();

    hull.push_back(collectionCopy[0]);
    hull.push_back(collectionCopy[1]);
    

    for (int i = 2; i < collectionSize; i++) {                
        while(orientation(hull[hull.size() - 2], hull[hull.size() - 1], collectionCopy[i]) > 0) {
            hull.pop_back();
        }
        hull.push_back(collectionCopy[i]);
    }

    assignEnd = clock();

    delete[] collection;
    delete[] collectionCopy;

    //OUTPUT INFO-------------------------------------------------------

    mainEnd = clock();

    cout << "Liczba punktow bioraca udzial w powloce: " << hull.size() << endl;
    cout << "Indeksy budujace powloke: " << endl;

    for (points i : hull) {
        cout << "index: " << i.i << " x: " << i.x << " y: " << i.y << endl;
    }
    cout << endl;

    double time1 = ((double)(mainEnd - mainStart)) / CLOCKS_PER_SEC;
    double time2 = ((double)(sortEnd - sortStart)) / CLOCKS_PER_SEC;
    double time3 = ((double)(assignEnd - assignStart)) / CLOCKS_PER_SEC;

    cout << "Czas sortowania: " << time2 << "s" << endl;
    cout << "Czas przypisania: " << time3 << "s" << endl;
    cout << "Czas calego programu: " << time1 << "s" << endl;

    return 0;
}
