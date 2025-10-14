'''
The weather_visualization function takes the
JSON-formatted weather data as input and uses
the Matplotlib library to create a visual plot.
'''
# Henry Lee
# hwlee4@uci.edu
# 89041994

import matplotlib.pyplot as p


def weather_visualization(data):
    '''
    Creates a visual plot of data
    with labels
    '''
    dates = [entry['datetime'] for entry in data['data']]
    high_temp = [entry['high_temp'] for entry in data['data']]
    low_temp = [entry['low_temp'] for entry in data['data']]
    city_name = data['city_name']

    p.figure(figsize=(10, 6))
    p.plot(dates, high_temp, marker='o', linestyle='-', label='High Temp')
    p.plot(dates, low_temp, marker='o', linestyle='-', label='Low Temp')
    p.xlabel('Date')
    p.ylabel('Temperature (°C)')
    p.title(f'Daily High and Low Temperatures in {city_name}')
    p.xticks(rotation=45)
    p.legend()
    p.tight_layout()
    p.savefig('WorkoutProject4-89041994.jpg')
