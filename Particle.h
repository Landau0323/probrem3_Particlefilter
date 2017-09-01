//
// Created by 研究用 on 2017/08/16.
//

#ifndef PROBREM3_PARTICLEFILTER_PARTICLE_H
#define PROBREM3_PARTICLEFILTER_PARTICLE_H


#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "parameter.h"
#include "Landmarks.h"

using namespace std;

class Particle {
    static int count_particle;

private:
    double x,y,theta;   //position and direction of the car
    int id;
    double probability;
    vector <double> expected_measure;   //expected value for measured values

public:
    Particle();

    void move(double, double);
    void expect_measure(vector<Landmarks>);
    void evaluate_prob(double[num_landmark]);

    void show_result();
    static void show_count();
    void show_expected_measure();

    void set_state(double,double,double);

    double getProbability();
    double getX() const;
    double getY() const;
    double getTheta() const;
    const vector<double> &getExpected_measure() const;
};


#endif //PROBREM3_PARTICLEFILTER_PARTICLE_H
