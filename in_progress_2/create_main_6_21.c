// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library.h"

#define BOOSTER_COLOR 0

void initialize_create();
void turn_to_pole();
void drive_to_booster(int distance, int direction);
void grab_booster_main(int distance);
void drop_booster_main(int distance, int booster);
void get_birdie();
void set_servos_for_getting_birdie();

int main()
{
	//_SKIP_PRESS_A_TO_CONTINUE = TRUE;
	
	initialize_create();
	
	set_servos_for_getting_birdie();
	press_A_to_continue();
	
	get_birdie();
	press_A_to_continue();
	
	turn_to_pole();
	
	drive_to_booster(47, BACKWARDS);
	grab_booster_main(5);
	drop_booster_main(23, 1);
	
	drive_to_booster(22, FORWARDS);
	grab_booster_main(3);
	drop_booster_main(25, 2);
	
	drive_to_booster(12, FORWARDS);
	grab_booster_main(3);
	drop_booster_main(15, 3);
	
	drive_to_booster(2, FORWARDS);
	grab_booster_main(3);
	
	return 0;
}

void initialize_create()
{
	printf("Program starts OK\n");										// Initializing procceses
	printf("Trying to connect to the Create.\n");
	create_connect();
	printf("Connected!\n");
	create_full();
	camera_open(LOW_RES);
	printf("Have you adjusted the joint servo yet????\n");
	press_A_to_continue();
	start_servos();
	press_A_to_continue();
}

void turn_to_pole()
{
	relax_servos();														// Turns the servos off to drive
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);									// Spins towards the pole
	press_A_to_continue();
}

void drive_to_booster(int distance, int direction)
{
	relax_servos();
	create_drive_distance(distance, 20, direction);						// Drives towards the pole, stopping at the booster
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);									// Turns towards the booster
	press_A_to_continue();
	
	unrelax_servos();
	move_so_blob_is_at(BOOSTER_COLOR, (116 + 144) / 2, 5, 100, BOOSTER_X, LEFT_RIGHT, 20); // was 159
	press_A_to_continue();
	move_so_blob_is_at(BOOSTER_COLOR, 51, 5, 100, BOOSTER_Y, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	
	move_so_blob_is_at(BOOSTER_COLOR, (116 + 144) / 2, 2, 100, BOOSTER_X, LEFT_RIGHT, 20);
	press_A_to_continue();
	move_so_blob_is_at(BOOSTER_COLOR, 51, 1, 100, BOOSTER_Y, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	/*move_so_blob_is_at_x(0, 91, 5, 0);									// Spins to the x of the booster
	press_A_to_continue();
	move_so_blob_is_at_y(0, 30, 1, 0, 0);								// Moves to the y of the booster
	press_A_to_continue();
	move_so_blob_is_at_x(0, 91, 2, 0);									// Fixes any inaccuracies in the previous x fix
	press_A_to_continue();
	move_so_blob_is_at_y(0, 30, 1, 0, 0);								// Fixes any inaccuracies caused by the second move to x
	press_A_to_continue();*/
}

void grab_booster_main(int distance)
{													
	//open_gate(600);														// Opens the gate so the arm can come down
	grab_booster(distance);												// Grabs the booster
	press_A_to_continue();
	lift_booster();														// Lifts the booster to drive
	press_A_to_continue();	
}

void drop_booster_main(int distance, int booster)
{
	create_spin_degrees(87, 87, LEFT);									// Spins towards the pole to drop the booster
	press_A_to_continue();
	
	if (booster == 1)
	{
		create_drive_distance(15, 20, BACKWARDS);						// Drives forward so the camera can see the pole
		press_A_to_continue();
	}
	move_so_blob_is_at(BOOSTER_COLOR, 64, 2, 100, CENTER_X, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	
	if (booster == 1 || booster == 2)
	{
		move_so_blob_is_at(BOOSTER_COLOR, 102, 2, 100, CENTER_Y, BACKWARDS_FORWARDS, 40);
		press_A_to_continue();
	}	
	
	create_drive_distance(distance, 3, BACKWARDS);						// Drives against the wall of the poles to correct itsef and drop the booster
	press_A_to_continue();
	drop_booster(DROP_BOOSTER);											// Drops the booster
}

void get_birdie() {
	// Back up until hits front bump sensor.
	create_drive(20, FORWARDS);
	while (TRUE)
	{
		if (get_create_lbump(0.05) == 1 || get_create_rbump(0.05) == 1)
		{
			break;
		}
	}
	create_stop();
	press_A_to_continue();
	
	// Go forward 19 cm.
	create_drive_distance(19, 20, FORWARDS);
	press_A_to_continue();
	
	// Turn right 90 degrees.
	create_spin_degrees(87, 87, RIGHT);
	press_A_to_continue();
	
	// Go backwards 30 cm.
	create_drive_distance(30, 20, BACKWARDS);
	press_A_to_continue();
}

void set_servos_for_getting_birdie() {
	set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
	set_servo_position(CAMERA_SERVO, CAMERA_TRAVEL_POSITION);
}

void spin_left_for_camera_search(int speed) { create_spin_CCW(speed); } // was 20
void spin_right_for_camera_search(int speed) { create_spin_CW(speed); }
void move_backwards_for_camera_search(int speed) { create_drive_straight(-speed); }  // was -40
void move_forwards_for_camera_search(int speed) { create_drive_straight(speed); } // was 40
void stop_camera_search() { create_stop(); }
