all: compile



compile:
	rm arquivo.dat indice_id.dat
	g++ main.cpp header.cpp -o a
	./a

clean:
	rm arquivo.dat indice_id.dat
