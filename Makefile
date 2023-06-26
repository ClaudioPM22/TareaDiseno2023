all:
	g++ -std=c++17 pDinamica2.cpp -o pd
	g++ -std=c++17 fuerzaBruta.cpp -o fb
	g++ -std=c++17 v3.cpp -o v3

clean:
	rm main
	rm fb
	rm v3
