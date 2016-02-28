void turn()
{
	float Refspeed = 0; // When turning lower velcocity is desired
	PlayImmediateTone(1000, 20); 
	float refpos = 0; // When turning, reset the ref.pos which has been moved forward during run-mode

		time1[T2]=0;
		time1[T3]=0;
		
		while(true)
		{
		AngularRot=read_angularrot(); // read the angular rotation during turn to be able to keep balancing


		Angle += AngularRot*dt; 
		Error = Angle;
		integral += Error*dt; 
		refpos += Refspeed*0.01;
		WheelPosition = nMotorEncoder[MotorB] - Start_position + refpos;
		WheelPositionIntegral += WheelPosition*dt;
		PositionDerivative = (WheelPosition - Lastposition)/dt + Refspeed*BatteryPowerSpeed;
		PID = Kp*Error + Kd*AngularRot + Ki*integral + Kw*WheelPosition + Kdw*PositionDerivative + Kwi*WheelPositionIntegral;


		motorpower = batteryPower*PID;
		turnOffset += (nMotorEncoder[MotorC] - nMotorEncoder[MotorB]);

		if(time1[T3] < 5000)
		{
			motor[motorB]=motorpower*1.3; // Go faster with one Wheel
			motor[motorC]=motorpower-30;  // reverse / go slowly with the other wheel, a nice smooth turn 
		} 

		turnOffset = 0; // we now dont want to compensate for old turn offsets, see ConstAndVariables.h
		Lastposition = WheelPosition; // The last position would be in a turn, reset Lastposition, see ConstAndVariables.h for declaration

		display_information(Angle,integral,AngularRot,WheelPosition,PositionDerivative) // Display information, see Functions.h

		if (break_on_time()) //Breaks the turn while loop, Goes back into balancing. 
			;
		else
			break;
}}
