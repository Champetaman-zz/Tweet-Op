# PROYECTO #2 - Makefile Mini-Twitter
# 
#   Camilo Oviedo
#   Oscar Moreno


all: Tweet

hello: Gestor.o Cliente.o
    g++ Gestor.o Cliente.o -o tweet

Gestor.o: Gestor.cpp
    g++ -c Gestor.cpp

Cliente.o: Cliente.cpp
    g++ -c Cliente.cpp


clean:
    rm *o Tweet