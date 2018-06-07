
## What is it?

A *second-order markov model* that generate lyrics in the style 
of a given  artist. 


## How do you run it?

1) ` pip3 install requirements.txt`

2) `python3 markov_chain.py --artist <your favorite artist> `

(optionally: `python3 markov_chain.py --artist <your favorite artist> --limit <training_data_size>`


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

*  We make a list of all words that start out on a new line. That is, `[W0, W5, W5]`. Let's call this list `initial`

* We create a mapping to represent that transitions from the first word to the second. So that looks something 
like this: 
<pre> 
	W0 -> [W1]
	W5 -> [W6, W3]
</pre>
	   
In code, this mapping is called `second`. So `second[W0] = [W1]	`.

* The most critical step: Because this is a second order markov chain, we create all possible mappings from **2** words to the next word 
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

* So, given the training data, our `initial` list likes this: `[W0, W5, W5]` We randomly pick a word, say `W5`. (`W5` has a higher likelihood of getting picked; this is *really the crux of the markov model, picking high probability sequences.*)

	- Mathematically,  `P(W5 | we've just started) = 2/3. ` So it makes sense that, despite picking randomly, `W5` has a good chance of being selected. We apply the same logic in the ensuing steps.

* Now, we randomly pick a word that occurrs AFTER `W5`. We can use `second` to see what words come after W5. `second[w5] = [W3, W6]`. Let's say we pick `W3`.

	- `In this case, P(W3 | W5) = P(W6 | W5) = 0.5 `

* We then pick a word that occurs after `W5` and `W3` (in that order!).  There's a few options: `["END", "END", W3]`. Say we pick `W3`. Had we picked `END`, we would start the algorithm again on the next line. 

* Repeat: pick a word that occurs after two succesive `W3`'s (hint: it's `W2` (the third line in the training data). Now pick a word that occurs after `W3` and `W2`...). 


* Keep doing this until you hit `END`, at which point you start the whole process on a new line.

The relevant chunk of code:

<code> 
	<pre>
	def generate_song(self, lines=10):
	        song = ""
		for line in range(lines):
		    w0 = self._random_sampling(self.initial)
		    w1 = self._random_sampling(self.second[w0])
		    song += w0 + " "+w1
		    while True:
			w2 = self._random_sampling(self.transition[(w0, w1)])
			w0 = w1
			w1 = w2
			if w2 == "END":
			    song += "\n"
			    break
			else:
			    song += " " + w2
		return song
		</pre>
</code> 


**Implementation drawbacks** 

* It's not efficient, in terms of space complexity, to have such huge lists. Maybe a create a set of tuples, where the first element in the tuple is a word, and the second element is the frequency of that word? 

* Cache the songs to reduce uptime. Easily accomplished with redis.








