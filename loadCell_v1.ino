#include <Joystick.h>
#include <HX711.h>

Joystick_ Joystick;


// Pin de datos y de reloj
byte pinData = 6;
byte pinClk = 5;

HX711 bascula;

int factor_calibracion = -120500; //Este valor del factor de calibración funciona para mi. El tuyo probablemente será diferente.

void setup() {

  Joystick.begin();
  // Iniciar sensor
  bascula.begin(pinData, pinClk);

}

int potenciometer =10000 ;

void loop() {

   int _potenciometer = analogRead(A0);

   if( (_potenciometer * 0.95) < potenciometer || (_potenciometer * 1.05) < potenciometer ){
    potenciometer = _potenciometer;
    calibrate(potenciometer);
   }
  
    Joystick.setThrottle((int) (bascula.get_units() ));
    Joystick.setBrake((int) (bascula.get_units() ));
    //Joystick.setAccelerator((int) (bascula.get_units() ));
    Joystick.setRzAxis(1023);
    //delay(10);

}

void calibrate( int factor ){
  int _factor = map(factor, 0, 1023, -122000, -100000);
  bascula.set_scale(_factor);
  bascula.tare();
  long zero_factor = bascula.read_average();
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW);
}

