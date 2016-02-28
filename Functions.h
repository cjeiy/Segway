/*Functions*/

int Check_Power(){
float battery = nAvgBatteryLevel; // Built-in RobotC function to aquire batteryvoltage

// A function that gives a proper constant to the motorpower to compensate for the batterpower
if(battery > 7800)
	batteryPower = 0.7;

else if(battery < 7800 && battery > 7300)
	batteryPower = 0.74;

else if(battery < 7300 && battery > 7000)
	batteryPower = 0.78;

else if(battery < 7000)
	batteryPower = 0.8;

PlayImmediateTone(2000, 20);
return batteryPower;

}

void Calibrate_gyros()
	{

	HTGYROstartCal(GYRO1); // Determines the gyroscopes raw data offset in the beginning, prevents drift
	HTGYROstartCal(GYRO2);
	PlayImmediateTone(2000, 20);
	wait10Msec(300);
	PlayImmediateTone(1000, 20);
	}

int Check_if_Racemode() // Check for button-push to enable race mode
{
time1[T10] = 0;
RaceMode=0
while(time1[T10] < 2000) // Waits 2 sec for button-push
	{
	if(SensorValue[S3] == 1) // if button is pressed, RaceMode enabled
		RaceMode = 1;
return RaceMode
	}
}

//Displays information on the NXT brick screen
void display_information(Angle,integral,AngularRot,WheelPosition,PositionDerivative)
	{
	nxtDisplayTextLine(1, "P: %f", Kp*Angle);
	nxtDisplayTextLine(2, "I: %f", Ki*integral);
	nxtDisplayTextLine(3, "D: %f", Kd*AngularRot);
	nxtDisplayTextLine(4, "Pw %f", WheelPosition);
	nxtDisplayTextLine(6, "Dw: %f", Kdw*PositionDerivative);
	wait10Msec(1);
	}

//Reads the angular velocity
void read_angularrot()
	{
	Rawdata= (HTGYROreadRot(GYRO1)- HTGYROreadRot(GYRO2))/2; //Built in function that converts raw data to ang. Velocity
	wait1Msec(1);
	Rawdata += (HTGYROreadRot(GYRO1)- HTGYROreadRot(GYRO2))/2;
	wait1Msec(1);
	Rawdata += (HTGYROreadRot(GYRO1)- HTGYROreadRot(GYRO2))/2;
	wait1Msec(1);
	Rawdata += (HTGYROreadRot(GYRO1)- HTGYROreadRot(GYRO2))/2;
	AngularRot = Rawdata/4; // Takes the average of four readings to prevent bad data from a reading beeing significant
	return AngularRot
	}


bool break_on_time(time1[T3],time1[T1])//a fucntion that is used to break a while loop when turning
{
	if((time1[T3]>5000)) // when 5 seconds has passed that turn is completed --> break out to balancing mode
	{
		if (time1[T1]>1000) // DEN HÄR SKA BORT ?!
		{
			counter += 1;
			time1[T1]=0;
			time1[T3]=0;
			return false; // false --> break the while loop
		}

	}
}

// Checks for button-push --> go from run-mode to balancing-mode
int CheckbuttonStop()
	{

 	if(SensorValue(S3) == 1)// button is pushed
 	{
 		x = true; //we flag the x as true
 		return 3;
 	} // just for returning an integer, no specific data
 	
 	if(x == true)
 		if (time1[T1]>1000) // When 1 second has passed we can break the run-mode
 			{
				counter += 1; //for keeping track of the meaning of button-pushes, if counter is odd we stay in balance, if even we break to run-mode 
				time1[T1]=0;
				x = false;
				return 7; // 7 will break the run while loop
			}
		return 2; //no significance
	}

int CheckButtonRun(){
 	if(SensorValue(S3) == 1)// if button is pressed we flag y for beeing ready to go into run-mode
 	{
 		y = true;
		return 3;	//no significance, just for returning something
	}
 	if((y == true) && (PositionDerivative >= 0)) // y is now true, we wait for the velocity to be in the opposite direction we wanna go in, for more stable forward run
 		{
 		if (time1[T1]>1000)  // for avoiding multiple button pushes
 			{ 
				counter += 1;
				time1[T1]=0;
				y = false;
				return 7; // 7 will break the while loop
			}
		}
	return 2; //no significance, just for returning an integer
	}

int SonarCheck()
{
	if ((SensorValue[S2] < 35) && (RaceMode == 0)) //sonar is only active when not in racemode(Racemode == 0), if sonar detects an obstacle closer than 35 cm, we want to go into turn-mode
		{
		if (time1[T4] >1000) //to avoid multiple button-clicks
			{
			counter2=true; // will activate turn-mode
			return 7       // breaks the run-mode			}
			}
	return 3 //no significance
		}
}

int Gear_Up(time1[T2]) //Will increase velocity during run-mode on different timeintervals to prevent balancing problems
{
	if ((time1[T2]>3000)&&(RaceMode==1)){
			Refspeed=-460;}
	else if ((time1[T2]>5000)&&(RaceMode==1)){
			Refspeed=-550;}
	else if ((time1[T2]>6500)&&(RaceMode==1)){
			Refspeed=-650;}
	else if ((time1[T2]>8000)&&(RaceMode==1)){
			Refspeed=-750;}
	else if ((time1[T2]>10000)&&(RaceMode==1)){
			Refspeed=-800;}

	return Refspeed  
	}

