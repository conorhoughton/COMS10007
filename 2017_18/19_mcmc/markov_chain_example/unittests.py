import unittest
from collections import defaultdict
from markov_chain import MarkovChain


class TestMarkovModel(unittest.TestCase):
    def setUp(self):
        self.model = MarkovChain()
        self.lyrics = [["hello world"], ["how are you"]]
        self.model.fit(self.lyrics)


    def test_first_words(self):
        self.assertEqual(self.model.initial,["hello", "how"])

    def test_second_transition(self):
        actual_second = defaultdict(list)
        actual_second["hello"].append("world")
        actual_second["how"].append("are")
        self.assertEqual(self.model.second,actual_second)


if __name__ == '__main__':
    unittest.main()
