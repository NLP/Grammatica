
Join our online chat at [![Gitter](https://badges.gitter.im/NLP/gitter.svg)](https://gitter.im/nlp)

# TODO:
```
-Move enums and structs to a single file or to their own files
-Find a general way to calculate the subject, verb, object of the syntax tree and sentence
-Add cases for multiple nouns in noun phrase, verbs in verb phrase, etc.
-Change heaad word of Prep Phrase to the Prep
-Test the Syntax Tree
-Install qtSQL
-Integrate the Word enums and structs with Grammar enums and structs
-Create Parser Class: Given a Grammar Structure and an Input, it will create all of 
the possible trees (or paths) allowed by the Grammar Structure and will match it with the Input Sequence.
It will then reduce the set of trees by checking if it correctly matches the structure of the input.
It will then hold a small subset of the original set (Hopefully only 1 tree remains)
-The Paser will also identify the head verbs/nouns of each phrase and mark them on the syntax tree with Idenfitifers
(This will be used to meaning representations and feature matrices)
-Event Storage for actor, action, prop, supporting actor, location, time
-Each actor, prop will also have location and time

-Add new Rules for Wh-Questions
-Find a way to generate the head words and objects of questions
-Create enums for Wh-words and phrases
-Create a way to store and lookup meaning representations and events
-Find a way to identify what the questions is asking for and where to look

-Add new Rules for Commands
-Create functors for Key Commands like Find, Define, Show, Explain, etc...

-Add Rules for Adjective Phrases
-The actor/prop/etc.. will be their own structs and will have features that hold the adjectives
-These can be used to identify particular adjectives (Who is funny?)
or to describe a noun (Describe the ball).

-Add Rules for Adverb Phrases
-The action will have their own structs with features holding the adverbs
-This caan be used to identify how someone did something (How did he kick the ball).
```
# DONE:
```
-Created Grammar Class
-Created the Context Free Grammar
-Updated Grammar Class so that it flows better
-Changed Grammar to Map (Should work perfectly)
```
# Parsing Methods
```
http://www.nltk.org/book/ch08.html
```
### Recursive Descent Parsing
### Shift-Reduce Parsing
### Left-Corner Parsing
# Context Free Grammar of Order Zero
```
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
```
