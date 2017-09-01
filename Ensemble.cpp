//
// Created by 研究用 on 2017/08/16.
//

#include "Ensemble.h"
#include "parameter.h"

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
#include <random>

using namespace std;

double uniform_random(double upper=1, double lower=0);

//set ground truth
void Ensemble::set_ground_truth(double x_input, double y_input, double theta_input) {
    ground_truth.set_state(x_input,y_input,theta_input);
}

//constructor
Ensemble::Ensemble(int N) {
    cout<<"create ensemble"<<endl;
    ensemble.resize(N);
    Particle::show_count();

    //initialize　particles position and direction
    cout<<"initialize ensemble"<<endl;
    for(int i=0;i<ensemble.size();i++){
        //real case: uniformly randomize
        double x0=uniform_random(world_size,0);
        double y0=uniform_random(world_size,0);
        double theta0=uniform_random(2*PI,0);

        ensemble[i].set_state(x0,y0,theta0);
//ensemble[i].show_result();
    }

}

////////////////movement phase////////////////
void Ensemble::movement(double input_alpha, double input_distance) {
    cout<<"movement"<<endl;
    for(int i=0;i<ensemble.size();i++) ensemble[i].move(input_alpha, input_distance);
    ground_truth.move(input_alpha, input_distance);
}

////////////////measurement phase////////////////
void Ensemble::measurement(double phi[num_landmark], vector<Landmarks> landmarks) {
    cout<<"measurement"<<endl;
//    evaluate_true_position(phi,landmarks);
    expect_measurement(landmarks);
    evaluate_weight(phi);
    resampling();   //resampling
}

void Ensemble::expect_measurement(vector<Landmarks> landmarks) {
    cout<<"expect measured values"<<endl;
    for(int i=0;i<number_particle;i++) ensemble[i].expect_measure(landmarks);
    ground_truth.expect_measure(landmarks);
    cout<<"expected measurement for ground truth:";
    ground_truth.show_expected_measure();
}

void Ensemble::evaluate_weight(double phi[num_landmark]) {
    cout<<"evaluate weight"<<endl;
    for(int i=0;i<number_particle;i++) ensemble[i].evaluate_prob(phi);

    ground_truth.evaluate_prob(phi);    //evaluate probability for each particle
    cout<<"weight for ground truth (this should be one):"<<ground_truth.getProbability()<<endl;
}

//std::discrete_distributionを使って書く. (参考：https://github.com/BenniRippel/P8_Particle_Filter/blob/master/src/particle_filter.cpp)
void Ensemble::resampling() {
    cout<<"resampling"<<endl;
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    //weightsにrobot N個それぞれの重みを格納
    vector<double> weights(number_particle);
    for(int i=0;i<number_particle;i++) weights[i]=ensemble[i].getProbability();

    //discrete_distributionを使って重みを反映した乱数生成（乱数は整数、範囲は0からnumber_particleまで）
    discrete_distribution<> distri (weights.begin(), weights.end());

    //resample後のparticle
    vector<Particle> resampled_particles(number_particle);
    for(int i=0;i<number_particle;i++) {
        int id=distri(engine);
        resampled_particles[i]=ensemble[id];
        if(resampled_particles[i].getProbability()>0.8){
            cout<<"weight:"<<resampled_particles[i].getProbability()<<" position:";//<<" "<<ensemble[n].getWeight()<<endl;
            resampled_particles[i].show_result();
        }
    }

    ensemble.clear();
    ensemble=resampled_particles;
    resampled_particles.clear();
}

/*
//4つのphiから真のx,y,thetaを出す
void Ensemble::evaluate_true_position(double phi[num_landmark],vector<Landmarks> landmarks) {
    cout<<"evaluate true position"<<endl;
//for(int i=0;i<num_landmark;i++) cout<<phi[i]<<" ";
    Particle* ptest_particle=new Particle;
    double x,y,theta;
    x=y=theta=0;
    ptest_particle->set_state(x,y,theta);

    //parameters for loop
    double num_loop=100;
    double delta_xy=world_size/num_loop;
    double delta_theta=2.0*PI/num_loop;

    for(int i=0;i<num_loop;i++){
        x=(double)i*delta_xy;
        for(int j=0;j<num_loop;j++){
            y=(double)j*delta_xy;
            for(int k=0;k<num_loop;k++){
                theta=(double)k*delta_theta;

//cout<<x<<" "<<y<<" "<<theta<<endl;
                ptest_particle->set_state(x,y,theta);
                ptest_particle->expect_measure(landmarks);
                double offset=0;
                for(int n=0;n<num_landmark;n++){
                    offset+=abs(ptest_particle->getExpected_measure()[n] - phi[n]);
                }
                if(offset<6*bearing_noise) cout<<"true position and angle:"<<x<<" "<<y<<" "<<theta<<endl;
            }
        }
    }

    delete ptest_particle;
}
 */

/////////////interface/////////////
void Ensemble::show_result() {
    cout<<"show result"<<endl;
    for(int i=0;i<ensemble.size();i++){
        ensemble[i].show_result();
    }
}

void Ensemble::show_summary() {
    cout<<"show summary (average of x, y, theta)"<<endl;
    double average_x,average_y,average_theta;
    average_x=average_y=average_theta=0;

    for(int i=0;i<ensemble.size();i++){
        average_x+=ensemble[i].getX()/number_particle;
        average_y+=ensemble[i].getY()/number_particle;
        average_theta+=ensemble[i].getTheta()/number_particle;
    }

    cout<<"["<<average_x<<", "<<average_y<<", "<<average_theta<<"]"<<endl;
}

void Ensemble::write_result() {
    string filename="particles.dat";
    ofstream fout;  //書き込み用のofstreamを宣言
    fout.open(filename,ios::app);

//    cout<<"write results"<<endl;
    for(int i=0;i<ensemble.size();i++){
        fout<< ensemble[i].getX()<<" "<<ensemble[i].getY()<<" "
            <<ensemble[i].getTheta() <<endl;
    }
    fout<<endl<<endl;
    fout.close();
}

void Ensemble::show_ground_truth() {
    cout<<"ground truth:["<<ground_truth.getX()<<", "
        <<ground_truth.getY()<<", "<<ground_truth.getTheta()<<"]"<<endl;
}

void Ensemble::write_ground_truth() {
    //true position of robot
    string filename="true_robot.dat";
    ofstream fout_true;
    fout_true.open(filename,ios::app);
    fout_true<< ground_truth.getX()<<" "<<ground_truth.getY()<<" "
        <<ground_truth.getTheta() <<endl;
    fout_true<<endl<<endl;
    fout_true.close();
}
