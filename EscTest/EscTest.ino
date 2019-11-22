// Need the Servo library
#include <Servo.h>

#define NUMMOTORS 4
typedef struct MotorDef
{
    Servo   Motor; 
    int     Pin;   // Indicates the Pin this motor is connected to
};

MotorDef Motors[NUMMOTORS];

// Stores the settings for all ESC. This can be made specific to each ESC, but that's not needed
// for a quadcopter project
typedef struct ESCSettingsDef
{
  int Low;
  int High;
};

ESCSettingsDef ESCSettings; 

#define NORMAL_MODE

int CurrentSpeed;
int Step = 5;


#define ESC_HIGH_DEFAULT 200
#define ESC_LOW_DEFAULT 40

void setup()
{
  
	// Required for I/O from Serial monitor
	Serial.begin(9600);
	Serial.println("Setup: Serial port communication at 9600bps");
	// Attach motors to pins
	
        Motors[0].Pin =  11;
	Motors[1].Pin =  10;
	Motors[2].Pin =  9;
	Motors[3].Pin =  8;

        for(int i = 0; i < NUMMOTORS; i++)
        {
          int pin = Motors[i].Pin;
          Motors[i].Motor.attach(pin);
        }

	// Set the ESC settings to the defaults
	ESCSettings.Low   = ESC_LOW_DEFAULT;
	ESCSettings.High  = ESC_HIGH_DEFAULT;
}

// Increase the speed of the motor from low to high as set by the user
void Run()
{
  // Send a low signal initially for normal mode
        for (int i = 0; i < NUMMOTORS; i++)
	{
	  Motors[i].Motor.write(ESCSettings.Low);
	}
	Serial.println("Running ESC");
	Serial.println("Step = ");
	Serial.print(Step);
	Serial.println("\nPress 'u' to increase speed, 'd' to reduce speed");

	CurrentSpeed = ESCSettings.Low;
	while (1) {
		while (!Serial.available())
		{
		}
		char currentChar = Serial.read();
		if (currentChar == 'u')
		{
			Serial.println("\nIncreasing motor speed by step");
			if (CurrentSpeed + Step < ESCSettings.High) {
				CurrentSpeed = CurrentSpeed + Step;
				Serial.println("New speed = ");
				Serial.print(CurrentSpeed);
			}

			else
			{
				Serial.println("\nMax speed reached\n");
			}
		}
		if (currentChar == 'd')
		{
			Serial.println("\nDecreasing motor speed by step\n");
			if (CurrentSpeed - Step >= ESCSettings.Low)
			{
				CurrentSpeed = CurrentSpeed - Step;
				Serial.println("New speed = ");
				Serial.print(CurrentSpeed);
			}

			else
			{
				Serial.println("\nMin speed reached\n");
			}
		}
		if (currentChar == 'e')
		{
			Serial.println("\nStopping Motors\n");
			CurrentSpeed = ESCSettings.Low;
		}
		for (int i = 0; i < NUMMOTORS; i++)
		{
		  Motors[i].Motor.write(CurrentSpeed);
		}
	}
}

void loop()
{
#ifdef NORMAL_MODE
	Run();
#endif
  while(1) { } 
}
