//
// Created by 研究用 on 2017/08/16.
//

#ifndef PROBREM3_PARTICLEFILTER_LANDMARKS_H
#define PROBREM3_PARTICLEFILTER_LANDMARKS_H

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Landmarks {
private:
    double x,y;

public:
    void setposition_landmarks(double,double);
    double get_x_landmarks();
    double get_y_landmarks();

};


#endif //PROBREM3_PARTICLEFILTER_LANDMARKS_H
