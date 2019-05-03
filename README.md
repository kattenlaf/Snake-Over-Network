# What is this?

This is showing simple multithreadedness by having a server create a thread to handle a connection
received from a client. By doing this it is possible to have multiple clients connected at the same
time. This entire project however is mocking the "twitchplayspokemon" aspect on the streaming website
known as twitch. Where users enter their commands in a chat and whenever the character on screen is ready
for another button press the last entered command is used. 

# How does it work?

To simulate that, I used a snake game, along with the client server architecture to have a server 
host, take the commands from clients also able to connect directly using telnet localhost <port_number> 
(port number in this case is 8888) and then the last command that was sent (written to the file) 
when the game is ready for an input is read from a file and used. 

# How to use it?

THE FILES WILL ALREADY BE COMPILED AND READY IN EXECUTABLE FORM.
Start up the server in a terminal window and have multiple clients ready/connected in other terminal windows
using ./server ./client OR telnet localhost 8888, 
(clients can join whenever but it is better to have them ready before the game starts because the 
snake could run into the walls and die).
Once this is met, start the snake game in a separate terminal window and have each client program enter 
commands(characters) at will which will be handled by the server threads. 
only w a s d will cause the snake to move in a certain direction.
Entering commands in either client terminal window will make the snake move.
w => up
a => left
s => right
d => down

# Limitations

# -- connections -- #
Also, I wished to have separate computers connect, which based on my code and research was not an
issue. The problem lies in how my current network may be set up. I tried to telnet into my PC from
another computer and it never worked so this is not related to my code but rather the network architecture
of perhaps my router. The system will work just the same if you could figure this out on your own to
have a class interact with the snake game for example, (i.e. one person runs the snake game and server
every other student connects via client/telnet and then just enter commands and hope altogether they
can grow the snake as long as possible)
# -- game-design -- #
A lot of cooler game design related things could have been done in terms of rendering the snake and 
such but required a lot of windows dependencies which would decrease portability. I tried my best to
find a snake game in C available for linux and tuned it to how I saw fit. As such the game will look
weird because it is actually drawing the board in the terminal "frame" at a time to simulate the 
actual refresh rate of a screen. So it may look a bit jumpy at times but smooth at other times.

# What else?
Have fun :)