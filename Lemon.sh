#!/bin/bash
lemon ./src/Grammar/grammar.y
flex ./src/Grammar/lexer.l
mv ./src/Grammar/grammar.c ./src/Grammar/grammar.cpp
mv ./lex.yy.c ./src/Grammar/lex.yy.c
mv ./src/Grammar/grammar.h ./include/Grammar/grammar.h
