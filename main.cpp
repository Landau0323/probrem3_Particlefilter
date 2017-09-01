#include <iostream>
#include "Ensemble.h"

using namespace std;

int main() {
    //install landmarks
    cout<<"install landmarks"<<endl;
    vector<Landmarks> landmarks(num_landmark);
    landmarks[0].setposition_landmarks(world_size,0);
    landmarks[1].setposition_landmarks(0,0);
    landmarks[2].setposition_landmarks(0,world_size);
    landmarks[3].setposition_landmarks(world_size,world_size);
    cout<<endl;

    ///////////////test for class Particle///////////////
    Particle particle;

    //move
    cout<<"test for move function"<<endl;
    //test case 1: move following [0,10], [PI/6,10], [0,20]
    cout<<"test case 1"<<endl;
    particle.set_state(0,0,0);
    particle.show_result();
    particle.move(0,10);
    particle.show_result();
    particle.expect_measure(landmarks); //results [0 3.14159 1.67046 0.837981]
    particle.show_expected_measure();
    particle.move(PI/6,10);
    particle.show_result();
    particle.expect_measure(landmarks); //results [5.97645 2.92478 1.48097 0.599492]
    particle.show_expected_measure();
    particle.move(0,20);
    particle.show_result();
    particle.expect_measure(landmarks); //results [5.87797 3.03333 1.68001 0.701242]
    particle.show_expected_measure();
    cout<<endl;

/*
    //test case 2: move following [-0.2,10] for ten times
    cout<<"test case 2"<<endl;
    particle.set_state(0,0,0);
    particle.show_result();
    for(int i=0;i<10;i++){
        particle.move(-0.2,10);
        particle.show_result();
        particle.expect_measure(landmarks);
        particle.show_expected_measure();
    }
    cout<<endl;

    //test case 3: eight movements (2*PI/10=0.62831853071 20)


    //measure
    cout<<"test for measurement function"<<endl;
    //test case 1
    cout<<"test case 1"<<endl;
    particle.set_state(30,20,0);
    particle.show_result();
    particle.expect_measure(landmarks);
    particle.show_expected_measure();
    cout<<endl;

    //test case 2
    cout<<"test case 2"<<endl;
    particle.set_state(30,20,PI/5);
    particle.show_result();
    particle.expect_measure(landmarks);
    particle.show_expected_measure();
    cout<<endl;
    */

    ///////////////Particle filter start///////////////
    cout<<"Particle filter starts!"<<endl;
    Ensemble* pE=new Ensemble(number_particle);
    pE->set_ground_truth(0,0,0);
    pE->write_result();
    pE->write_ground_truth();

    //proceed time
    double alpha,distance;
    //movement
    alpha=0;
    distance=10;
    cout<<"1st move. Inputted alpha and distance:["<<alpha<<" "<<distance<<"]"<<endl;
    pE->movement(alpha,distance);
    pE->show_summary();
    pE->show_ground_truth();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;

    //measurement
    double phi[num_landmark];
    phi[0]=0; phi[1]=3.14159; phi[2]=1.67046; phi[3]=0.837981;
    cout<<"1st measurement. Input measured values:[";
    for(int i=0;i<num_landmark;i++) cout<<phi[i]<<", ";
    cout<<"]"<<endl;
    pE->measurement(phi,landmarks);
    pE->show_summary();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;


    //movement
    alpha=0.523583;
    distance=10;
    cout<<"2nd move. Inputted alpha and distance:["<<alpha<<" "<<distance<<"]"<<endl;
    pE->movement(alpha,distance);
    pE->show_summary();
    pE->show_ground_truth();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;

    //measurement
    phi[0]=5.97645; phi[1]=2.92478; phi[2]=1.48097; phi[3]=0.599492;
    cout<<"2nd measurement. Input measured values:[";
    for(int i=0;i<num_landmark;i++) cout<<phi[i]<<", ";
    cout<<"]"<<endl;
    pE->measurement(phi,landmarks);
    pE->show_summary();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;

    //movement
    alpha=0;
    distance=20;
    cout<<"3rd move. Inputted alpha and distance:["<<alpha<<" "<<distance<<"]"<<endl;
    pE->movement(alpha,distance);
    pE->show_summary();
    pE->show_ground_truth();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;

    //measurement
    phi[0]=5.87797; phi[1]=3.03333; phi[2]=1.68001; phi[3]=0.701242;
    cout<<"3rd measurement. Input measured values:[";
    for(int i=0;i<num_landmark;i++) cout<<phi[i]<<", ";
    cout<<"]"<<endl;
    pE->measurement(phi,landmarks);
    pE->show_summary();
    pE->write_result();
    pE->write_ground_truth();
    cout<<endl;

    return 0;
}

//test case 1: [[4.746936 3.859782 3.045217 2.045506],
//                [3.510067 2.916300 2.146394 1.598332],
//                [2.972469 2.407489 1.588474 1.611094],
//                [1.906178 1.193329 0.619356 0.807930],
//                [1.352825 0.662233 0.144927 0.799090],
//                [0.856150 0.214590 5.651497 1.062401],
//                [0.194460 5.660382 4.761072 2.471682],
//                [5.717342 4.736780 3.909599 2.342536]]
//          ->final position:[93.476 75.186 5.2664]
