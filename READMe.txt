David Parker
CSCI 191T Midterm

I did not have to add any additional classes, I simply extended GLScene.cpp. I did have to change
Model, however, as each model did not have a unique textureLoader object tied to them so each Model
would always have the most recent loaded texture.

The gun and cursor both are kept at constant places in the screen, so not much happens with them.
The "bullet" is initially kept far off screen, and constantly zooms from 0.0 to -40.0, when the mouse button
is clicked, the zoom is set to 0.0 and position is set equal to the cursor position, then it zooms to -40.0
and disappears (goes off screen again). Also, if the bullet is on screen you cannot shoot another bullet.

The falling parachute men are an array of 5 Models that fall at a randomized rate, they are each kept at different
X positions. To track them with the skyBox, I changed the model mouseMove function in Inputs to translate them
and played with the amounts to get them to track well with the skyBox rotation. After they fall too far (just off
screen), the Y position is changed to reappear above the screen. The "bullet" also translates with the skyBox so
it is not always in the cursor when moving it after shooting.

To detect collision, I check two things: the "bullet" is within a certain X and Y distance from a parachute man, 
and also that the "bullet" is zoomed passed -28.0. This forces the conditions where the bullet has to both travel towards
and also go through a parachute man. Upon collision, the hit parachute man is reset to the top position.

Here is a video of it being played: https://youtu.be/yD4LEcC6zC4