/*
% ------------------------------------------------------------------
% Title: G.711 μ-law Audio Decoder
% Brief: This file contains the implementation of a G.711 μ-law audio decoder.
%        It reads a μ-law encoded WAV file, decodes it to linear PCM format,
%        and writes the PCM data to a new WAV file.
% Author: Kiran Jojare & Viraj Patel
% Course: ECEN 5803  Mastering Embedded System Architecture
% Project: Project 2 - Module 2
% Date: Nov 8 2023
%
% References:
% - G.711 μ-law and A-law implementations in C:
%   https://opensource.apple.com/source/tcl/tcl-20/tcl_ext/snack/snack/generic/g711.c
% - G.711 Wikipedia Article:
%   https://en.wikipedia.org/wiki/G.711
% - WAV file format tutorial:
%   http://www.topherlee.com/software/pcm-tut-wavformat.html
% ------------------------------------------------------------------
*/

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define constants used for μ-law encoding and decoding
#define SIGN_BIT    (0x80)    // Sign bit for a A-law byte, used for encoding.
#define QUANT_MASK  (0xf)     // Mask to extract the quantization bits.
#define SEG_SHIFT   (4)       // Number of bits to left shift for segment number.
#define BIAS        (0x84)    // Bias for linear code.
#define SEG_MASK    (0x70)    // Mask to extract the segment number.
#define CLIP        32635     // Clipping value for the magnitude of the signal.

// Function to convert a μ-law value to 16-bit linear PCM
short Snack_Mulaw2Lin(unsigned char u_val) {
    short t;
    u_val = ~u_val;  // Complement the μ-law value to get the original signal value.
    t = ((u_val & QUANT_MASK) << 3) + BIAS;  // Extract and scale the quantization bits.
    t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;  // Shift the value based on the segment.
    return ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));  // Return the final PCM value.
}

// Define a standard header for the μ-law WAV format
uint8_t header[] = {
    // The 'RIFF' chunk descriptor
    'R', 'I', 'F', 'F', // ChunkID
    0x00, 0x00, 0x00, 0x00, // ChunkSize (placeholder, will be updated later)
    'W', 'A', 'V', 'E',     // Format
    // The 'fmt ' sub-chunk (format information)
    'f', 'm', 't', ' ',     // Subchunk1ID
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size (16 for PCM)
    0x01, 0x00,             // AudioFormat (PCM)
    0x01, 0x00,             // NumChannels (1 channel)
    0x40, 0x1f, 0x00, 0x00, // SampleRate (8000 Hz)
    0x80, 0x3e, 0x00, 0x00, // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
    0x02, 0x00,             // BlockAlign (NumChannels * BitsPerSample/8)
    0x10, 0x00,             // BitsPerSample (16 bits)
    // The 'data' sub-chunk (actual sound data)
    'd', 'a', 't', 'a',     // Subchunk2ID
    0x00, 0x00, 0x00, 0x00  // Subchunk2Size (placeholder, will be updated later)
};

int main() {
    // Specify the path to the input and output files
    const char* inputFilePath = "Au8A_eng_f2.wav";
    const char* outputFilePath = "pcm_decoded_output_of_mulaw.wav";

    // Attempt to open the input file for reading
    FILE *inputFilePointer = fopen(inputFilePath, "rb");
    if (inputFilePointer == NULL) {
        fprintf(stderr, "Could not open input file %s\n", inputFilePath);
        return 1;
    }

    // Attempt to open the output file for writing
    FILE *outputFilePointer = fopen(outputFilePath, "wb+");
    if (outputFilePointer == NULL) {
        fprintf(stderr, "Could not open output file %s\n", outputFilePath);
        fclose(inputFilePointer);
        return 1;
    }

    // Write the placeholder header to the output file
    fwrite(header, sizeof(header), 1, outputFilePointer);

    // Prepare to read and decode the μ-law data
    uint8_t buffer;
    uint16_t output;
    size_t dataChunkSize = 0;

    // Skip the header of the input file as it's not needed for decoding
    fseek(inputFilePointer, 44, SEEK_SET);

    // Decode each μ-law byte and write the output as PCM data
    while (fread(&buffer, sizeof(buffer), 1, inputFilePointer) == 1) {
        output = Snack_Mulaw2Lin(buffer);
        fwrite(&output, sizeof(output), 1, outputFilePointer);
        dataChunkSize += sizeof(output);
    }

    // Update the sizes in the header with actual data size
    uint32_t riffChunkSize = dataChunkSize + 36; // Calculate RIFF chunk size
    fseek(outputFilePointer, 4, SEEK_SET); // Move to the RIFF chunk size position
    fwrite(&riffChunkSize, sizeof(riffChunkSize), 1, outputFilePointer);

    // Move to the 'data' subchunk size position and write it
    fseek(outputFilePointer, 40, SEEK_SET);
    fwrite(&dataChunkSize, sizeof(dataChunkSize), 1, outputFilePointer);

    // Close the input and output files
    fclose(inputFilePointer);
    fclose(outputFilePointer);

    // Indicate successful decoding
    printf("Decoding complete.\n");

    return 0;
}
