all: compile



compile:
	g++ main.cpp header.cpp -o a
	./a

clean:
	rm arquivo.dat indice_id.dat indice_anoRank.dat
