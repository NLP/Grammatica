
Join our online chat at [![Gitter](https://badges.gitter.im/NLP/gitter.svg)](https://gitter.im/nlp)

# TODO:
```
-Add a new Def S-> IP NP NP to allow sentences like Is he a person?
-Add cases for this new type of question in Subj, DO, and IDO

-Find a general way to calculate the subject, verb, object of the syntax tree and sentence

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
#Key Objects to Make
```
-Event: It will describe an action
  -Has an action (the verb)
  -Actors: (The subject)
  -Props: (Direct Objects)
  -Receiver: (indirect Objects)
  -Location: (Prepositional)
-A Special Type of Event: Existence, Definition, Description
  -Existence uses the word is/are/were/will be/to be as its action
    -Denotes the existence of a subject
    -Has: Actors (The subject)
    -Location: (Where the Actors are)
  -Definition denotes the what the subject is (He is a person. That is a cat)
    -Has: Actors (The definee)
    -Definition: (The Direct Object)
  -Description denotes characteristics of the subject (He is funny.)
    -Has Actors
    -Has Characteristics (The adjectives acting as direct objects)
-Actors, Props, Receivers, Location will have Features:
  -Features include their location, time, etc.
  -It also includes any description or adjective
-Action will have features as well:
  -Includes adverbs
  
-Wh Identifiers (Who, What, When, Where, Why, How, Which)
  -These denote WHAT the program should look for when asked a question
  -The subject, verb, and possible objects and prep of the question will tell the program which event/feature to
  search for
    -But the Wh word will tell it what to extract from the database
    -These are found in interrogatives
-Functors for Commands (Common Words are: Define, Show, Explain, Describe, Find, Calculate, etc.)
  -There is no general way to implement ALL of these so the common ones just have to be hard coded in
  -These, like the wh Identifiers, tell the program what to do when given a command
  -The subject and any other modifier will tell it specifically what to do the command with
  -These are only found in imperatives
-Possible commands:
  -Show: Picture of DO or IDO (in the case of Show me an apple vs Show an apple)
  -Define: Write definition of DO or IDO (same case as above)
  -Explain: The Why or How .. Might not be possible at the moment
  -Describe: Get the adjectives of the DO or IDO or the adverbs of the V
  -Find: ??
  -Calculate: Calculates the given expression 
```
# Rules for calculating objects and the head words
```
Head Words:
-Noun Phrase: Noun
-Verb Phrase: Verb
-Adj Phrase: Adj
-Adv Phrase: Adv
-Prep Phrase: Prep
-Sentence: Verb

Objects:
Declarative Sentences:
-The subject almost always comes before the main verb and is a noun/noun phrase
-The main verb will almost always be the head verb of the sentence
-The direct object will almost always be the noun/noun phrase that follows the main verb
-The indirect object will be the noun that follows the direct object BUT not in the Prep Phrase
-The Prep Object will be the noun in the prep phrase
Special Case for Infinitives, Present Progressives, 
-These can act like subjects and direct objects
-Infinitive Phrases include to walk in the park->I like to walk in the park
-Present Progressive Phrases include walking in the park->I like walking in the park
Interrogative Sentences (Questions):
-The subject and main verb swap places most of the time
-There is usually a Wh-Identifier that begins the sentence (except in Y/N questions)
-The Wh is usually the first phrase
-The main verb is still the head verb of the sentence
-But the subject is now the first noun phrase AFTER the main verb (except in some cases of Who?)
-The rules for DO, IDO, PO are the same, except:
-Depending on the Wh term, one of the is replaced with it (Where replaces the Loc., Who/What replaces the subj,
DO, or IDO, etc.) So some of the objects might be blank in these cases, and that is what we try to find when we search
Imperative Sentences (Commands):
-There is no subject (it is an implied you)
-The main verb is the head verb of the sentence and is almost always first
-The DO is the noun that follows the main verb, and the IDO follows the DO
-The PO is in the prep phrase
```
# DONE:
```
-Created Grammar Class
-Created the Context Free Grammar
-Updated Grammar Class so that it flows better
-Changed Grammar to Map (Should work perfectly)
-Moved enums and structs to a single file or to their own files
-Created Syntax Tree
-Created Parser
-Added Question Grammar Structure

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
