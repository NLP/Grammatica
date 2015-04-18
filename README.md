
Join our online chat at [![Gitter](https://badges.gitter.im/NLP/gitter.svg)](https://gitter.im/nlp)

TODO:
-Create Syntax Tree Class: Probably just a regular tree
-Create Parser Class: Given a Grammar Structure and an Input, it will create all of 
the possible trees (or paths) allowed by the Grammar Structure and will match it with the Input Sequence.
It will then reduce the set of trees by checking if it correctly matches the structure of the input.
It will then hold a small subset of the original set (Hopefully only 1 tree remains)
-Fix Graph Crash Problem

DONE:
-Created Grammar Class
-Created the Context Free Grammar
 * Sentence -> Noun Phrase + Verb Phrase
 * Noun Phrase -> Pronoun
 * Noun Phrase -> Proper Noun
 * Noun Phrase -> Determiner + Nominal
 * Nominal -> Noun + Nominal
 * Nominal -> Noun
 * Verb Phrase -> Verb
 * Verb Phrase -> Verb + Noun Phrase
 * Verb Phrase -> Verb + Noun Phrase + Preposition Phrase
 * Verb Phrase -> Verb + Preposition Phrase
 * Preposition Phrase -> Preposition + Noun Phrase
