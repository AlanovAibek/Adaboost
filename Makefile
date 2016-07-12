CC := g++
CFLAGS := -c -Wall
LDFLAGS :=
SOURCES := main.cpp modelevaluation.cpp adaboost.cpp data.cpp feature.cpp image.cpp pixel.cpp sample.cpp randomgenerator.cpp strongclassifier.cpp weakclassifier.cpp
OBJDIR := source
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES))
TARGET=Boosting-Sex-Identification-Performance

all: $(TARGET)
    																																																																																																									
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf *.o

