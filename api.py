'''
The weatherAPI class is responsible for interacting
with the Weatherbit API to fetch daily weather
forecasts for a specified city. get_weather method
takes a city name as input, constructs a URL with the
necessary parameters (including the API key), and
sends a request to the Weatherbit API.
'''
# Henry Lee
# hwlee4@uci.edu
# 89041994

import json as js
from urllib import request
from urllib.parse import quote


class WeatherAPI:
    '''
    API class for weather which will be used to
    interact with the weather api
    '''
    def __init__(self, key):
        '''
        Initializes weather api object
        by taking key
        '''
        self.url = "https://api.weatherbit.io/v2.0"
        self.apikey = key
    try:
        def get_weather(self, city):
            '''
            Connects to weatherapi.io with specified weather
            returns json data
            '''
            my_city = quote(city)
            print(my_city)
            url = f"{self.url}/forecast/daily"
            parameters = {
                "key": self.apikey,
                "city": my_city
            }
            temp = '&'.join([f'{key}={value}' for key, value
                             in parameters.items()])
            line = f"{url}?{temp}"
            resp = request.urlopen(line)
            var = js.loads(resp.read())
            print(var)
            return var
    except Exception as e:
        print(f"Error: {e}")


def read(data, filename):
    '''
    Creates JSON file with data from
    weather api
    '''
    with open(filename, "w") as f:
        js.dump(data, f)
