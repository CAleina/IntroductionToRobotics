# Introduction To Robotics (2022-2023)

Repository for homeworks in the laboratory for Introduction To Robotics. 
Created in 3rd year of Faculty of Mathematics and Computer Science, University of Bucharest, by Cosali Aleina, group 343.
Below are details about homeworks such as requirements, implementation details, code and image files.

# Homework 1

  Requirements:
1. Hardware: RBG  LED  (1  minimum),  potentiometers  (3  minimum), resistors and wires (per logic).
2. Code: Use a separate potentiometer in controlling each of the colors of the RGB LED (Red, Green and Blue). The control must be done with digital electronics.

  Pictures:
  
![RGB1](https://user-images.githubusercontent.com/62470536/197416807-4a800053-9f1e-46af-a24d-885fa89930fd.jpg)![RGB2](https://user-images.githubusercontent.com/62470536/197416810-9c384495-800a-42d5-9f68-7837fab4086b.jpg)        ![RGB3](https://user-images.githubusercontent.com/62470536/197416830-c65df0a2-1875-4a9b-a670-417d5c909346.jpg)

  Video of functionality:  https://youtu.be/gUk2o1IBo4g
  
  Code for this homework is found in Homework1.ino.

# Homework 2 

  Requirements:
1. Hardware: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
2. Code: 
  State 1(default, reinstated after state 4 ends): green light for cars, red light for people,  no sounds. Duration: indefinite, changed by pressing the button.
  
  State 2(initiated by counting down 8 seconds after a button press): the light should be yellow  for cars, red for people and no sounds. Duration: 3 seconds.
  
  State 3(initiated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.
  
  State 4(initiated after state 3 ends): red for cars, blinking greenfor people and a beeping sound from the buzzer, at a constant in-terval, faster than the beeping in state 3. Duration: 4 seconds.
  
  Pressing the button in any other state than State 1 should not have any actions.
  
  Pictures:
  
  ![befunky_2022-10-3_1-51-34](https://user-images.githubusercontent.com/62470536/199363300-04b53375-de91-41c8-99b1-2704c2f2f6bb.jpg)   ![befunky_2022-10-3_1-51-48](https://user-images.githubusercontent.com/62470536/199363319-35ce3792-a937-4f6b-b503-dba9b5a4aa9b.jpg)

  Video of functionality: https://youtu.be/L5DsG5n-7Qg
  
  Code for this homework can be found in Homework2.ino.
  
  # Homework 3
  
  Requirements:
1. Hardware:  1  7-segment  display,  1  joystick,  resistors  and  wires  (perlogic)
2. Code: 
  State  1 (default,  but  also  initiated  after  a  button  press  in  State2):  Current  position  blinking. Can use the joystick to move from one position to  neighbors. Short pressing the button toggles state 2. Long pressing the button in state 1 resets the entire display byturning all the segments OFF and moving the current position to thedecimal point.
  State  2 (initiated  after  a  button  press  in  State  1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back tostate 1.
  Long pressing the button to reset should only be available in State 1.
  
  Pictures:
  
  ![WhatsApp Image 2022-11-09 at 23 51 39](https://user-images.githubusercontent.com/62470536/200949870-dfa4901e-15da-452e-8b23-ddd81bda899c.jpg)   ![WhatsApp Image 2022-11-09 at 23 51 38](https://user-images.githubusercontent.com/62470536/200949888-b227de74-3229-4a07-a8a1-d5247caf3215.jpg)

  Video of functionality: https://youtu.be/H0Sy8HvQvYk
  
  Code for this homework can be found in Homeowork3.ino.
  
  # Homework 4
  
  Requirements:
  1. Hardware: a joystick, a 4 digit 7-segment display, a 74hc595 shift register
  2. Code:
    State 1: You can use a joystick axis to cycle through the 4 digits; Using the other axis does nothing. A blinking decimal point shows the current digit position.  When pressing the button, you lock in onthe selected digit and enter the second state.
    State 2: In this state, the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the  4  digits. Instead, using  the other  axis,  you  can increment or decrement the number on the current digit IN HEX. Pressing the button again returns you to the previous state. Also, keep in mind that when changing the number, you must increment it for each joystick movement - it should  notwork continuosly increment if you keep the joystick in one position.
    Reset:  Toggled by long pressing the button only in the first state. When resetting, all the digits go back to 0 and the current position is set to the first digit, in the first state.
    
   Pictures:
    
![WhatsApp Image 2022-11-16 at 16 22 46](https://user-images.githubusercontent.com/62470536/202209009-eb5fa8f7-c995-4538-8f01-473bf980bb6b.jpg) ![WhatsApp Image 2022-11-16 at 16 22 46 (1)](https://user-images.githubusercontent.com/62470536/202209064-600387ad-3d34-4edf-ad32-b4c891203262.jpg)

   Video of functionality: https://youtu.be/eduu_dPamiM
    
   Code for homework can be found in Homework4.ino.
  
  
