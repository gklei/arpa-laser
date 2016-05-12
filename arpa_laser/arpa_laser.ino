#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper _stepper(STEPS, 8, 9, 10, 11);

/*-----( Declare Variables )-----*/

int STEP_DISTANCE = 1;
int TOTAL_NOTES = 8;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  _stepper.setSpeed(200); 
} /*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  // Turn Laser on
  // Read Photoresistor Value
  // Do note stuff
  // Turn laser off
  // Step

   for (int i = 0; i < TOTAL_NOTES; ++i)
   {
      _stepper.step(1);
      delay(1); 
   }
   for (int i = TOTAL_NOTES; i > 0 ; --i)
   {
      _stepper.step(-1);
      delay(1);
   }
} /* --(end main loop )-- */
