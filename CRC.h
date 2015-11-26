//
//  CRC.h
//  CRC Algorithm
//
//  Created by Ken Ishiguro on 11/18/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef CRC_h
#define CRC_h
#include <string>
#include <bitset>
#include <math.h>
using namespace std;
const int bitSize = 17; //<==This is actually 16 bit. I screwed up and too lazy to fix
//                      Change this to change table size 1=1 2=3 3=7 4=15...

string format(string input){
    for (int x = 0; x < input.size(); x++) {
        if (input[x] >= 'a' && input[x] <= 'z')
            input[x] -= 32;
        if (input[x] < 'A' || input[x] > 'Z')
            input.erase(x);
    }
    return input;
}

int getMaxSize() {
    int convertDec(string bin);
    int returnThis = 1;
    for (int x = 0; x<bitSize; x++) {
        returnThis*=10+1;
    }
    string temp = to_string(returnThis);
    return convertDec(temp);
}

char calc(char A, char B){
    if(A == B)
        return '0';
    else
        return '1';
}

int convertDec(string bin){
    int result = 0;
    int n;
    
    for (int count = (int)bin.size()-1; count >= 0; count--) {
        if (bin[bin.size()-1-count] == '1')
            n = 1;
        else
            n=0;
        result += powf((2 * n), count);
    }
    return result;
}

string convertToBin(string target){
    string tempSum("");
    for (int count = 0; count < target.size(); count++) {
        bitset<8>sum(target.c_str()[count]);
        tempSum += sum.to_string();
    }
    return tempSum;
}

int performCyclic(const string &source){
    string product = convertToBin(format(source));
    string divisor = product.substr(0, bitSize);
    
    if (divisor.c_str()[0] == '0') {
        for (int start = 0; start < divisor.size(); start++) {
            if (divisor.c_str()[start] == '0')
                divisor.replace(start, 1, "1");
            else
                divisor.replace(start, 1, "0");
        }
    }
    
    product.append(bitSize-1, '0');
    
    while (product.size() > bitSize-1) {
        product.erase(0,product.find_first_not_of("0"));
        for (int count = 0; count < divisor.size(); count++) {
            product[count] = calc(product[count], divisor[count]);
        }
    }
    
    product.erase(0,product.find_first_not_of("0"));

    return convertDec(product);
}

//int binaryToBase10(string bin)
//{
//    char n[bin.size()];
//    
//    for (int count = 0; count < bin.size(); count++) {
//        n[count] = bin[count];
//    }
//    int output = 0;
//    
//    for(int i=0; (int)n > 0; i++) {
//        if(n % 10 == 1) {
//            output += (1 << i);
//        }
//        n /= 10;
//    }
//    
//    return output;
//}



#endif /* CRC_h */
