#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 14
#define LBD_Port 15
#define RFD_Port 17
#define RBD_Port 16
#define Intake_Left_Port 11
#define Intake_Right_Port 20
#define Uptake_Top_Port 2
#define Uptake_Bottom_Port 1

/* ********** Define Sensor Ports ********** */

#define IMU_Port 9
#define Left_Encoder_Top_Port 'a'
#define Left_Encoder_Bottom_Port 'b'
#define Right_Encoder_Top_Port 'c'
#define Right_Encoder_Bottom_Port 'd'
#define Middle_Encoder_Top_Port 'e'
#define Middle_Encoder_Bottom_Port 'f'

/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES),
      RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),
      RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES),
      LI (Intake_Left_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES),
      RI (Intake_Right_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),
      TU (Uptake_Top_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES),
      BU (Uptake_Bottom_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu IMU (IMU_Port);
ADIEncoder LEnc (Left_Encoder_Top_Port,Left_Encoder_Bottom_Port,true),
           REnc (Right_Encoder_Top_Port,Right_Encoder_Bottom_Port,false),
           MEnc (Middle_Encoder_Top_Port,Middle_Encoder_Bottom_Port,false);

/* ********** Creates Controller ********** */

Controller Main (CONTROLLER_MASTER);
