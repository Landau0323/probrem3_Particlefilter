//
// Created by 研究用 on 2017/08/16.
//

#include "Particle.h"
#include "parameter.h"

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

double Gaussian_random(double sigma=1);

int Particle::count_particle=0;

//getter and setter
double Particle::getProbability(){
    return probability;
}
double Particle::getX() const {
    return x;
}
double Particle::getY() const {
    return y;
}
double Particle::getTheta() const {
    return theta;
}
const vector<double> &Particle::getExpected_measure() const {
    return expected_measure;
}

void Particle::set_state(double input_x, double input_y, double input_theta) {
    x=input_x;
    y=input_y;
    theta=input_theta;
}


//interface
void Particle::show_result() {
    cout<<"id: "<<id<<endl;
    cout<<"x, y, theta: "<<x<<" "<<y<<" "<<theta<<endl;
}

void Particle::show_count() {
    cout<<"particle number:"<<count_particle<<endl;
}

void Particle::show_expected_measure() {
    cout<<"Measurement: [";
    for(int i=0;i<num_landmark;i++) cout<<expected_measure[i]<<" ";
    cout<<"]"<<endl;
}


//constructer
Particle::Particle() {
    //count and id of particle
    count_particle++;
    id=count_particle;
    expected_measure.resize(num_landmark);
}

//move
void Particle::move(double input_alpha, double input_distance) {
//cout<<"move following order ["<<input_alpha<<", "<<input_distance<<"]"<<endl;

    //adding noise
    input_distance+=Gaussian_random(distance_noise);
    input_alpha+=Gaussian_random(steering_noise);
    //restricting steering angle
    if(input_alpha>max_steering_angle) input_alpha=max_steering_angle;
    else if(input_alpha<-max_steering_angle) input_alpha=-max_steering_angle;

    double R=length/tan(input_alpha);   //R is the radius of the circle made by the rear tire
    double beta=input_distance/R;   //beta is the angle for the rear tire
    double cx=x-R*sin(theta);   //cx, cy are the position of the center of the circle made by the rear tire
    double cy=y+R*cos(theta);

    //if beta is not very small, we do the normal procedure
    if(abs(beta)>=0.001) {
        x = cx + R * sin(theta + beta);
        y = cy - R * cos(theta + beta);
        theta += beta;
    }
    //if beta is very small, R diverges, so we regard that the particle is going straight.
    else{
        x+=input_distance*cos(theta);
        y+=input_distance*sin(theta);
    }

    //角度がmod 2piであることを実装
    if(theta<0) theta+=2.0*PI;
    else if(theta>2.0*PI) theta+= -2.0*PI;
}

//measurement
void Particle::expect_measure(vector<Landmarks> landmarks) {
    //for debug
/*x=30;
y=20;
theta=PI/5;//0;
 */

    //for each landmark, evaluate the expected measured values
    for(int i=0;i<num_landmark;i++){
        double xl=landmarks[i].get_x_landmarks();
        double yl=landmarks[i].get_y_landmarks();
        double phi=atan2((yl-y),(xl-x))-theta;

        if(phi<0) phi+= 2.0*PI;
        if(phi>2.0*PI) phi+= -2.0*PI;

        expected_measure[i]=phi;
//cout<<"landmark id:"<<i<<" phi="<<expected_measure[i]<<endl;
    }
}

void Particle::evaluate_prob(double phi[num_landmark]) {

//for debug
/*phi[0]=5.3764;
phi[1]=3.10111;
phi[2]=1.30127;
phi[3]=0.223666;
*/

    double exponent=0;
    for(int i=0;i<num_landmark;i++){
        double offset=phi[i]-expected_measure[i];
        //difference of angle is mod PI
        while(!(offset>0 && offset<PI)) {
            if (offset > PI) offset -= PI;
            if(offset<0) offset+=PI;
        }
//cout<<i<<" "<<offset<<endl;
        exponent+=offset*offset/(2.0*bearing_noise*bearing_noise);
    }
    probability=exp(-exponent);
    if(probability>0.8) {
        cout << "probability of particle " << id << ":" << probability << endl;
        cout<<"its position and angle:"<<x<<" "<<y<<" "<<theta<<endl;
    }
}