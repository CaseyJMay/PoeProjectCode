import spotipy
import spotipy.util as util
import sys
from spotipy.oauth2 import SpotifyClientCredentials

# export SPOTIPY_CLIENT_ID='aa68cd63fc8f4e7dab614bbf91008b23'
# export SPOTIPY_CLIENT_SECRET='bf148999956d428eb0af2a93d60d132f'
# export SPOTIPY_REDIRECT_URI='http://localhost/'
scope = 'user-read-currently-playing'
username = 'thranxar'

#util.prompt_for_user_token(username,scope,client_id=' aa68cd63fc8f4e7dab614bbf91008b23',client_secret='bf148999956d428eb0af2a93d60d132f',redirect_uri='https://github.com/CaseyJMay')
token = util.prompt_for_user_token(username, scope)

if token:
    sp = spotipy.Spotify(auth=token)
    current_track = sp.currently_playing(market=None)
    current_track_uri = current_track['item']['uri']
else:
    print("Can't get token for" + username)


scope = 'user-library-read'
token = util.prompt_for_user_token(username, scope)

if token:
    sp = spotipy.Spotify(auth=token)
    scope = 'user-library-read'
    results = sp.audio_analysis(current_track_uri)
    print(results)
else:
    print("Can't get token for" + username)
