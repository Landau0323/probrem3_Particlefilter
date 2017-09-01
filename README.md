# probrem3_Particlefilter
Codes for the problems in udacity program "Artificial Intelligence for Robotics" (3: particle filter). 

This is a program for localization of car moving on a plane following the inputted order. 
When the robot moves, it specifies the steering angle, and then go straight. 
The order for movement is given in terms of (theta, R), which are the steering angle and the length of going straight. 
The motion of the car is modeled with bicycle model.
The measurement gives the angles from the car to the landmarks. 
By running the code and plotting the result, one can see visually that the uncertainty on the position of the car decreases after measurements.
