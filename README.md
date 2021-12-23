# TinyParser

## Introduction

A parser is a compiler/interpreter component which is responsible for producing parser tree or abstract syntax tree.
In this repo, my goal is to write a Tiny Parser using a predictive top-down parsing technique — recursive descent technique.

### Grammar rules in EBNF

- program -> stmt-seq
- stmt-seq -> stmt{;stmt}
- stmt -> if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
- if-stmt -> if exp then stmt-seq [else stmt-seq] end
- repeat-stmt -> repeat stmt-seq until exp
- assign-stmt -> identifier := exp
- read-stmt -> read identifier
- write-stmt -> write exp
- exp -> simple-exp [comparison-op simple-exp]
- comparison-op -> < | =
- simple-exp -> term {addop term}
- addop -> + | -
- term -> factor {mulop factor}
- mulop -> \* | /
- factor -> (exp) | number | identifier

### Notes

- statement has neighbors and child nodes which could be statements
- expressions are depicted as oval and statements are depicted as rectangle
- max number of children for a statement is 3 children -- for an if statement
- max number of children for an expression is 2
- 
