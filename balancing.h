
void Transferfunction();
 integral = lastintegral - (Kwi/Ki)*WheelPositionIntegral;
 WheelPositionIntegral = 0;

void balancing()
{

	time1[T4]=0;
	while(true)
	{

		if ((counter2 == true) && (time1[T4]>2000) && ((abs(PID)) < 5))
			{
			counter2 = false;

			WheelPosition = 0; 
			WheelPositionIntegral=0; 
			Lastposition = 0;
			nMotorEncoder[MotorB] = 0;
			nMotorEncoder[MotorC] = 0;
			Start_position = nMotorEncoder[MotorB];

			turn();


			Lastposition = 0;
			nMotorEncoder[MotorB] = 0;
			nMotorEncoder[MotorC] = 0;
			Start_position = nMotorEncoder[MotorB];



			WheelPosition = 0; 
			WheelPositionIntegral=0;
			}

		AngularRot = read_angularrot();

		Angle += AngularRot*dt; //RiemannSum
		Error = Angle;
		integral += Error*dt; //RiemannSum
		WheelPosition = nMotorEncoder[MotorB] - Start_position;
		WheelPositionIntegral += WheelPosition*dt;
		PositionDerivative = (WheelPosition - Lastposition)/dt;

		PID = Kp*Error + Kd*AngularRot + Ki*integral + Kw*WheelPosition + Kdw*PositionDerivative + Kwi*WheelPositionIntegral;
		motorpower = batteryPower*PID;
		turnOffset = nMotorEncoder[MotorC] - nMotorEncoder[MotorB];


		motor[MotorB] = motorpower*0.88;
		motor[MotorC] = motorpower;
		Lastposition = WheelPosition;

		display_information(Angle,integral,AngularRot,WheelPosition,PositionDerivative);

		wait10Msec(1);

		if(CheckButtonRun() == 7)
			break;
				
}}
