# WARNINGS - nizej ma dodatkowe flagi
# DEBUG - do debagowania za pomoca gdb
WARNINGS = -Wall -W -Wextra -Wshadow 
# -Wno-switch -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter -Wno-char-subscripts
#DEBUG = -g
OTHERS = -O2 -std=c++11

# katalog do ktorego beda umieszczane pliki obiektowe
ODIR = .obj

TARGET = SpVec

CXX = g++

CFLAGS = $(WARNINGS) $(DEBUG) $(OTHERS)

# dyrektywa wildcard zwroci oddzielone spacja wszystkie nazwy ktore pasuja do patternu "*.cpp"
SOURCES = $(wildcard *.cpp)
# dla kazdego el. SOURCES konczacego sie na .cpp stworz tutaj taki sam .o, ktory trzyma nazwy plikow obiektowych
_OBJS = $(SOURCES:.cpp=.o)
# patsubst dla kazdego el. $(_OBJS), to co zgadza sie z patternem % zmieni to na $(ODIR)/%, czyli w tym przypadku dopisze sciezke katalogu
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(TARGET)
	@

$(TARGET): $(ODIR) $(OBJS) clean
	$(CXX) -o $(TARGET) $(CFLAGS) $(OBJS)

$(ODIR):
	mkdir $(ODIR)

$(ODIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)

super_clean: clean
	rm -f $(TARGET) $(ODIR)/*.o
