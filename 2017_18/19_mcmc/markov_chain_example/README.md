
## What is it?

A *second-order markov model* that generate lyrics in the style 
of a given  artist.


## How do you run it?

1) ` pip3 install requirements.txt`

2) `python3 markov_chain.py --artist <your favorite artist> `


## How does it work??

Building a markov chain entails the following critical steps:


* Collecting training data (in this case, a collection of songs by said artist. See `fetch.py`.)

* Buidling transitions across words 

The first part is only incidental and relatively simple to accomplish with libraries.

The second part is the meat of it. It has two sub-steps: prepreocessing and song generation (in that order).

**Pre Processing**

Given a collection of songs (aka "training data") by our favorite artist, we can flatten out the songs to form one huge song. It could look something like this:

<pre> 
	W0 W1 W4 W5 W3 END

	W5 W6 W5 W4 W3 W1 W4 W2 END 

	W5 W3 W3 W2 W5 END 

</pre>


where `W[i]` is a word, `END` denotes a newline.

We do the following:

A) We make a list of all words that start out on a new line. That is, `[W0, W5, W5]`. Let's call this list `initial`

B) We create a mapping to represent that transitions from the first word to the second. So that looks something 
like this: 
<pre> 
	W0 -> [W1]
	W5 -> [W6, W1]
</pre>
	   
In code, this mapping is called `second`. So `second[W0] = [W1]	`.

C) The most critical step: Because this is a second order markov chain, we create all possible mappings from **2** words to the next word 
<pre>
Like this: 
	(W0, W1) -> [W4]
	(W4, W2) -> ["END"]
	(W5, W6) -> [W5]
	(W1, W4) -> [W5,w2]
	...etc 
</pre>

Once we're done creating these mappings, we can generate a song out of it.

**Algorithm to generate a song:**
`
* So our initial list of words looks likes this: `[W0, W5, W5]` We pick a random word, say `W5`. (`W5` has a higher likelihood of getting picked; this is *really the crux of the markov model, picking high probability sequences, given some data*)

* Now, we pick out a word that has a high likelihood of occurring AFTER W5. We can use `second` to see what words come after W5. `second[w5] = [W3, W6]`. Let's say we pick W3.

* We then pick a word that occurs <i> AFTER </i>  W5 and W3.  There's 2 options: `["END", "END", W3]`. Say we pick W3. 

* Repeat: pick a word that occurs after two succesive `W3 and W3` (hint: it's W2 (the third line in the training data). Now pick a word that occurs after `W3` and `W2`...). 


* Keep doing this until you hit `END`, at which point you start the whole process on a new line.







