all: compile



compile:
	g++ binConverter.cpp -o a
	./a

clean:
	rm arquivo
	g++ binConverter.cpp -o a
	./a
