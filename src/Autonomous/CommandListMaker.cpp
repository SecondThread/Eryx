/*
 * CommandListMaker->cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: lazar
 */
#include <Autonomous/CommandListMaker.h>
#include "WPILib.h"
#define TURNIF_NOSHOT false

CommandListMaker::CommandListMaker(IProfile *p) {
	profile = p;
	storage = NULL;
	stick = new Joystick(1);

	// TODO Auto-generated constructor stub
}

CommandListMaker::~CommandListMaker() {
	delete storage;
}

void CommandListMaker::RobotInit() {
	autoPosition = new SendableChooser();
	autoPosition->AddDefault(low, (void*) &low);
	autoPosition->AddObject(ram, (void*) &ram);
	autoPosition->AddObject(rock, (void*) &rock);
	autoPosition->AddObject(port, (void*) &port);
	autoPosition->AddObject(chev, (void*) &chev);
	autoPosition->AddObject(sall, (void*) &sall);
	autoPosition->AddObject(deb, (void*) &deb);
	autoPosition->AddObject(moat, (void*) &moat);
	autoPosition->AddObject(draw, (void*) &draw);
	SmartDashboard::PutData("Position", autoPosition);

	autoDefence = new SendableChooser();
	autoDefence->AddDefault(pos1, (void*) &pos1);
	autoDefence->AddObject(pos2, (void*) &pos2);
	autoDefence->AddObject(pos3, (void*) &pos3);
	autoDefence->AddObject(pos4, (void*) &pos4);
	autoDefence->AddObject(pos5, (void*) &pos5);
	SmartDashboard::PutData("Defence", autoDefence);
}

void CommandListMaker::makeBasic() {

	if(storage != NULL){
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();


	driveStep* step1 = new driveStep();
	step1->command = stepBase::driveStraight;
	step1->speed = 1.0;
	step1->distance = 1;
	step1->stepNum = 0;
	step1->speed = 1.0;
	storage->push_back(step1);

	turnStep* stp = new turnStep();
	stp->command = stepBase::turn;
	stp->angle = SmartDashboard::GetNumber("Auto Angle", 0);
	stp->speed = .5;
	stp->stepNum = 1;
	//storage->push_back(stp);

	stepBase *step2 = new stepBase();
	step2->command = stepBase::target;
	step2->stepNum = 2;
	//storage->push_back(step2);

	stepBase *fin = new stepBase();
	fin->command = stepBase::shoot;
	fin->stepNum = 3;
	//storage->push_back(fin);

	stepBase *sb3 = new stepBase();
	sb3->command = stepBase::stop;
	sb3->stepNum = 4;
	storage->push_back(sb3);
}

void CommandListMaker::makeDefenceBreaker() {

	if (storage != NULL) {
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();

#if 0
	/* Gets the current selction from the dashboard (should default to LowBar)*/
	//Selection
	void* temp = autoPosition->GetSelected();
	std::string* dt = static_cast<std::string*>(temp);
	std::string defence = *dt;

	temp = autoDefence->GetSelected();
	dt = static_cast<std::string*>(temp);
	std::string position = *dt;

	delete dt;
#endif

	//Defaults to low bar
	std::string defence = low;

	if (stick->GetRawButton(7)) {
		defence = low;
	} else if (stick->GetRawButton(8)) {
		defence = rock;
	} else if (stick->GetRawButton(9)) {
		defence = deb;
	} else if (stick->GetRawButton(10)) {
		defence = moat;
	} else if (stick->GetRawButton(11)) {
		defence = ram;
	}

	//Bool determining if Shooting is possible on the current defence
	bool CanShoot = false;

	//Step Number Needs to be tracked
	int GlobalStep = 0;

	//Fist Drive Step Distance and Speed
	double DriveDistance;
	double DriveSpeed;

	//The Step We Are Going to Pass
	driveStep* drive = new driveStep();

	//Which Defence we are going over determines the speed and distance they will go
	//But ignores the type and number
	if (defence.compare(deb) == 0)	//DEBRIS
			{
		DriveDistance = 28;
		DriveSpeed = .75;
	} else if (defence.compare(ram)) //RAMPARTS
			{
		DriveDistance = 28;
		DriveSpeed = .75;
	} else if (defence.compare(rock)) //ROCK WALL
			{
		DriveDistance = 28;
		DriveSpeed = .75;
	} else if (defence.compare(low)) // LOW BAR
			{
		DriveDistance = 28;
		DriveSpeed = .75;
	} else if (defence.compare(moat) == 0) // Moat
			{
		DriveDistance = 28;
		DriveSpeed = .75;
	} else //THE OTHERS
	{

		DriveDistance = 0.5;
		DriveSpeed = 0.5;
		CanShoot = false;
	}

	//Seting the Values and Pushing the Command
	drive->stepNum = GlobalStep;
	GlobalStep++;
	drive->command = stepBase::driveStraight;
	drive->distance = DriveDistance;
	drive->speed = DriveSpeed;
	storage->push_back(drive);

	stepBase* stop = new stepBase();
	stop->stepNum = GlobalStep;
	GlobalStep++;
	stop->command = stepBase::stop;
	storage->push_back(stop);

#if 0
	//Turn Decision based on position
	if (CanShoot && TURNIF_NOSHOT) {
		//Eventual TurnStep
		turnStep *turn = new turnStep();

		//The Position it is in gotten through 'rough' means
		int pos = 1;

		//Turn angle and
		double TurnAngle;
		double TurnSpeed; //TODO Remove from IControl this is't used

		//Switch Controller;
		switch (pos) {
		case 1:
			TurnAngle = 39.09;
			TurnSpeed = .6;
			break;
		case 2:
			TurnAngle = 27.11;
			TurnSpeed = .6;
			break;
		case 3:
			TurnAngle = 11.95;
			TurnSpeed = .6;
			break;
		case 4:
			TurnAngle = -5.06;
			TurnSpeed = .6;
			break;
		case 5:
			TurnAngle = -21.25;
			TurnSpeed = .6;
			break;
		default:
			TurnAngle = 0;
			TurnSpeed = .6;
			break;
		}

		//Sets and Push the Actual Step
		turn->stepNum = GlobalStep;
		GlobalStep++;
		turn->command = stepBase::turn;
		turn->angle = TurnAngle;
		turn->speed = TurnSpeed;
		storage->push_back(turn);
	}

	if (CanShoot) {
		stepBase* prepareShot = new stepBase();
		prepareShot->stepNum = GlobalStep;
		GlobalStep++;
		prepareShot->command = stepBase::target;
		storage->push_back(prepareShot);

		stepBase* shoot = new stepBase();
		shoot->stepNum = GlobalStep;
		GlobalStep++;
		shoot->command = stepBase::shoot;
		storage->push_back(shoot);

		stepBase* stop = new stepBase();
		stop->stepNum = GlobalStep;
		GlobalStep++;
		stop->command = stepBase::stop;
		storage->push_back(stop);
	}
#endif
}

void CommandListMaker::makeTest(){

	int x = 0;

	if(storage != NULL){
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();

	driveStep* ds = new driveStep();
	ds->speed = 1.0;
	ds->distance = 5;
	ds->stepNum = x; x++;
	ds->command = stepBase::driveStraight;
	storage->push_back(ds);

	driveStep* ds2 = new driveStep();
	ds2->speed = 1.0;
	ds2->distance = 5;
	ds2->stepNum = x; x++;
	ds2->command = stepBase::driveStraight;
	storage->push_back(ds2);

	stepBase* stp = new stepBase();
	stp->command = stepBase::stop;
	stp->stepNum = x; x++;
	storage->push_back(stp);

}

void CommandListMaker::makeTest2(){
	if(storage != NULL){
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();
	int x = 0;

	turnStep* tn = new turnStep();
	tn->angle = 90;
	tn->speed = .5;
	tn->stepNum = x; x++;
	tn->command = stepBase::turn;
	storage->push_back(tn);

	stepBase* stp = new stepBase();
	stp->command = stepBase::stop;
	stp->stepNum = x; x++;
	storage->push_back(stp);
}

void CommandListMaker::makeTest3(){

	if(storage != NULL){
		delete storage;
		storage = NULL;
	}
	storage = new std::vector<stepBase*>();
	int x = 0;

	stepBase* tar = new stepBase();
	tar->command = stepBase::target;
	tar->stepNum = x; x++;
	storage->push_back(tar);

	stepBase* sht = new stepBase();
	sht->command = stepBase::shoot;
	sht->stepNum = x; x++;
	storage->push_back(sht);

	stepBase* stp = new stepBase();
	stp->command = stepBase::stop;
	stp->stepNum = x; x++;
	storage->push_back(stp);
}

vector<stepBase*>* CommandListMaker::getList() {
	return storage;
}
