#include "main.h"

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
#define RU_Port 9

// IMU
#define LIMU_Port 15
#define RIMU_Port 16

// Distance
#define Distance_Port 12

// Optical
#define Intake_Optical_Port 1
#define Middle_Uptake_Optical_Port 5
#define Top_Uptake_Optical_Port 2

// Encoder
#define HEnc_Top_Port 'e'
#define HEnc_Bottom_Port 'f'
#define VEnc_Top_Port 'g'
#define VEnc_Bottom_Port 'h'

#define Bottom_Line_Port 'd'
#define Middle_Line_Port 'c'
#define Top_Line_Port 'b'

/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),
      RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),

      LI (LI_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES),
      RI (RI_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),

      LU (LU_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),
      RU (RU_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu LIMU (LIMU_Port),
    RIMU (RIMU_Port);
Distance Distance_Sensor (Distance_Port);
Optical Intake_Optical (Intake_Optical_Port),
        Middle_Uptake_Optical (Middle_Uptake_Optical_Port),
        Top_Uptake_Optical (Top_Uptake_Optical_Port);
ADILineSensor Bottom_Line (Bottom_Line_Port),
              Middle_Line (Middle_Line_Port),
              Top_Line (Top_Line_Port);
ADIEncoder HEnc (HEnc_Top_Port,HEnc_Bottom_Port,false),
           VEnc (VEnc_Top_Port,VEnc_Bottom_Port,false);

/* ********** Creates Controller ********** */

Controller Main (CONTROLLER_MASTER);

/* ********** Creates Tasks ********** */

Task *trackingTask = nullptr;
Task *chassisTask = nullptr;
