'''
The run function serves as the entry point for the
entire project. It initializes the WeatherAPI object,
prompts the user to input a city, fetches weather data
using the API, saves the data to a JSON file, and
visualizes it using weather_visualization.
'''
# Henry Lee
# hwlee4@uci.edu
# 89041994
import api as get_api
from visualization import weather_visualization


def run():
    '''
    Assigns values to variables
    Creates WeatherAPI object
    Calls different functions from modules
    '''
    key = "08e57c1e4f584f46bc21eafe2bc660ee"
    weather = get_api.WeatherAPI(key)
    city = input("Enter city: ")
    user_city = city
    weather_data = weather.get_weather(user_city)
    get_api.read(weather_data, "daily weather read file.json")
    weather_visualization(weather_data)
    print("Data retrieved: JPG file created.")


if __name__ == "__main__":
    run()
