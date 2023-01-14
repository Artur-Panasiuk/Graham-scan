#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct points{
    double x;
    double y;
};

int main()
{
    points *collection;
    int collectionSize;

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

    cout.precision(9);
    for(int i = 0; i < collectionSize; i++){
        cout << "x: " << collection[i].x << " y: " << collection[i].y << endl;
    }

    delete[] collection;

    return 0;
}
