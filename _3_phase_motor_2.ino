//http://elabz.com/brushless-dc-motor-with-arduino/

int dT = 25;
int counter = 0;

#define DHT11_PIN 4      //PORT C analog pin 3

byte dht11_dat[5];

byte read_dht11_dat()
{
 	byte i = 0;
	byte result=0;
	for(i=0; i< 8; i++){
		
		while(!(PIND & _BV(DHT11_PIN)));  // wait for 50us
		delayMicroseconds(30);
		
		if(PIND & _BV(DHT11_PIN)) 
			result |=(1<<(7-i));
              while((PIND & _BV(DHT11_PIN)));  // wait '1' finish
         
	}
	return result;
}


void setup(){
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);//this PIN is for the DHT11

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  
   pinMode(17, OUTPUT);//this PIN repaces the 4

	DDRD |= _BV(DHT11_PIN);
	PORTD |= _BV(DHT11_PIN);

	  Serial.begin(9600);
  
Serial.println("Ready");
 readTempHum();
 delay(500);

}

void loop(){
   readTempHum();
  counter = 0;
  doRotationLeft();
  delay(100);
     readTempHum();
  counter = 0;
  doRotationRight();
  delay(100);
}

void readTempHum(){
  
	byte dht11_in;
	byte i;
	// start condition
	// 1. pull-down i/o pin from 18ms
	PORTD &= ~_BV(DHT11_PIN);
	delay(18);
	PORTD |= _BV(DHT11_PIN);
	delayMicroseconds(40);
	
	DDRD &= ~_BV(DHT11_PIN);
	delayMicroseconds(40);
	
	dht11_in = PIND & _BV(DHT11_PIN);
	
	if(dht11_in){
		Serial.println("dht11 start condition 1 not met");
		return;
	}
	delayMicroseconds(80);
	
	dht11_in = PIND & _BV(DHT11_PIN);
	
	if(!dht11_in){
		Serial.println("dht11 start condition 2 not met");
                delay(1000);
		return;
	}
	delayMicroseconds(80);
	// now ready for data reception
	for (i=0; i<5; i++)
		dht11_dat[i] = read_dht11_dat();
		
	DDRD |= _BV(DHT11_PIN);
	PORTD |= _BV(DHT11_PIN);
	
        byte dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];
	// check check_sum
	if(dht11_dat[4]!= dht11_check_sum)
	{
		Serial.println("DHT11 checksum error");
	}
	
	Serial.print("Current humdity = ");
	Serial.print(dht11_dat[0], DEC);
	Serial.print(".");
	Serial.print(dht11_dat[1], DEC);
	Serial.print("%  ");
	Serial.print("temperature = ");
	Serial.print(dht11_dat[2], DEC);
	Serial.print(".");
	Serial.print(dht11_dat[3], DEC);
	Serial.println("C  ");
	
}

void doRotationLeft(){
  while ( counter < 200){
    counter++;
    if ( counter < 10 ) dT = 25; 
    else if ( counter > 10 && counter < 30 ) dT = 22;
    else if ( counter > 30 && counter < 180 ) dT = 20;
    else if ( counter > 180 && counter < 190 ) dT = 22;
    else if ( counter > 190 ) dT = 30;
    p1();
    p2();
    p3();
    p4();
    p5();
    p6();
  }

}

void doRotationRight(){
  
 
  
  while ( counter < 200){
    counter++;
    if ( counter < 10 ) dT = 25; 
    else if ( counter > 10 && counter < 30 ) dT = 22;
    else if ( counter > 30 && counter < 180 ) dT = 20;
    else if ( counter > 180 && counter < 190 ) dT = 22;
    else if ( counter > 190 ) dT = 30;
    p6();
    p5();
    p4();
    p3();
    p2();
    p1();
  }

}

void p1(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(17, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);

  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);


  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);


  delay(dT);
}
void p2(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(17, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);


  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);


  delay(dT);
}
void p3(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(17, HIGH);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);


  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16, HIGH);


  delay(dT);
}
void p4(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(17, HIGH);

  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);


  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);


  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16, HIGH);


  delay(dT);
}
void p5(){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(17, HIGH);

  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);

  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);


  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);

  delay(dT);
}
void p6(){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(17, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);

  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);


  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);

  delay(dT);
}














