CPP = g++
OPTS =  -lglut -lGL

all: 
	$(CPP) main.cpp -o main $(OPTS)

clean:
	rm main