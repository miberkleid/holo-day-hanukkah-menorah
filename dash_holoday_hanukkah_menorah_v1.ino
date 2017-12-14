// Maiky Iberkleid Dec 2017
// Holo-day Hanukah Menorah V1.0
// Mandatory shout-out to Pranav Gokhale and Franky Romero

//Dash Pins
int zero = D15; 
int one = D30; 
int two = D28; 
int three = D29; 
int four = D26; 
int five = D07; 
int six = D06; 
int seven = D05; 
int eight = D02; 

//Variables 
int whileCounter = 5; 
int messageSuccess = 0; 
int pointer = 0; 
int sms_queue = 0; 

//this array is used to simplify the order on the animations 
int lights[] = {one, two, three, four, zero, five, six, seven, eight};  


void setup() { 
 //set pins to output 
 pinMode(zero, OUTPUT); 
 pinMode(one, OUTPUT); 
 pinMode(two, OUTPUT); 
 pinMode(three, OUTPUT); 
 pinMode(four, OUTPUT); 
 pinMode(five, OUTPUT); 
 pinMode(six, OUTPUT); 
 pinMode(seven, OUTPUT); 
 pinMode(eight, OUTPUT);
 
// initialize Serial communication for debugging 
 Serial.begin(9600); 
 Serial.println("Starting"); 

//test sequence 
test_sequence(); 

//send a starting messge to the Hologram cloud 
 HologramCloud.sendMessage("Starting", "Holiday"); 

 //attach the SMS Handler Funciton 
 HologramCloud.attachHandlerSMS(cloud_sms); 
} 


void loop() { 
//print loop to let us know we are running in serial 
 Serial.println("loop"); 
   delay(3000); 
} 

//On received SMS, print the sender, timestamp and message 
//Message the cloud that an SMS was received with the sender number 
//as the content and the tag SMSRX
//Thanks Hologram!
 
void cloud_sms(const String &sender, const rtc_datetime_t &timestamp, const String &message) { 
 Serial.println("CLOUD SMS RECEIVED:"); 
 Serial.print("SMS SENDER: "); 
 Serial.println(sender); 
 Serial.print("SMS TIMESTAMP: "); 
 Serial.println(timestamp); 
 Serial.println("SMS TEXT: "); 
 Serial.println(message); 
 String message2 = message; 
 message2.toLowerCase(); 

 if (message2 == "one" || message2 == "1") { 
   Serial.println("ehad"); 
   night_one(); 
 } 
 else if (message2 == "two" || message2 == "2") { 
   Serial.println("shtaim"); 
   night_two(); 
 } 
 else if (message2 == "three" || message2 == "3") { 
   Serial.println("shalosh"); 
   night_three(); 
 } 
 else if (message2 == "four" || message2 == "4") { 
   Serial.println("arba"); 
   night_four(); 
 } 
 else if (message2 == "five" || message2 == "5") { 
   Serial.println("hamesh"); 
   night_five(); 
 } 
 else if (message2 == "six" || message2 == "6") { 
   Serial.println("shesh"); 
   night_six(); 
 } 
 else if (message2 == "seven" || message2 == "7") { 
   Serial.println("sheva"); 
   night_seven(); 
 } 
 else if (message2 == "eight" || message2 == "8") { 
   Serial.println("shmona"); 
   night_eight(); 
 } 
 else if (message2 == "zero" || message2 == "0") { 
   Serial.println("0"); 
   night_zero(); 
 } 
 else if (message2 == "off") { 
   Serial.println("off"); 
   all_off(); 
 } 
 else if (message2 == "marquee") { 
   Serial.println("Marquee"); 
   all_off(); 
   marquee(); 
 } 
   else if (message2 == "random") { 
   Serial.println("Random"); 
   all_off(); 
   Random(); 
 } 
     else if (message2 == "ladder") { 
   Serial.println("Ladder"); 
   all_off(); 
   Ladder(); 
 } 
    else if (message2 == "plz help") { 
   HologramCloud.sendMessage("0-8, Off, Marquee, Random, Ladder", "Help"); 
   Serial.println("0-8"); 
   Serial.println("Off"); 
   Serial.println("Marquee"); 
   Serial.println("Random"); 
   Serial.println("Ladder"); 
 } 
 else { 
   Serial.println("Invalid Input"); 
 } 

 if (HologramCloud.sendMessage(message, "SMSRX")) { 
   Serial.println("SMS received message sent to cloud."); 
 } else { 
   Serial.println("Notification send failed."); 
 } 
} 


void all_off() { 
 digitalWrite(zero, LOW); 
 digitalWrite(one, LOW); 
 digitalWrite(two, LOW); 
 digitalWrite(three, LOW); 
 digitalWrite(four, LOW); 
 digitalWrite(five, LOW); 
 digitalWrite(six, LOW); 
 digitalWrite(seven, LOW); 
 digitalWrite(eight, LOW); 
} 

void all_on() { 
 digitalWrite(zero, HIGH); 
 digitalWrite(one, HIGH); 
 digitalWrite(two, HIGH); 
 digitalWrite(three, HIGH); 
 digitalWrite(four, HIGH); 
 digitalWrite(five, HIGH); 
 digitalWrite(six, HIGH); 
 digitalWrite(seven, HIGH); 
 digitalWrite(eight, HIGH); 
} 

void night_zero() { 
 all_off(); 
 digitalWrite(zero, HIGH); 
} 

void night_one() { 
 night_zero(); 
 delay(300); 
 digitalWrite(one, HIGH); 
} 

void night_two() { 
 night_one(); 
 delay(300); 
 digitalWrite(two, HIGH); 
} 

void night_three() { 
 night_two(); 
 delay(300); 
 digitalWrite(three, HIGH); 
} 

void night_four() { 
 night_three(); 
 delay(300); 
 digitalWrite(four, HIGH); 
} 

void night_five() { 
 night_four(); 
 delay(300); 
 digitalWrite(five, HIGH); 
} 

void night_six() { 
 night_five(); 
 delay(300); 
 digitalWrite(six, HIGH); 
}
 
void night_seven() { 
 night_six(); 
 delay(300); 
 digitalWrite(seven, HIGH); 
}
 
void night_eight() { 
 night_seven(); 
 delay(300); 
 digitalWrite(eight, HIGH); 
} 

void marquee() { 
 sms_queue = 0; 
 Serial.println(sms_queue); 
 while (sms_queue == 0) { 
   Serial.println(sms_queue); 
   while (pointer != 8) { 
     sms_queue = HologramCloud.checkSMS(); 
     digitalWrite(lights[pointer], HIGH); 
     delay(300); 
     digitalWrite(lights[pointer], LOW); 
     pointer++; 
   } 
   while (pointer != 0) { 
     sms_queue = HologramCloud.checkSMS(); 
     digitalWrite(lights[pointer], HIGH); 
     delay(300); 
     digitalWrite(lights[pointer], LOW); 
     pointer--; 
   } 
 } 
} 

void Random() { 
 sms_queue = 0; 
 Serial.println(sms_queue); 
 while(sms_queue == 0){ 
   Serial.println(sms_queue); 
   sms_queue = HologramCloud.checkSMS(); 
   pointer = random(0,9); 
   digitalWrite(lights[pointer], HIGH); 
     delay(300); 
     digitalWrite(lights[pointer], LOW); 
   } 
} 

void Ladder() { 
 sms_queue = 0; 
 while (sms_queue == 0) { 
   pointer = 0; 
   while (pointer <= 8) { 
     sms_queue = HologramCloud.checkSMS(); 
     digitalWrite(lights[pointer], HIGH); 
     delay(300); 
     pointer++; 
   } 
   pointer = 8; 
   while (pointer >= 0 ) { 
     sms_queue = HologramCloud.checkSMS(); 
     digitalWrite(lights[pointer], LOW); 
     delay(300); 
     pointer--; 
   } 
 } 
} 

void test_sequence(){ 
 all_on(); 
 delay(200); 
 all_off(); 
 delay(500); 
 all_on(); 
 delay(200); 
 all_off(); 
 delay(200); 
 night_one(); 
 delay(200); 
 night_two(); 
 delay(200); 
 night_three(); 
 delay(200); 
 night_four(); 
 delay(200); 
 night_five(); 
 delay(200); 
 night_six(); 
 delay(200); 
 night_seven(); 
 delay(200); 
 night_eight(); 
} 
