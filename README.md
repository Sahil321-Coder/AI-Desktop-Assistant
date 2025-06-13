# AI-Desktop-Assistant
Arduino AI Desktop Assistant

#Total Cost needed for this Project is:
```bash
$88.19
```

My Arduino AI Desktop Assistant is designed to enhance  user experience through voice commands and automation. This project integrates Arduino with machine learning to create an intelligent assistant to perform various tasks.

Note: The Python code should be run in the PyCharm Community Edition for better and smoother results.

What my Project is:

So Basically my project is a collection of micrcontrollers and more electronics components thta make a AI DESKTOP ASSISTANT, this idea is mainly focused for Working People who don't have time for opening their mobile seeing hte climate, time and also to find answers to their questions, so for that i have inventes this AI DESKTOP ASSISTANT for them, beacuse it will just listen to their commands and answer it by voice and also it will be also taking care of you privacy because it will only listen to everything when we say the wake word "Hi Buddy!". This bot also focuses on kids who need help with their homework, etc, and it will talk to everyone like a friendly assistant. It is not compatible with Alexa and Google Home, but it does have some basic features, such as telling time and answering basic questions like "What is ESP32?"
Features :

1. Voice Recognition: It uses our built-in laptop or Desktop Mic to listen to what we say, and gives us an answer using the API Key I used ( OpenRouter ),  and it also displays the answer, but in a short version
on the OLED Display, and also  note that I am using PyCharm Community Edition, so use that only for a better experience and to work it smoothly.

2. Time Changing: It also tells time according to your time zone in your area by the API key.
3. Plays Music: I just put 1 music in the Code, you can put more by changing this "![Screenshot 2025-05-28 124243](https://github.com/user-attachments/assets/844e735f-96ab-49e1-b308-fabf7dba2476) and this also

(If you want to change this (the second pic))

![Screenshot 2025-05-28 124256](https://github.com/user-attachments/assets/c1dc43ce-7dea-4e5a-ae08-e7d6df614b02)

 " in the python code, it is given in the Important Files > Program Files > Python code ( Note: This will be a folder, open the folder, and take all the files you want, use PyCharm for better performance and smooth work, if you are using different environment(I don't know it will work or not).

For the materials I used, I have given a BOM File in CSV Format, you can check it.

Also I have given the BOM File in Table format Below.


*Important*
Pictures:
These are the pictures of the 3D Model I was making in FreeCAD 1.0.1 & Blender.

![photo-collage png](https://github.com/user-attachments/assets/c36c5b24-277b-4fdd-8ff3-3f915d87a6b8)



This is the picture for Wirirng Diagram I Created in Wokwi:

![Screenshot 2025-06-11 114641](https://github.com/user-attachments/assets/42f1a500-7593-459d-8736-54705fc85e00)

If you want to see it in Wokwi, go to this link below:
Note: I have just made the wiring Diagram not written the code there.

```bash
https://wokwi.com/projects/433443551673204737
```



The Table :

|     Item      |                                                        Purpose                                                               |     Source    |     Price     |    Shipping    | Total Price
| ------------- | ---------------------------------------------------------------------------------------------------------------------------- | ------------- | ------------- | -------------- | --------------------- |
|SSD1306 OLED Display           |For displaying animated eyes, Time, Short Answers, & Weather                                                                                    |EBhoot     |$1.56           |      $0.25       |  $1.78                     |
|50 CM Micro USB Cable |To power Arduino and for uploading code                                                             |EBhoot         |$0.28          |      $0       |       $0.28              |
|ESP32 DevKit1 Board    | Microcontroller Board                                  |EBhoot        | $3.14 |   $0    |      $3.14       |
|Rasberry Pi SD Card    | Storage                                 |Robu.in       | $4.10 |   $0    |      $4.10        |   
|Raspberry Pi 4  B ( 4 GB )  | Offline Controller                                |RoboticsDNA        | $55.2 |   $1    |      $56.2         | 
|Microphone For Raspberry Pi  | Microphone                                 |SilverLine Electronics        | $3.48 |   $0    |      $3.48         |
|Speaker  | To hear the input                                 |N/A        | $5 |   $0    |      $5         |
|Breadboard  | Alternative to Soldering                                 |RoboSAP        | $0.81 |   $0    |      $0.81         |
|Push Button  | switching between modes                                 |EBhoot        | $0.012 |   $0    |      $0.012         |
|Jumper Wires  | Connections                                 |EBhoot        | $1.22 |   $0.0    |      $1.22         |



This is how your Project Folder should look like -
```bash
project/
│
├── voice_assistant.py
├── song1.mp3
└── vosk-model-small-en-us-0.15/  <- unzip model here
```


To run the code Run this in your IDE's Terminal or Command Prompt.

```bash
python3 voice_assistant.py
```
