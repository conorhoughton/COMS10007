"""

A one-off script that generates lyrics in the style
of any given artist. 

See README.txt for more details.

Example usage: python3 markov_chain.py --artist <your favorite artist> 

By: Navya Zaveri, CS MEng Class of 2021.

"""




import numpy as np
from collections import defaultdict
import requests
from PyLyrics import *
import bs4 as bs
import requests
import numpy as np
from collections import defaultdict
import re
import fetch
import argparse
import warnings
import time 
warnings.filterwarnings("ignore")


class MarkovChain:
    def __init__(self):

        self.initial = []
        self.second = defaultdict(list)
        self.transition = defaultdict(list)

    def fit(self, songs):
        for each_song in songs:
            for line in each_song:
                words = line.split()
                if len(words) <= 1:
                    continue

                for word_index in range(len(words)):
                    if word_index == 0:
                        self.initial.append(words[word_index])

                    elif word_index == 1:
                        prev_word = words[word_index-1]
                        cur_word = words[word_index]
                        self.second[prev_word].append(cur_word)

                    else:
                        prev_prev_word = words[word_index-2]
                        prev_word = words[word_index-1]
                        cur_word = words[word_index]
                        if word_index == len(words) - 1:
                            self.transition[(prev_word, cur_word)].append("END")

                        self.transition[(prev_prev_word, prev_word)].append(cur_word)

    def _random_sampling(self, list_of_words):
        return np.random.choice(list_of_words)

    def generate_song(self, lines=10):
        song = ""
        for line in range(lines):
            w0 = self._random_sampling(self.initial)
            w1 = self._random_sampling(self.second[w0])
            song += w0 + " " + w1
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


def main(artist):
    print("Fetching data...")

    artist_songs = fetch.songs_by_artist(artist)

    if len(artist_songs)==0:
        raise Exception("I haven't heard of anything by " +artist+"! Try another artist.")

    print("Fetch successful. Now building markov model....")

    time.sleep(2)

    model = MarkovChain()
    model.fit(artist_songs)
    new_song = model.generate_song()
    print("################ THE SONG #############################")
    print(new_song)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--artist', nargs='+', type=str,
                        help='What artist to train the markov model on?')
    args = parser.parse_args()
    if not args.artist:
        raise argparse.ArgumentError(args.artist,
                                     "Example usage: python3 markov_chain.py --artist <your favourite artist>")
    artist = " ".join(args.artist)
    main(artist)
