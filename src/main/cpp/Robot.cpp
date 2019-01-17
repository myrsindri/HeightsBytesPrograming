/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/*
 * main robot code for the first haddon heights robotics team 2018
 *
 * written by Nicole tolarba & Nicholas kaegi
 *
 */

#include <IterativeRobot.h>
#include <Joystick.h>
#include <Spark.h>
#include <WPILib.h>

float powert = 0;
float tablet = 0;
bool auto_set = false;
bool set = false;
int i = 2;
int y = 1;
int x = 0;
double auto_x = 0;
double auto_y = 0;
double time_s = 0;
double FortyFiveL[4] = {0,-.8,.15,0};
double FortyFiveR[4] = {0,.8,.15,0};

//auto plan first number (forward or back) second number (rotation) third number (time) forth number (cube table)
//double s1v2[10][4] = { { -.6, .15, 1.8, 0}, {-.45,0,2,0 }, { 0, 0, 1, 1 }, { 0, 0, -1, 0 } };
//double s1v1[10][4] = { { -.6, .15, .6, 0 },{0,.45,.5,0},{ -.6, .15, .6, 0 },{0,-8,.15,0},{ -.6, .15, .6, 0 },{ 0, 0, 1, 1 },{ 0, 0, -1, 0 } };
//double s1v1[][4] = {{ -.6, .15, .5, 0 }, {0,-1.0,.2,0} ,{ -.6, .15, 4, 0 },{0, 1.0,.2,0}, { -.6, .15, .5, 0 }, { 0, 0, 1, 1 },{ 0, 0, -1, 0 } };
//Right
double s1v1[][4] = {{ -.6, .15, 1.8, 0}, { 0, 0, -1, 0 }};
// left side
double s2vl[][4] = {{ -.6, .15, .5, 0}, { 0, -.8, .3, 0 }, { -.6, .15, 3.5, 0}, { 0,  .8, .3, 0 }, { -.6, .15,   1, 0}, { 0, 0, -1, 1 }};
double s2vr[][4] = {{ -.6, .15, .5, 0}, { 0,  .8, .3, 0 }, { -.6, .15, 1.1, 0}, { 0, -.8, .3, 0 }, { -.6, .15, 3.5, 0}, { 0, 0, -1, 1 }};
//Left
double s1v2[][4] = {{ -.6, .15, 1.8, 0}, {-.45,0,2,0 }, { 0, 0, 1, 0 }, { 0, 0, -1, 0 } };//cube flip dissabled for now
//drive forward ten feet then stop;
double s3v1[][4] = {{ -.6, .15, 1.8, 0}, { 0, 0, -1, 0 }};

std::string version = "L";
int instr = 0;
std::string state = "r";



const double accel_max = 0.07;
const double accel_low = 0.02;
const double z_max = 0.7;
const double y_max = 1.0;
const double y_slow = 0.7;
bool MidAuto = false;

static void clamp(double &value, const double ul, const double ll)
{
    if (value < ll)
    {
        value = ll;
    }
    else if (value > ul)
    {
        value = ul;
    }
}

class Robot : public frc::IterativeRobot
{
public:
    Robot() :
    	direction(1)
    {
        m_robotDrive.SetExpiration(0.1);
        //m_timer.Start();

//		CameraServer::GetInstance()->StartAutomaticCapture();
//		CameraServer::GetInstance()->StartAutomaticCapture();
    }

    void AutonomousInit()override
    {
        printf("Duel 2.1");
        m_timer.Reset();
        m_timer.Start();

        auto_set = false;
        instr = 0;

        std::string gameData;
        gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
        //MidAuto = SmartDashboard::GetBoolean("DB/Button 2", false);
        if(MidAuto){
        	printf("mid-auto\n");

            if (gameData[0] == 'L')
            {
                //Put left auto code here
                printf("left \n");
                version = "L";

                auto_x = s2vl[instr][0];
                auto_y = s2vl[instr][1];
                time_s = s2vl[instr][2];

                if (s2vl[instr][3] == 1)
                {
                    auto_set = true;
                    m_timercube.Reset();
                }
            }
            else
            {
                //Put right auto code here

                printf("right \n");
                version = "R";

                auto_x = s2vr[instr][0];
                auto_y = s2vr[instr][1];
                time_s = s2vr[instr][2];

                if (s2vr[instr][3] == 1)
                {
                    auto_set = true;
                    m_timercube.Reset();
                }
            }
            state = "r";
#if 0
        	//your current two autos
        	//if(L) Scenario one
        	//else scenario two
            auto_x = s3v1[0][0];
            auto_y = s3v1[0][1];
            time_s = s3v1[0][2];

            auto_set = false;
            state = "r";
#endif
        }
        else if (gameData.length() > 0)
        {
            if (gameData[0] == 'L')
            {
                //Put left auto code here
                printf("left \n");
                version = "L";

                auto_x = s1v1[instr][0];
                auto_y = s1v1[instr][1];
                time_s = s1v1[instr][2];

                if (s1v1[instr][3] == 1)
                {
                    auto_set = true;

                    m_timercube.Reset();
                }
            } 
            else
            {
                //Put right auto code here

                printf("right \n");
                version = "R";

                auto_x = s1v2[instr][0];
                auto_y = s1v2[instr][1];
                time_s = s1v2[instr][2];

                if (s1v2[instr][3] == 1)
                {
                    auto_set = true;
                    m_timercube.Reset();
                }
            }
            state = "r";
        }
        else if (true)
        {
        	//your current two autos
        	//if(L) Scenario one
        	//else scenario two
            auto_x = s3v1[0][0];
            auto_y = s3v1[0][1];
            time_s = s3v1[0][2];

            auto_set = false;
            state = "r";
        }
        else
        {
            state = "s";
        }

        if (time_s < 0) state = "s";

        instr++;

        // ???
        if  ((s1v2[instr][2] == -1) || (s1v1[instr][2] == -1))
        {
            instr = 0;
        }


        printf("current command %s %f %f %f %s \n", version.c_str(), auto_x, auto_y, time_s, state.c_str());
        if (auto_set == true)
        {
            printf("table flip active");
        }

//        tablet = SmartDashboard::GetNumber("tablet", 0);
//        powert = SmartDashboard::GetNumber("powert", 0);

        tablet = 0.15;
        powert = -0.6;

        m_timer.Reset();
        m_timer.Start();

        m_timerwin.Reset();
        m_timerwin.Start();
    }

    void AutonomousPeriodic()override
    {
        float current_time = m_timer.Get();

        // check for drive status
        if  (state == "r")
        {
            if (m_timer.Get() < time_s)
            {
                m_robotDrive.ArcadeDrive(auto_x, auto_y);
            }
            //read next instruction
            else
            {
                if (MidAuto)
                {
                    if (version == "L")
                    {
						auto_x = s2vl[instr][0];
						auto_y = s2vl[instr][1];
						time_s = s2vl[instr][2];

	                    if (s2vl[instr][3] == 1)
	                    {
	                        auto_set = true;
	                        m_timercube.Reset();
	                        m_timercube.Start();
	                    }
                    }
                    else
                    {
                        auto_x = s2vr[instr][0];
                        auto_y = s2vr[instr][1];
                        time_s = s2vr[instr][2];

	                    if (s2vr[instr][3] == 1)
	                    {
	                        auto_set = true;
	                        m_timercube.Reset();
	                        m_timercube.Start();
	                    }

                    }
                }
                else if (version == "L")
                {
                    auto_x = s1v1[instr][0];
                    auto_y = s1v1[instr][1];
                    time_s = s1v1[instr][2];

                    printf("current_time = %f", current_time);

                    if (s1v1[instr][3] == 1)
                    {
                        auto_set = true;
                        m_timercube.Reset();
                        m_timercube.Start();
                    }
                }
                else if (version == "R")
                {
                    auto_x = s1v2[instr][0];
                    auto_y = s1v2[instr][1];
                    time_s = s1v2[instr][2];

                    if (s1v2[instr][3] == 1)
                    {
                        auto_set = true;
                        m_timercube.Reset();
                        m_timercube.Start();
                    }

                    printf("current_time = %f", current_time);
                }
                if (time_s < 0) state = "s";

                instr++;

                m_timer.Reset();
                m_timer.Start();

                printf("current command %s %f %f %f %s \n", version.c_str(), auto_x, auto_y, time_s, state.c_str());

                if (auto_set == true)
                {
                    printf("table flip active");
                }
            }
        }
        // Stop robot
        else
        {
            m_robotDrive.ArcadeDrive(0.0, 0.0);
        }

        if (auto_set == true)
        {
            if (m_timercube.Get() < tablet)
            {
                float cubetime = m_timercube.Get();
                printf("on going \n");
                printf("current time %f \n", cubetime);
                m_tableup.Set(powert);
            } 
            else
            {
                printf("time is up \n");

                m_tableup.Set(0.0);

                auto_set = false;

                m_timercube.Stop();
            }
        }
        // lower the intake arms
        if (m_timerwin.Get() < 15)
        {
        	winmotor.Set(1.0);
        }
        else
        {
        	winmotor.Set(0.0);
        }

    }


    void TeleopInit()override
    {
        last_y = last_z = 0.0;

        direction = 1;

        set = false;

        powert = 0.0;
    }

    void TeleopPeriodic()override
    {



        double tmp_y = last_y;
        double tmp_z = last_z;

        // drive processing
        double y = m_stick_d.GetY() * direction;
        double z = m_stick_d.GetRawAxis(4);

        // printf("1: y=%f z=%f\n", y, z);

        clamp(y, y_max, -y_max);
        clamp(z, z_max, -z_max);

//        printf("2: y=%f z=%f\n", y, z);

        double dy = y - last_y;
        double dz = z - last_z;

        clamp(dy, accel_max, -accel_max);
        clamp(dz, accel_max, -accel_max);

        last_y = last_y + dy;
        last_z = last_z + dz;

        if (tmp_y != last_y && tmp_z != last_z)
        {
            printf("3: y: %5.2f => %5.2f x: %5.2f => %5.2f\n", y, last_y, z, last_z);
        }

        m_robotDrive.ArcadeDrive(-last_y, last_z, true);


        if (m_stick_d.GetRawButtonPressed(3))
        {
            // toggle direction multiplier
            direction *= -1;
        }

        // raise/lower the intake arms
        if (m_stick_d.GetRawButton(5))
        {
        	winmotor.Set(1.0);
        }
        else if (m_stick_d.GetRawButton(6) || m_stick_o.GetRawButton(6))
		{
			winmotor.Set(-1.0);
		}
		else
        {
        	winmotor.Set(0.0);
        }


        if (m_stick_o.GetRawButton(1))
        {
            m_inleft.Set(.5);
            m_inright.Set(-.3);

//          printf("in\n");
        } 
        else if (m_stick_o.GetRawButton(2))
        {
            m_inleft.Set(.3);
            m_inright.Set(.2);

//          printf("rotate\n");
        }
        else if (m_stick_o.GetRawButton(3))
        {
            m_inleft.Set(-.3);
            m_inright.Set(-.2);

//          printf("rotate\n");
        } 
        else if (m_stick_o.GetRawButton(4))
        {
            m_inleft.Set(-.8);
            m_inright.Set(.8);

//          printf("out\n");
        } 
        else
        {
            m_inleft.Set(0);
            m_inright.Set(0);

            //printf("stop\n");
        }


        if (true ==  m_stick_o.GetRawButtonPressed(5))
        {
            set = true;

            tablet = 0.15;
            powert = -0.6;

            m_timercube.Reset();
            m_timercube.Start();
        }
        else if (true ==  m_stick_o.GetRawButtonReleased(5))
        {
            set = true;

            tablet = 0.15;
            powert = 0.3;

            m_timercube.Reset();
            m_timercube.Start();
        }

        if (set == true)
        {
            if (m_timercube.Get() > tablet)
            {
                printf("time is up=%f \n", m_timercube.Get());

                powert = 0.0;

                set = false;

                m_timercube.Stop();
            }
        }

//        printf("%5.2f: powert=%f", m_timercube.Get(), powert);

        m_tableup.Set(powert);
    }

    void TestPeriodic()override { }

private:
    // Robot drive system
    frc::Spark m_left{0};
    frc::Spark m_right{1};
    frc::DifferentialDrive m_robotDrive{m_left, m_right};

    frc::Joystick m_stick_d{0};
    frc::Joystick m_stick_o{1};

    frc::Timer m_timer;
    frc::Timer m_timercube;
    frc::Timer m_timerwin;


    frc::Spark m_inleft{2};
    frc::Spark m_inright{3};

    frc::Spark m_tableup{5};

	frc::Spark winmotor{6};

    double last_z {0};
    double last_y {0};
    int direction;
};

START_ROBOT_CLASS(Robot)
