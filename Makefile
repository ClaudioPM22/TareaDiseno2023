all:
	g++ -std=c++17 pDinamica2.cpp -o pd
	g++ -std=c++17 fuerzaBruta.cpp -o fb

clean:
	rm main
	rm fb
