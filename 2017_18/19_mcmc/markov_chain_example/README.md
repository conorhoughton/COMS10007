
## What is it?

A **second-order markov model** that generate lyrics in the style 
of your favorite artist.


## How do you run it?

1) ` pip3 install requirements.txt`

2) python3 markov_chain.py --artist <your favorite artist> 


## How does it work??

Building a markov chain entails the following critical steps:

1) Collecting training data (in this case, a collection of songs made by said artist. See `fetch.py` )

2) Buidling transitions across words 

The first part is only incidental and relatively simple to accomplish with libraries.

The second part is the meat of it.

An example: let's say we concatenated all songs of our favorite artist to create one huge song. It could look something like this:


W0 W1 W4 W5 W3 END

W5 W6 W5 W4 W3 W1 W4 W2 END 

W5 W3 W3 W2 W5 END 


where W[i] is a word, END denotes a newline.

We do the following:

A) We make a list of all words that start out on a new line. That is, [W0, W5, W5]. Let's call this list **initial**

B) We create a mapping to represent that transitions from the first word to the second. So that looks something 
like this: W0 -> [W1]
	   W5 -> [W6, W1]
	   
	   
In code, this mapping is called **second**. So second[W0] = [W1]	

C) The most critical step: Because this is a second order markov chain, we create all possible mappings from **2** words to the next word 

Like this: 
	W0, W1 -> [W4]
	W4, W2 -> ["END"]
	W5, W6 -> [W5]
	W1, W4 -> [W5,w2]
	...etc 

Once we're done creating the mapping, we can generate a song out of it.

**Algorithm to generate a song:**

(1) So our initial list of words looks likes this: [W0, W5, W5]

We pick a random word, say W5. (Because W5 has a higher likelihood of getting picked; this is really the crux of the markov model)

(2) Now, we pick out a word that has a high likelihood of occurring AFTER W5. We have a list of words that occur after W5 as the second word =[W3, W6]. Let's say we pick W3.

(3) We then pick a word that occurs AFTER W5 and W3.  There's 2 options: ["END", "END", W3]. Say we pick W3. 

Repeat: pick a word that occurs after W3 and W3. 


(4) Keep doing this until you hit "END", at which point you start the whole process on a new line.







