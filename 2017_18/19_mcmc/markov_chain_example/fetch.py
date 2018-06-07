import bs4 as bs
import requests
import re
from PyLyrics import *

BASE_URL = "http://www.songfacts.com/artist-{}.php"
LIMIT = 45 #number of songs to fetch. Anything higher sadly leads to a request timeout 


def songs_by_artist(artist):
    artist = re.sub(" ", "_", artist)
    artist_url = BASE_URL.format(artist)
    resp = requests.get(artist_url)
    html = bs.BeautifulSoup(resp.text, "lxml")
    song_titles = []
    for ul in html.find_all(class_="songullist-orange"):
        for song in ul.find_all("li")[:LIMIT]:
            song_titles.append(song.text)

    songs = extract_song_from_song_title(artist, song_titles)
    return songs


def extract_song_from_song_title(artist, song_titles):
    songs = []
    for song_title in song_titles:
        try:
            lyrics = PyLyrics.getLyrics(artist, song_title).splitlines()
            clean_lyrics = [
                re.sub("[^a-z' ]", "", line.lower().strip()) for line in lyrics]
            songs.append(clean_lyrics)
        except ValueError:
            pass
    return songs
