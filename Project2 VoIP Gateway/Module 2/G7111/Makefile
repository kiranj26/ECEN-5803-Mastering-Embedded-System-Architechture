CC=gcc
CFLAGS=-Wall -Werror
TARGET=g711_Decoder

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET) pcm_decoded_output_of_mulaw.wav
