#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 13
#define LBD_Port 11
#define RFD_Port 18
#define RBD_Port 20

#define Intake_Left_Port 2
#define Intake_Right_Port 10

#define Uptake_Left_Port 1
#define Uptake_Right_Port 8

/* ********** Define Sensor Ports ********** */

#define LIMU_Port 14
#define RIMU_Port 15

#define Distance_Port 5

#define Intake_Optical_Port 3
#define Uptake_Optical_Port 4

#define Bottom_Line_Port 'd'
#define Middle_Line_Port 'c'
#define Top_Line_Port 'b'

#define Horizontal_Encoder_Top_Port 'e'
#define Horizontal_Encoder_Bottom_Port 'f'
#define Vertical_Encoder_Top_Port 'g'
#define Vertical_Encoder_Bottom_Port 'h'

/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),
      RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),

      LI (Intake_Left_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES),
      RI (Intake_Right_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),

      LU (Uptake_Left_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),
      RU (Uptake_Right_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu LIMU (LIMU_Port),
    RIMU (RIMU_Port);
Distance Distance_Sensor (Distance_Port);
Optical Intake_Optical (Intake_Optical_Port),
        Uptake_Optical (Uptake_Optical_Port);
ADILineSensor Bottom_Line (Bottom_Line_Port),
              Middle_Line (Middle_Line_Port),
              Top_Line (Top_Line_Port);
ADIEncoder HEnc (Horizontal_Encoder_Top_Port,Horizontal_Encoder_Bottom_Port,false),
           VEnc (Vertical_Encoder_Top_Port,Vertical_Encoder_Bottom_Port,false);

/* ********** Creates Controller ********** */

Controller Main (CONTROLLER_MASTER);


/* ********** Creates Tasks ********** */

Task *trackingTask = nullptr;
Task *chassisTask = nullptr;
