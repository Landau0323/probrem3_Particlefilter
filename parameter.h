//
// Created by 研究用 on 2017/08/16.
//

#ifndef PROBREM3_PARTICLEFILTER_PARAMETER_H
#define PROBREM3_PARTICLEFILTER_PARAMETER_H

const double PI=3.1415;

const double length=20.0;
const double world_size=100.0;
const int num_landmark=4;

const double max_steering_angle=PI/4.0;

//these noises are Gaussian
const double bearing_noise=0.3; //If we set as 0.1, it does not work!
const double steering_noise=0.1;
const double distance_noise=5.0;

//for test
/*const double steering_noise=0.0;
const double distance_noise=0.0;
*/

const int number_particle=2000;


#endif //PROBREM3_PARTICLEFILTER_PARAMETER_H
