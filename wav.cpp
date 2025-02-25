#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Riff Chunk
const string chunk_id = "RIFF";
const string chunk_size = "----"; // 4 dashes because in standart it says there is need for 4 bytes. each character is 1 byte. we will replace later very easily 
const string format = "WAVE";

// FMT sub-chunk
const string subchunk1_id = "fmt "; // put a space bcs it will look for 4 bytes
const int subchunk1_size = 16; // 16 for PCM.
const int audio_format = 1; // for pcm, 4 bytes for now, has to be 2
const int num_channels = 2; // monoyox stereo
const int sample_rate = 44100; // samples per second hz. common standart
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_align = num_channels * (subchunk1_size / 8); // he number of bytes for one sample including all channels
const int bits_per_sample = 16;

// Data sub-chunk
const string subchunk2_id = "data";
const string sub2chunk2_size = "----"; // bcs we dont know the actual size yet

const int duration = 2;
const int max_amplitude = 32760;
const double frequency = 250;


// helper method to get the number of bytes correctly. for audio_format size. it has to be 2 bytes, bu we cant repsresent number as 2 bytes
void write_as_bytes(ofstream& file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}


int main()
{
    ofstream wav;
    wav.open("test.wav", ios::binary);

    if (wav.is_open()) {
        wav << chunk_id;
        wav << chunk_size;
        wav << format;


        wav << subchunk1_id;
        write_as_bytes(wav, subchunk1_size, 4);
        write_as_bytes(wav, audio_format, 2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align, 2);
        write_as_bytes(wav, bits_per_sample, 2);

        wav << subchunk2_id;
        wav << sub2chunk2_size;

        // where I am at
        int start_audio = wav.tellp();
        
        for (int i = 0; i < sample_rate * duration; i++) {
            // obey the max amplitude and operate as a wave, just oscilate on the same hegiht, the same sound
            double amplitude = (double)i / sample_rate * max_amplitude;
            double value = sin((2 * 3.14 * i * frequency) / sample_rate);

            // first takes higher, second makes smaller number
            double channel1 = amplitude * value / 2;
            double channel2 = (max_amplitude - amplitude) * value;
            // basically eft ear-low to high, right ear-highto low
            
            write_as_bytes(wav, channel1, 2);
            write_as_bytes(wav, channel2, 2);
        }

        // where I ended, how many  passed
        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4 );// goes to the location on the file
        write_as_bytes(wav, end_audio - start_audio, 4);

        wav.seekp(4, ios::beg);
        write_as_bytes(wav, end_audio - 8, 4);
    }
    wav.close();
}
