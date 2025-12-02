#ifndef ARRAYM_H
#define ARRAYM_H

#include <iostream>
using namespace std;


class Arraymethod{
private:
    string* arr;
    int lenth;

public:

    Arraymethod(){
        lenth = 0;
        arr = new string[0];
    }


    Arraymethod(int len){
        lenth = len;
        arr = new string[len];

    }

    ~Arraymethod(){
        delete[] arr;
    }

    string getbyindex(int idx){
        return arr[idx];
    }

    void delbyindex(int idx){
        string* newarr = new string[lenth-1];
        int i = 0;
        int j = 0;

        while (i < idx){
            newarr[i] = arr[i];
            i++;
            j++;
        }
        j++;

        for (j ; j < lenth ; j++){
            newarr[i] = arr[j];
            i++;
        }

        delete[] arr;
        lenth--;
        arr = newarr;

    }

    void append(string val){
        string* newarr = new string[lenth+1];
        for (int i = 0 ; i < lenth ; i++){
            newarr[i] = arr[i];
        }

        newarr[lenth] = val;
        lenth++;

        delete[] arr;
        arr = newarr;       

    }

    void addbyindex(int idx, string val){
        string* newarr = new string[lenth+1];
        int i = 0;
        for (i ; i < idx ; i++){
            newarr[i] = arr[i];
        }

        if (idx == lenth - 1){
            newarr[i] = val;
            newarr[i+1] = arr[i];

            lenth++;

            delete[] arr;
            arr = newarr;
            return;

        }

        newarr[i] = val;
        for (i ; i < lenth ; i++){
            newarr[i+1] = arr[i];
        }
        lenth++;

        delete[] arr;
        arr = newarr;
    }

    void display(){
        for (int i = 0 ; i < lenth ; i++){
            cout << "index " << i << " : " << arr[i] << endl;
        }
        cout << endl;
    }

};




#endif 