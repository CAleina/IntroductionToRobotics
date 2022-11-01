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
  
  
