#include "ukf.h"
#include <gtest/gtest.h>
#include "Eigen/Dense"
#include <iostream>



TEST(PredictRadar, sampleInput)
{

  UKF testUkf;
  testUkf.x_ << 5.7441,
         1.3800,
         2.2049,
         0.5015,
         0.3528;

  Eigen::MatrixXd S(3,3);
  Eigen::VectorXd z_exp(2);
  Eigen::MatrixXd Tc(5,3);



  Eigen::MatrixXd Xsig_predTest(5,15);
  Xsig_predTest<< 5.9374,  6.0640,   5.925,  5.9436,  5.9266,  5.9374,  5.9389,  5.9374,  5.8106,  5.9457,  5.9310,  5.9465,  5.9374,  5.9359,  5.93744,
           1.48,  1.4436,   1.660,  1.4934,  1.5036,    1.48,  1.4868,    1.48,  1.5271,  1.3104,  1.4787,  1.4674,    1.48,  1.4851,    1.486,
          2.204,  2.2841,  2.2455,  2.2958,   2.204,   2.204,  2.2395,   2.204,  2.1256,  2.1642,  2.1139,   2.204,   2.204,  2.1702,   2.2049,
         0.5367, 0.47338, 0.67809, 0.55455, 0.64364, 0.54337,  0.5367, 0.53851, 0.60017, 0.39546, 0.51900, 0.42991, 0.530188,  0.5367, 0.535048,
          0.352, 0.29997, 0.46212, 0.37633,  0.4841, 0.41872,   0.352, 0.38744, 0.40562, 0.24347, 0.32926,  0.2214, 0.28687,   0.352, 0.318159;

  testUkf.Xsig_pred_ = Xsig_predTest;

    // radar measurement noise standard deviation radius in m
  testUkf.std_radr_ = 0.3;

  // radar measurement noise standard deviation angle in rad
  testUkf.std_radphi_ = 0.0175;

  // radar measurement noise standard deviation radius change in m/s
  testUkf.std_radrd_ = 0.1;


  testUkf.PredictRadar(z_exp,S, Tc);


  

  Eigen::VectorXd z_predTest(3);
  z_predTest<<6.12155, 0.245993, 2.10313;

  Eigen::MatrixXd STest(3,3);
  STest <<0.0946171, -0.000139448, 0.00407016,
  -0.000139448, 0.000617548, -0.000770652,
0.00407016, -0.000770652, 0.0180917;



  ASSERT_LT((z_exp- z_predTest).norm(), 10e-4);
//  ASSERT_LT((S- STest).norm(), 10e-5);

}


TEST(PredictSigmaPoints, inputPrediction)
{ 


  UKF testUkf;
  testUkf.x_ << 5.7441,
         1.3800,
         2.2049,
         0.5015,
         0.3528;


   testUkf.P_ <<     0.0043,   -0.0013,    0.0030,   -0.0022,   -0.0020,
          -0.0013,    0.0077,    0.0011,    0.0071,    0.0060,
           0.0030,    0.0011,    0.0054,    0.0007,    0.0008,
          -0.0022,    0.0071,    0.0007,    0.0098,    0.0100,
          -0.0020,    0.0060,    0.0008,    0.0100,    0.0123;

   testUkf.std_a_ = 0.2;
   testUkf.std_yawdd_ = 0.2;


  
   double delta_t = 0.1;
   Eigen::MatrixXd XsigTest(7,15);
   XsigTest.fill(0);

  
   XsigTest <<
5.7441,  5.85768,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,  5.63052,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,
  1.38,  1.34566,  1.52806,     1.38,     1.38,     1.38,     1.38,     1.38,  1.41434,  1.23194,     1.38,     1.38,     1.38,     1.38,     1.38,
2.2049,  2.28414,  2.24557,  2.29582,   2.2049,   2.2049,   2.2049,   2.2049,  2.12566,  2.16423,  2.11398,   2.2049,   2.2049,   2.2049,   2.2049,
0.5015,  0.44339, 0.631886, 0.516923, 0.595227,   0.5015,   0.5015,   0.5015,  0.55961, 0.371114, 0.486077, 0.407773,   0.5015,   0.5015,   0.5015,
0.3528, 0.299973, 0.462123, 0.376339,  0.48417, 0.418721,   0.3528,   0.3528, 0.405627, 0.243477, 0.329261,  0.22143, 0.286879,   0.3528,   0.3528,
     0,        0,        0,        0,        0,        0,  0.34641,        0,        0,        0,        0,        0,        0, -0.34641,        0,
     0,        0,        0,        0,        0,        0,        0,  0.34641,        0,        0,        0,        0,        0,        0, -0.34641;



   testUkf.PredictSigmaPoints(XsigTest, delta_t);

   Eigen::MatrixXd Xsig_predTest(5,15);

   Xsig_predTest<< 
 5.93553,  6.06251, 5.92217,  5.9415,  5.92361,  5.93516,  5.93705,  5.93553,  5.80832,  5.94481,  5.92935,  5.94553,  5.93589,  5.93401,  5.93553,
 1.48939,  1.44673, 1.66484, 1.49719,    1.508,  1.49001,  1.49022,  1.48939,   1.5308,  1.31287,  1.48182,  1.46967,  1.48876,  1.48855,  1.48939,
  2.2049,  2.28414, 2.24557, 2.29582,   2.2049,   2.2049,  2.23954,   2.2049,  2.12566,  2.16423,  2.11398,   2.2049,   2.2049,  2.17026,   2.2049,
 0.53678, 0.473387,0.678098,0.554557, 0.643644, 0.543372,  0.53678, 0.538512, 0.600173, 0.395462, 0.519003, 0.429916, 0.530188,  0.53678, 0.535048,
  0.3528, 0.299973,0.462123,0.376339,  0.48417, 0.418721,   0.3528, 0.387441, 0.405627, 0.243477, 0.329261,  0.22143, 0.286879,   0.3528, 0.318159;



  ASSERT_LT((testUkf.Xsig_pred_- Xsig_predTest).norm(), 10e-5);

}



TEST(GenerateSigmaPointsTest, sampleAugmentedMatrix)
{ 

  UKF testUkf;
  testUkf.x_ << 5.7441,
         1.3800,
         2.2049,
         0.5015,
         0.3528;


   testUkf.P_ <<     0.0043,   -0.0013,    0.0030,   -0.0022,   -0.0020,
          -0.0013,    0.0077,    0.0011,    0.0071,    0.0060,
           0.0030,    0.0011,    0.0054,    0.0007,    0.0008,
          -0.0022,    0.0071,    0.0007,    0.0098,    0.0100,
          -0.0020,    0.0060,    0.0008,    0.0100,    0.0123;

   testUkf.std_a_ = 0.2;
   testUkf.std_yawdd_ = 0.2;


   Eigen::VectorXd x_aug(7);
   x_aug.fill(0);
  
   Eigen::MatrixXd xsig_aug(7,15);
   xsig_aug.fill(0);
   
   Eigen::MatrixXd XsigTest(7,15);
   XsigTest.fill(0);

   testUkf.GenerateSigmaPoints(xsig_aug, x_aug);



   XsigTest <<
5.7441,  5.85768,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,  5.63052,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,   5.7441,
  1.38,  1.34566,  1.52806,     1.38,     1.38,     1.38,     1.38,     1.38,  1.41434,  1.23194,     1.38,     1.38,     1.38,     1.38,     1.38,
2.2049,  2.28414,  2.24557,  2.29582,   2.2049,   2.2049,   2.2049,   2.2049,  2.12566,  2.16423,  2.11398,   2.2049,   2.2049,   2.2049,   2.2049,
0.5015,  0.44339, 0.631886, 0.516923, 0.595227,   0.5015,   0.5015,   0.5015,  0.55961, 0.371114, 0.486077, 0.407773,   0.5015,   0.5015,   0.5015,
0.3528, 0.299973, 0.462123, 0.376339,  0.48417, 0.418721,   0.3528,   0.3528, 0.405627, 0.243477, 0.329261,  0.22143, 0.286879,   0.3528,   0.3528,
     0,        0,        0,        0,        0,        0,  0.34641,        0,        0,        0,        0,        0,        0, -0.34641,        0,
     0,        0,        0,        0,        0,        0,        0,  0.34641,        0,        0,        0,        0,        0,        0, -0.34641;



  ASSERT_LT((XsigTest- xsig_aug).norm(), 10e-6);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
