


void run()
{
	float Refspeed =-350.0292; // sets Refspeed, see ConstAndVariable.h
	float refpos = 0; // Avoid old data beein significant
	float refposintegral = 0; // Avoid old data
	
	time1[T2]=0; // timer for a smooth gear up, see Functions.h
	time1[T4]=0; // timer

	PlayImmediateTone(1000, 20); // Alert that run-mode has been activated
	PlaySoundFile("Mario.rso"); // Play Super Mario 8-bit theme song


	if (RaceMode==1) // if RaceMode is active, go faster
		Refspeed = Racespeed;
	
	while(true)
		{
		AngularRot = read_angularrot()

		Angle += AngularRot*dt;
		Error = Angle;
		integral += Error*dt;
		refpos += Refspeed*0.01;
		refposintegral += refpos*0.01;

		WheelPosition = nMotorEncoder[MotorB] - Start_position;
		WheelPositionIntegral += WheelPosition*dt;
		WheelPositionIntegral = 0.99*WheelPositionIntegral;
		PositionDerivative = (WheelPosition - Lastposition)/dt;

		PID = Kp*Error + Kd*AngularRot + Ki*integral + Kw*WheelPosition + Kdw*PositionDerivative + Kwi*WheelPositionIntegral + Kpr*refpos + Kdr*refspeed + Kir*refposintegral;
		motorpower = batteryPower*PID;
		turnOffset += (nMotorEncoder[MotorC] - nMotorEncoder[MotorB]);


		Refspeed = Gear_Up(time1[T2]); // Increase refspeed depending on time, see Functions.h

		motor[MotorB] = motorpower * 0.9137;
		motor[MotorC] = motorpower;

		display_information(Angle,integral,AngularRot,WheelPosition,PositionDerivative) // Display information on NXT-Brick screen

		turnOffset = 0; // Avoid turnOffset getting too significant
		Lastposition = WheelPosition;
		Lastintegral = integral;


		wait10Msec(1);
		// if sonar detects an obstacle or the stop button has been pressed, wait for the right moment, and go back to balancing-mode
		if((CheckButtonStop() == 7) || ((SonarCheck() == 7 ) && (abs(PID)) < 10)) 
			{
			break;
			}

		}

}
