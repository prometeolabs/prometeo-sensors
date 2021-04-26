#include <prometeo_sensors.h>

AtlasScientificDO doSensor;

bool error = false;
unsigned long sampleRate = 1000;     // 5 second dust sample rate
unsigned long sampleTime;           // variable to monitor time of each sample start

float doValue;


void setup()
{
    doSensor.begin();
    Serial.begin(9600);

    error = doSensor.isConnected();
    if (error == true)
    {
        Serial.println("error - atlas scientific DO sensor connection error");
    }else
    {
        Serial.println("info - atlas scientific DO sensor connection success");
    }
}


void loop()
{
    if (millis() >= (sampleRate + sampleTime))
    {
        if (doSensor.isConnected() == true)
        {
            doValue = doSensor.readDissolvedOxygen();
            Serial.print("info - dissolved oxygen: ");
            Serial.println(doValue);
        }

        sampleTime = millis();      //resets timer before printing output
    }
}



/*

char command[20];           //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte received_from_computer = 0; //we need to know how many characters have been received.
byte serial_event = 0;           //a flag to signal when data has been received from the pc/mac/other.
byte code = 0;                   //used to hold the I2C response code.
char do_data[20];                //we make a 20 byte character array to hold incoming data from the D.O. circuit.
byte in_char = 0;                //used as a 1 byte buffer to store inbound bytes from the D.O. Circuit.
byte i = 0;                      //counter used for DO_data array.
int time_ = 575;                 //used to change the delay needed depending on the command sent to the EZO Class DO Circuit.

char *DO;                        //char pointer used in string parsing.
char *sat;                       //char pointer used in string parsing.

float DO_float;                  //float var used to hold the float value of the D.O.
float sat_float;                 //float var used to hold the float value of the percent saturation.



void setup()//hardware initialization.
{
    Serial.begin(9600);            //enable serial port.
    Wire.begin();                  //enable I2C port.
}


void loop() {                                                                     //the main loop.
    if (serial_event == true) {                                                      //if a command was sent to the EZO device.
        command[0] = 'r';                                                                    //0x72  reset i, we will need it later
        time_ = 575;             //if a command has been sent to calibrate or take a reading we wait 575ms so that the circuit has time to take the reading.

        Wire.beginTransmission(address);                                        //call the circuit by its ID number.
        Wire.write(command);                                               //transmit the command that was sent through the serial port.
        Wire.endTransmission();                                                 //end the I2C data transmission.

        delay(time_);                                                         //wait the correct amount of time for the circuit to complete its instruction.

        Wire.requestFrom(address, 20, 1);                                     //call the circuit and request 20 bytes (this is more than we need)
        code = Wire.read();                                                   //the first byte is the response code, we read this separately.

        switch (code) {                           //switch case based on what the response code is.
            case 1:                                 //decimal 1.
                Serial.println("Success");            //means the command was successful.
                break;                                //exits the switch case.

            case 2:                                 //decimal 2.
                Serial.println("Failed");             //means the command has failed.
                break;                                //exits the switch case.

            case 254:                               //decimal 254.
                Serial.println("Pending");            //means the command has not yet been finished calculating.
                break;                                //exits the switch case.

            case 255:                               //decimal 255.
                Serial.println("No Data");            //means there is no further data to send.
                break;                                //exits the switch case.
        }

        while (Wire.available()) {                 //are there bytes to receive.
            in_char = Wire.read();                   //receive a byte.
            do_data[i] = in_char;                    //load this byte into our array.
            i += 1;                                  //incur the counter for the array element.
            if (in_char == 0) {                      //if we see that we have been sent a null command.
                i = 0;                                 //reset the counter i to 0.
                break;                                 //exit the while loop.
            }
        }

        Serial.println(do_data);                  //print the data.
        Serial.println();                         //this just makes the output easier to read by adding an extra blank line


        //if (command[0] == 'r') string_pars(); //uncomment this function if you would like to break up the comma separated string into its individual parts.
    }

}


void string_pars() {                  //this function will break up the CSV string into its 2 individual parts. DO|SAT|
    //this is done using the C command “strtok”.

    DO = strtok(do_data, ",");          //let's pars the string at each comma.
    sat = strtok(NULL, ",");            //let's pars the string at each comma.

    Serial.print("DO:");                //we now print each value we parsed separately.
    Serial.println(DO);                 //this is the D.O. value.

    Serial.print("SAT:");               //we now print each value we parsed separately.
    Serial.println(sat);                //this is the percent saturation.
    Serial.println();                   //this just makes the output easier to read by adding an extra blank line

    //uncomment this section if you want to take the values and convert them into floating point number.
/*  
    DO_float=atof(DO);
    sat_float=atof(sat);
*/
}
*/