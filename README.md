# the_midi_masterpiece
A bunch of stuff related to the Adafruit Neotrellis M4. Buttons.h contains classes for using the buttons in different ways. Accel.h helps to interface with the onboard accelerometer.

## Buttons
For all the buttons, turning on sends a CC message with value 127, turning off sends a CC message with value 0.

### Latch
A single button that changes state once per press.

Arguments of begin():

- Adafruit_NeoTrellisM4 *x: Neotrellis object

- long int on_color: Color to be shown while button is in on state

- long int off_color: Color to be shown while button is in off state

- byte location: Which physical button on the neotrellis this is

- byte message: CC message corresponding to button

- bool start_state: Should the button start in on or off state

### Toggle
A single button who's state is on as long as it is pressed and turns off when released.

Arguments of begin():

- Adafruit_NeoTrellisM4 *x: Neotrellis object

- long int on_color: Color to be shown while button is in on state

- long int off_color: Color to be shown while button is in off state

- byte location: Which physical button on the neotrellis this is

- byte message: CC message corresponding to button


### Knob
TODO: explain this (implementation will probibly still change)


### MultiCC
Use various buttons to send a CC message where the value corresponds to the pressed button.

Arguments of begin():

- Adafruit_NeoTrellisM4 *x: Neotrellis object

- long int *colors: Array of colors for all the buttons

- byte *locations: Array of locations of all the buttons

- byte message: CC message

- byte *presets: Array of values of all the buttons

- byte len: How many buttons there are

### Binary
Multiple buttons encoding a binary value.

Arguments of begin():

- Adafruit_NeoTrellisM4 *x: Neotrellis object

- long int *colors: Array of colors for all the buttons

- byte *locations: Array of locations of all the buttons (TODO: check if order is MSB to LSB or vice versa)

- byte len: How many buttons there are

## Accel
TODO: explain this

## Examples

### basicSynth
Basic midi synth. The 8X4 grid is split into a 5X4 and a 3X4 section. Color of pressed keys change over time.

### crazyPitches
Controller for this pedalboard running on a mod duo https://pedalboards.moddevices.com//pedalboards/5d87a9bb2564d46f5ae27d19

### gameOfLife
Conway's gae of life. TODO: make this also do something musical

### pedalBoard
Controller for this pedalboard running on a mod duo https://pedalboards.moddevices.com//pedalboards/5d87a86d2564d46f59dbecef

### sequencer1
Step sequencer. It cycles through 8 steps and each step can play 12 notes

