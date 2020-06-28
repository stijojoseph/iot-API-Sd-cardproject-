//## STIJO JOSEPH PROJECT ASSIGNMENT

#include <HTTPClient.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include &lt;SPI.h&gt;
#include &lt;SD.h&gt;

#include <DateTime.h>

#include <DateTimeStrings.h>


#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message

 
const char* ssid = "yourNetworkName";
const char* password =  "yourPassword";

int getPCtime() //to get the current time from pc
{
 // if time available from serial port, sync the DateTime library
 while(Serial.available() >=  TIME_MSG_LEN ){  // time message
   if( Serial.read() == TIME_HEADER ) {       
     time_t pctime = 0;
     for(int i=0; i < TIME_MSG_LEN -1; i++){   
       char c= Serial.read();         
       if( c >= '0' && c <= '9')   
         pctime = (10 * pctime) + (c - '0') ; // convert digits to a number           
     }   
     DateTime.sync(pctime);   // Sync DateTime clock to the time received on the serial port
   } 
 }
return pctime;
}

 
void setup() 
{
 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");

  

if (!SD.begin(5)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
 


 if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("http://demo4657392.mockable.io/list-tag-ids"); // URL whcih was given for the assignment
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);// all the datas got copied to the string httpCode
        Serial.println(payload);
         myFile = SD.open("test.txt", FILE_WRITE);
         if (myFile) {
         Serial.print("Writing to test.txt...");
         myFile.println(httpCode);// writing the data from string to the sd card file "test.txt"
        
      }
 
    else 
    {
      Serial.println("Error on HTTP request");//if api wasnt able to connect this time successfully
      

      myFile = SD.open("test.txt");//taking the previously stored file 
    
    
    
    }
}
 
void loop() {
 
int time1; 
int p;
int t=0;
time1=getPCtime() ;
if (myFile) {
    Serial.println("test.txt:");
    int t=0;// to check which line is currently reading incrementation in eachloop
    while (myFile.available()) //checking wheather test.txt is available
     {
      
      t++;
      ch=myFile.read();//read the first line in test.txt and copy to ch as string
      int l = ch.length();//reads the length of the first line
      int k=0; 
      int i = 0;
      if t==1;
      i=11;//for getting the data after student_id in the first line
   
      for (; i < l; i++) 
       {ch = str.at(i); //copyting character
         if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')||(ch >= '0' && ch <= '9'))// checking wheather its alphabet or digit
            {
             if( (k==3 )&& (ch >= '0' && ch <= '9'));//if a number comes after three symbols then it will be the API id so storing it to variable p
             {p=ch;//storing API ID
              k=0;
             }
            }
           else if( k==5);//if a number or alphabet comes after 5 symbols then its API key, storing the ap key  to an array
          {  c.append(ch);
             int m=0;
             if(c.length()==18)// every api key is 18 letters 
              {k=0;
       
               for(int s=0;s<18;s++)
                { 
                  if (c.at(s)==p.at(s))//comparing the user given KEY to the API key in the file
                 {
                  m++;
                  }

                  if(m==18)
                  {
                   Serial.print("the key is",p); //if each letter of the API key matches with that of the user entered ..displaying API ID
                  }
                }        
             }
        }
        else
         k++;

       }

     }

}
int time2=getPCtime() ;
int timeq=time1=time2;
Serial.println("time for query=")
Serial.println(time*1000,"ms")


   
myFile.close();
http.end(); //Free the resources
  
 
delay(10000);
 
}
