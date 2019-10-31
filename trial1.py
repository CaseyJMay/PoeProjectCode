# export SPOTIPY_CLIENT_ID='32ff2b617b2842689c41c40ed094e055'
# export SPOTIPY_CLIENT_SECRET='8ab27008ff8440fc9f856598034a7bde'
# export SPOTIPY_REDIRECT_URI='http://localhost/'

import sys
import spotipy
import spotipy.util as util

scope = 'user-read-currently-playing'
username = 'HK Rho'


token = util.prompt_for_user_token(username, scope)
sp = spotipy.Spotify(auth=token)


if token:
    sp = spotipy.Spotify(auth=token)
    current_track_uri = sp.currently_playing(market=None)
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