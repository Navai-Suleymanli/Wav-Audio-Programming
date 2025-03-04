# Wav-Audio-Programming
This code was written with the help of the tutorial: https://www.youtube.com/watch?v=rHqkeLxAsTc&t=1338s by Ferrabacus.
 It was just a practice for building audio fundamentals that I will need for my future security-related project.

 **WAV File Generator in C++**

**Overview**

This is a simple C++ program that generates a .wav audio file containing a sine wave. The generated wave has a frequency of 250 Hz and a duration of 2 seconds. It creates a stereo (2-channel) WAV file with a sample rate of 44.1 kHz and 16-bit depth.

**Features**

Generates a valid WAV file from scratch

Uses PCM format (Pulse Code Modulation)

Stereo sound: left and right channels have different amplitudes

Simple and minimalistic C++ implementation

**How It Works**

Writes WAV file headers following the RIFF format.

Generates a sine wave with the specified frequency.

Writes the audio data to the file.

Updates the file size fields after writing the audio data.

**Dependencies**

C++ Standard Library (iostream, fstream, string, cmath)

No external dependencies required

**Running the Program**

Once compiled, the program will generate test.wav in the same directory. You can play it using any media player that supports WAV format.

![image](https://github.com/user-attachments/assets/4d3cf200-b620-42a4-bbbf-d7f3bcd7f595)
This image is obtained by visualizing the resulting test.wav file using Audacity

 

