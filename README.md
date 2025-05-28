# AI-Desktop-Assistant
Arduino AI Desktop Assistant

My Arduino AI Desktop Assistant is designed to enhance  user experience through voice commands and automation. This project integrates Arduino with machine learning to create an intelligent assistant to perform various tasks.

Note: That the python code should be runed in the PyCharm Community Edition fot better and smooth results.

Features :

1. Voice Recognition: It uses our built-in laptop or Desktop Mic to listen to what we say, and gives us an answer using the API Key I used ( OpenRouter ),  and it also displays the answer, but in a short version
on the OLED Display, and also  note that I am using PyCharm Community Edition, so use that only for a better experience and to work it smoothly.

2. Real Time Weather: It shows the real-time weather of the Place where I live ( Nashik ), you can change it by changing the latitude & longitude of the place where you live. I am using Weather Stack API Key
for this project.

3. Plays Music: I just put 1 music in the Code, you can put more by changing this " ![Screenshot 2025-05-27 164609](https://github.com/user-attachments/assets/dda8d343-2d02-4760-b268-16123abac819)
 " in the python code, it is given in the Important Files > Program Files > Python code.zip ( Note: This will be a Zip file, Extract the zip file, then open Pycharm,the next instructions are given the instructions.txt file in the zip. )

4. Shows Time: It shows the time in the place I live ( Nashik ) , you can change it by changing this command in the file

   I- Find this section in the code :
   
   ![Screenshot 2025-05-27 163130](https://github.com/user-attachments/assets/1c23c3c8-913f-4557-9604-83a884fda6df)

   II- To change the location, update this line :

   ![Screenshot 2025-05-27 163139](https://github.com/user-attachments/assets/700832de-9a94-44c6-863c-13788fb94495)

🌍Here are some common time zones:

   New York > "America/New_York"
   
   London > "Europe/London"
   
   Tokyo > "Asia/Tokyo"
   
   Mumbai > "Asia/Kolkata"
   
   Berlin > "Europe/Berlin"
   
   Sydney > "Australia/Sydney"
   
*For eg: Set to London :*
  location = "Europe/London"

For the materials I used, I have given a BOM File in CSV Format, you can check it.


*Important*

The Table :

|     Item      |                                                        Purpose                                                               |     Source    |     Price     |    Shipping    | Total Price
| ------------- | ---------------------------------------------------------------------------------------------------------------------------- | ------------- | ------------- | -------------- | --------------------- |
|4 PIN Push Button           |Changing between Modes                                                                                                        |Local Store          |$0.12            |   $0       |  $0.12                     |
|SSD1306 OLED Display           |For displaying animated eyes, Time, Short Answers, & Weather                                                                                    |Local Store     |N/A            |      N/A       |                       |
|Breadboard           |For Connecting multiple things to GND and VCC                                                      |Local store     |$1.25           |      $0        |  $1.25           |
|Jumper Wires    |For circuit connections                                                       |eBhoot Electronics ( Online )     |$0.94           |      $0.5        |  $0.99                     |
|Power Bank or USB Battery|Main power unit                                                                  |Amazon         |$8.99          |      $1        |   $9.99            |
|USB Cable |To power Arduino and for uploading code                                                             |Ships with Arduino         |$14.04          |      $3       |       $17.04               |
|Govo GO Surround 300      |To listen to music and the answers to questions                                                                                |Govo.com         |$5.49          |      $0        |                       |
|Arduino Uno    | Microcontroller Board                                  |Arduino        | $4.68 |      $2.60     |      $7.28            |
