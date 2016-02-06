#include "targetGiver.h"
#include "Profile/IProfile.h"
#include "Profile/SProfile.h"
#include "Drive/Drive.h"


class Robot: public IterativeRobot {
public:

	IControl::profile CompareID(std::string id) {

		IControl::profile ret;

		if (id.compare("Tim") == 0) {
			ret = IControl::profile::Tim;
		}

		else if (id.compare("Hoen") == 0) {
			ret = IControl::profile::Hoen;
		}

		else if (id.compare("Monty20")==0) {
			ret = IControl::Monty20;
		}

		else if (id.compare("Proto")==0) {
			ret = IControl::Proto;
		}

		else if (id.compare("bot2016")==0) {
			ret = IControl::bot2016;
		} else {
			ret = IControl::nothing;
		}
		return ret;
	}

	noList* master;
	IControl::profile id;
	IProfile *profile;

	Robot() {
		master = new noList();
		profile = new SProfile();

		id = CompareID(SmartDashboard::GetString("Identity", ""));
		//EX ADDNODE
		//master->addNode(new IControl, "NAME");
		master->addNode(new Drive(profile), "drive");

	}

private:
	LiveWindow *lw;

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		SmartDashboard::PutString("State", "Robot Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->RobotInit(IControl::profile(id));
			test = test->parent;
		}

	}

	void AutonomousInit() {
		SmartDashboard::PutString("State", "Autonomous Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->AutonomousInit();
			test = test->parent;
		}
	}

	void AutonomousPeriodic() {
		SmartDashboard::PutString("State", "Autonomous Periodic");
		//No list here beacause auto was always a bit more complicated
	}

	void TeleopInit() {
		SmartDashboard::PutString("State", "Teleop Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TeleopInit();
			test = test->parent;
		}
	}

	void TeleopPeriodic() {
		SmartDashboard::PutString("State", "Teleop Periodic");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TeleopPeriodic();
			test = test->parent;
		}
	}

	void TestInit() {
		SmartDashboard::PutString("State", "Test Init");
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TestInit();
			test = test->parent;
		}
	}

	void TestPeriodic() {
		SmartDashboard::PutString("State", "Test Periodic");
		lw->Run();
		nLNode* test = master->head;
		while (test != NULL) {
			test->value->TestPeriodic();
			test = test->parent;
		}
	}
};

START_ROBOT_CLASS(Robot);
