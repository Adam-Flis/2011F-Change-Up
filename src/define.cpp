#include "main.h"

/* ********** Define Motor Ports ********** */

#define LFD_Port 1
#define LBD_Port 2
#define RFD_Port 3
#define RBD_Port 4
#define Bottom_Intake_Left_Port 5
#define Bottom_Intake_Right_Port 6
#define Arm_Port 7
#define Top_Intake_Port 8

/* ********** Define Sensor Ports ********** */

#define IMU_Port 9
#define Left_Encoder_Top_Port 'a'
#define Left_Encoder_Bottom_Port 'b'
#define Right_Encoder_Top_Port 'c'
#define Right_Encoder_Bottom_Port 'd'
#define Middle_Encoder_Top_Port 'e'
#define Middle_Encoder_Bottom_Port 'f'
#define Arm_Potentiometer_Port 'g'

/* ********** Creates Motors ********** */

Motor LFD (LFD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor LBD (LBD_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor RFD (RFD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor RBD (RBD_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor BLI (Bottom_Intake_Left_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES);
Motor BRI (Bottom_Intake_Right_Port,MOTOR_GEARSET_6,true,MOTOR_ENCODER_DEGREES);
Motor TI (Top_Intake_Port,MOTOR_GEARSET_6,false,MOTOR_ENCODER_DEGREES);
Motor Arm (Arm_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);

/* ********** Creates Sensors ********** */

Imu IMU (IMU_Port);
ADIEncoder LEnc (Left_Encoder_Top_Port,Left_Encoder_Bottom_Port,true);
ADIEncoder REnc (Right_Encoder_Top_Port,Right_Encoder_Bottom_Port,false);
ADIEncoder MEnc (Middle_Encoder_Top_Port,Middle_Encoder_Bottom_Port,false);
ADIAnalogIn ArmPot (Arm_Potentiometer_Port);

/* ********** Creates Controller ********** */

Controller Master (CONTROLLER_MASTER);
