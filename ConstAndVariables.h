
/*Constants*/

float dt = 0.01; // Timeinterval for gyroscope readings

float Kp = 34.75822; // The proportional constant for the Angular-PID
float Ki = -2.022331;// The integral constant for the Angular-PID
float Kd = 1.02213131;// The derivative constant for the Angular-PID

float Kw = 0.4292331;// The proportional constant for the Encoder-PID
float Kdw = 0.122223;// The integral constant for the Encoder-PID
float Kwi = 0.00249992203;// The derivative constant for the Encoder-PID

float Refspeed = -350; // The reference speed, a constant that controls the speed by manipulating referenceposition(How much the ref.pos is supposed to move forward)
float batteryPower; // Used in a function to allways give a similar behaviour undepending on real battery Voltage

/*Variables*/

float T10 = 0;

float PID = 0; //The total PID (ENC.PID + ANG.PID )
float Error = 0; // Angular error from desired state
float WheelPosition = 0; // Encoder error from desired state
float Offset = 0; //NOT USED???
float AngularRot = 0; // The rotational velocity 
float Angle = 0; // The same as error
float integral = 0; //The integral term in the ANG.PID
float WheelPositionIntegral = 0; //The Integral term in the ENC.PID
float motorpower = 0; //The motorpower beeing fed to the motors
float Lastposition = 0; // Previous WheelPosition
float Rawdata = 0; // The angular velocity before, the average of four ang. velocity readings is called AngularRot
float PositionDerivative = 0; // The derivative term in the ENC.PID
float turnOffset = 0 ; // The difference between how far the wheels has moved, used to compensate for turning
float Start_position = 0; // Start position of Encoder
float Lastintegral = 0; // The previous value of the Ang. Integral
float sonarValue = 0; // Declartion of Sonar Value Variable
int counter = 1; // used for determining buttonpushes, odd counter executes balancing mode, even counter executes runmode
bool counter2 =false; // used for executing turn when sonar detects obstacle
bool y = false; // a variable which is flagged when run-mode is executed
bool x = false; // a variable which is flagged when balancing-mode should be executed from run-mode


int RaceMode = 0; // Decleration of Race Mode Variable
float Racespeed = -400.5; // A higher standard speed which is used when racemode is executed