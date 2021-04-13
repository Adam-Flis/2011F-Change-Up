#include "main.h"

/* ********** Define Ports ********** */

// Drivetrain
#define LFD_Port 13
#define LBD_Port 14
#define RFD_Port 19
#define RBD_Port 17

// Intake
#define LI_Port 3
#define RI_Port 20

// Uptake
#define LU_Port 4
#define RU_Port 7

// IMU
#define LIMU_Port 15
#define RIMU_Port 16

// Distance
#define Distance_Port 12

// Optical
#define Intake_Optical_Port 1
#define Bottom_Uptake_Optical_Port 5
#define Middle_Uptake_Optical_Port 2

// Encoder
#define HEnc_Top_Port 'e'
#define HEnc_Bottom_Port 'f'
#define VEnc_Top_Port 'g'
#define VEnc_Bottom_Port 'h'

/* ********** Create Motors, Sensors, Variables ********** */

// Drivetrain
Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),
      RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),

// Intake
      LI (LI_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES),
      RI (RI_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),

// Uptake
      LU (LU_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),
      RU (RU_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES);

// IMU
Imu LIMU (LIMU_Port),
    RIMU (RIMU_Port);

// Distance
Distance Distance_Sensor (Distance_Port);

// Optical
Optical Intake_Optical (Intake_Optical_Port),
        Bottom_Uptake_Optical (Bottom_Uptake_Optical_Port),
        Middle_Uptake_Optical (Middle_Uptake_Optical_Port);

// Encoder
ADIEncoder HEnc (HEnc_Top_Port,HEnc_Bottom_Port,false),
           VEnc (VEnc_Top_Port,VEnc_Bottom_Port,false);

// Controller
Controller Main (CONTROLLER_MASTER);

// Variables
// Optical
double blueThresh = 200;
double redThresh = 18;
// Distance
double distanceThresh = 220;

// Tasks
Task *trackingTask = nullptr;
Task *chassisTask = nullptr;
Task *intakeTask = nullptr;
Task *uptakeTask = nullptr;
