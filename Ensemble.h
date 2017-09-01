//
// Created by 研究用 on 2017/08/16.
//

#ifndef PROBREM3_PARTICLEFILTER_ENSEMBLE_H
#define PROBREM3_PARTICLEFILTER_ENSEMBLE_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Particle.h"
#include "Landmarks.h"
#include "parameter.h"

using namespace std;

class Ensemble {
private:
    vector<Particle> ensemble;
    Particle ground_truth;

public:
    Ensemble(int);
    void set_ground_truth(double,double,double);

    void movement(double,double);

    void measurement(double phi[num_landmark], vector<Landmarks>);
    void expect_measurement(vector<Landmarks>);
    void evaluate_weight(double phi[num_landmark]);
    void resampling();

    void show_result();
    void show_ground_truth();
    void show_summary();
    void write_result();
    void write_ground_truth();
};


#endif //PROBREM3_PARTICLEFILTER_ENSEMBLE_H
