# Adjustable Monostable Multi-Vibrator

This is a simple program to make an arduino act as a dual adjustable monostable multivibrator also known as a One-Shot. It detects a rising edge and outputs a pulse for an adjustable amount of time regardless of the input.It leverages hardware timers to achieve accurate and repeatable timing, out performing the CPU's ability to keep time.

## Features

- Two independent monostable multivibrators
- Adjustable pulse width
- Adjustable trigger edge
- Timing accuracy within +-1 microsecond

## Usage

Program the `highTime` to set the pulse width in microseconds. Note that the highTime units are in microseconds.

The void loop of the program is empty. The arduino could run other code while the monostable multivibrators are running. This is likely to significantly reduce the accuracy of the timing.

The code is also limited by the size of the timers. The maximum on time is 255 timer clocks. This can be as small as 255/16MHz = 16 microseconds. This can be increased by increasing the prescaler of the timer. This will reduce the accuracy of the timing as a single clock takes up more time. There is no maximum off time.
