'''
a5.py is an extension of a4.py in which it utilizes
ui.py and implements GUI features based off extended
modules ds_client and ds_protocol.
'''
# a5.py

# Starter code for assignment 5 in ICS 32
# Programming with Software Libraries in Python

# Replace the following placeholders with your information.

# Henry Lee
# hwlee4@uci.edu
# 89041994


import os
import json
from pathlib import Path
from Profile import Post, Profile
from ui import process
import ds_client
import LastFM
import OpenWeather
import WebAPI
import json as js
import urllib.error
from urllib import request
import ds_protocol

path = Path()
profile = Profile()
server_port = int(3021)
open_weather = None
last_fm = None


def send_direct_message(token: str, entry: str, recipient: str, timestamp: str):
    '''
    Sends a direct message to the recipient using ds_client.
    '''
    json_message = ds_protocol.create_direct_message(token, entry, recipient, timestamp)
    ds_client.send_message(json_message)

def request_messages(token: str, message_type: str):
    '''
    Requests messages from the server based on the message type using ds_client.
    '''
    json_message = ds_protocol.create_request_messages(token, message_type)
    ds_client.send_message(json_message)

def handle_response(response: str):
    '''
    Handles the response from the server using ds_protocol.
    '''
    data_tuple = ds_protocol.extract_json(response)
    if data_tuple.type == "ok":
        print(data_tuple.message)
        if data_tuple.token:
            return data_tuple.token
    else:
        print("Error:", data_tuple.message)

def _download_url(url_to_download: str) -> dict:
            response = None
            r_obj = None
            try:
                response = request.urlopen(url_to_download)
                json_results = response.read()
                r_obj = js.loads(json_results)
            except urllib.error.HTTPError as e:
                print('Failed to download contents of URL')
                print(f'Status code: {e.code}')
            finally:
                if response is not None:
                    response.close()
            return r_obj


def list(directory_path, options=None):
    '''
    Provides a way to filter and display files and
    directories within a specified directory based
    on certain options.
    '''
    directory = Path(directory_path)
    files = [item for item in directory.iterdir() if item.is_file()]
    directories = [item for item in directory.iterdir() if item.is_dir()]
    directories.reverse()
    options.reverse()
    ans = []

    while len(options) != 0:
        operation = options.pop()
        if operation == '-r':
            while len(files) != 0:
                ans.append(files[0])
                files.pop(0)
            while len(directories) != 0:
                temp = directories.pop()
                ans.append(temp)
                for f in temp.iterdir():
                    if f.is_file():
                        ans.append(f)
                    else:
                        directories.append(f)
        elif operation == '-f':
            temp = []
            if ans == []:
                for i in files:
                    temp.append(i)
            else:
                for i in ans:
                    if i.is_file():
                        temp.append(i)
            ans = temp
        elif operation == '-e':
            temp = []
            extension = "." + options.pop()
            if ans == []:
                for i in files:
                    ext = os.path.splitext(i)[1]
                    if extension == ext:
                        temp.append(i)
            else:
                for i in ans:
                    ext = os.path.splitext(i)[1]
                    if extension == ext:
                        temp.append(i)
            ans = temp
        elif operation == '-s':
            temp = []
            desire = options.pop()
            if ans == []:
                for i in files:
                    check = os.path.basename(i)
                    if check == desire:
                        temp.append(i)
            else:
                for i in ans:
                    check = os.path.basename(i)
                    if check == desire:
                        temp.append(i)
            ans = temp
    for i in ans:
        print(i)


def list_recursive(directory):
    '''
    Lists all the items (files and directories)
    in the specified directory and subdirectories
    recursively.
    '''
    for item in os.listdir(directory):
        ans = os.path.join(directory, item)
        print(ans)


def create_file(directory, command, name):
    '''
    Creates the file and adds it to a
    server with username and password.
    '''
    if command != '-n':
        print("ERROR")
    ans = os.path.join(directory, name + ".dsu")
    global path
    if os.path.exists(Path(ans)):
        open_file(Path(ans))
    else:
        path = ans
        server = input("What server do you want to join? ")
        username = input("Enter your username: ")
        while ' ' in username:
            print("ERROR: Username must not contain whitespace")
            username = input("Enter your username: ")
        password = input("Enter your password: ")
        while ' ' in password:
            print("ERROR: Password must not contain whitespace")
            password = input("Enter your password: ")

        data = {'dsuserver': server,
                'username': username,
                'password': password,
                'bio': ""}
        global profile
        profile = Profile(server, username, password)
        f = open(ans, 'w')
        json.dump(data, f)
        f.close()


def delete_file(file_path):
    '''
    Deletes the file upon
    user's request.
    '''
    remove_file = Path(file_path)
    if (os.path.exists(remove_file) and remove_file.suffix == '.dsu'):
        os.rmdir(remove_file)
        print(f"{remove_file} DELETED")
    else:
        print("ERROR")


def read_file(file_path):
    '''
    Function reads the user's
    given file.
    '''
    file_to_read = Path(file_path)
    if (file_to_read.exists() and
        file_to_read.is_file() and
            os.path.splitext(file_to_read)[1] == '.dsu'):
        ans = open(file_to_read, "r")
        if ans is None:
            print("EMPTY")
        else:
            print(ans.read())

        ans.close()
    else:
        print("ERROR")


def open_file(file_path):
    '''
    Simply opens file while checking for errors.
    '''
    global path
    path = Path(file_path)
    if path.exists() and path.is_file() and path.suffix == '.dsu':
        try:
            with open(path, 'r') as f:
                data = json.load(f)
                server = data.get('dsuserver', 'N/A')
                username = data.get('username', 'N/A')
                password = data.get('password', 'N/A')

                print("DSU Server:", server)
                print("Username:", username)
                print("Password:", password)
                next_command = input("Do you want to join as a user on "
                                     "the server? (y/n) ")
                if next_command == 'y':
                    ds_client.send(server, server_port, username,
                                   password, "", "")
        except json.JSONDecodeError:
            print("Invalid JSON format in the file.")
    elif not path.exists():
        print("ERROR: File does not exist.")
    elif not path.is_file():
        print("ERROR: The specified path is not a file.")
    elif path.suffix != '.dsu':
        print("ERROR: The file is not a .dsu file")
    else:
        print("ERROR: File does not exist or is not a .dsu file.")


def edit_file(options):
    '''
    Edits the file, given the options that the user
    wants to edit.
    '''
    my_file = Path(path)
    temp = options.split()
    command = []
    for i in temp:
        if i[0] == '-':
            command.append(i)
    inputs = options.split('"')[1::2]
    pos = 0
    if my_file.exists() and my_file.is_file() and my_file.suffix == '.dsu':
        f = open(my_file, 'r+')
        data = f.read()

        start = data.find('dsuserver') + 13
        end = data.find(', \"username', start)
        server = data[start:end-1]

        start = data.find('username') + 12
        end = data.find(', \"password', start)
        username = data[start:end-1]

        start = data.find('password') + 12
        end = data.find(', \"bio', start)
        password = data[start:end-1]

        start = data.find('bio') + 7
        end = data.find('}', start)
        bio = data[start:end-1]
        f.close()
        f = open(my_file, 'w')
        while pos != len(command):
            if command[pos] == '-usr':
                username = inputs[pos]
            elif command[pos] == '-pwd':
                password = inputs[pos]
            elif command[pos] == '-bio':
                bio = inputs[pos]
                next_input = input("Do you want to send this "
                                   "to the server? (y/n) ")
                if next_input == 'y':
                    ds_client.send(server, server_port, username,
                                   password, "", bio)
            elif command[pos] == '-addpost':
                post = Post()
                print(post)
                one = input("Which do you want to transclude? "
                            "LastFM (listeners) or "
                            "OpenWeather (description of weather): ")
                ans = ""
                if one.upper() == 'LASTFM':
                    ans = last_fm.transclude(inputs[pos])
                elif one.upper() == 'OPENWEATHER':
                    ans = open_weather.transclude(inputs[pos])
                else:
                    ans = inputs[pos]
                # elif one.upper() == 'NO':
                #     continue
                post.set_entry(ans)
                profile.add_post(post)
                next_input = input("Do you want to send this to "
                                   "the server? (y/n) ")
                if next_input == 'y':
                    ds_client.send(server, server_port, username, password,
                                   post.get_entry(), "")
            elif command[pos] == '-delpost':
                post = Post()
                thing = profile.get_posts()
                h = int(temp[1])
                if (h-1) > len(thing):
                    print('ERROR')
                else:
                    profile.del_post(h-1)
            else:
                print('ERROR')
            pos += 1
        data = {'dsuserver': server,
                'username': username,
                'password': password,
                'bio': bio}
        json.dump(data, f)
        f.close()
    else:
        print("ERROR")


def print_profile(options):
    '''
    Based on user's command, function prints
    out what the user requested from the options below.
    '''
    my_file = Path(path)
    if my_file.exists() and my_file.is_file() and my_file.suffix == '.dsu':
        f = open(my_file, 'r')
        data = f.read()
        if '-usr' in options:
            start = data.find('username') + 11
            end = data.find(', \"password', start)
            username = data[start:end]
            print("Username:", username)
        elif '-pwd' in options:
            start = data.find('password') + 11
            end = data.find(', \"bio', start)
            password = data[start:end]
            print("Password:", password)
        elif '-bio' in options:
            start = data.find('bio') + 6
            end = data.find('}', start)
            bio = data[start:end]
            print("Bio:", bio)
        elif '-posts' in options:
            posts = profile.get_posts()
            print(posts)
        elif '-post' in options:
            pos = int(options[1])
            posts = profile.get_posts()
            if pos > len(posts):
                print("Invalid post ID")
            else:
                print(posts[pos-1])
        elif '-all' in options:
            print("All content:")
            start = data.find('username') + 11
            end = data.find(', \"password\"', start)
            username = data[start:end-1]
            print("Username:", username)

            start = data.find('password') + 11
            end = data.find(', \"bio\"', start)
            password = data[start:end-1]
            print("Password:", password)

            start = data.find('bio') + 6
            end = data.find('}', start)
            bio = data[start:end-1]
            print("Bio:", bio)

            posts = profile.get_posts()
            print(posts)

        f.close()
    else:
        print("ERROR")


def quit():
    '''
    Quits out.
    '''
    exit()


admin = False


def run():
    '''
    The main code that runs this program by
    identifying what command the user
    inputs into the system.
    '''
    while True:
        global admin
        command = process(admin)
        if command == 'admin':
            admin = True
            command = input()
        command_parts = command.split()
        response = command_parts[0]
        print(command_parts)

        if response == 'Q':
            quit()
        elif response == 'L':
            directory_path = command_parts[1]
            if len(command_parts) >= 3:
                list(directory_path, command_parts[2:])
            else:
                list_recursive(directory_path)
        elif response == 'R':
            if len(command_parts) == 2:
                read_file(command_parts[1])
            else:
                print('Invalid')
        elif response == "C":
            if len(command_parts) == 4:
                create_file(command_parts[1],
                            command_parts[2],
                            command_parts[3])
            else:
                print("ERROR")
        elif response == 'D':
            if len(command_parts) == 2:
                delete_file(command_parts[1])
            else:
                print("ERROR")
        elif response == 'O':
            if len(command_parts) == 2:
                open_file(command_parts[1])
            else:
                print("ERROR")
        elif response == 'E':
            if len(command_parts) >= 1:
                options = command.replace('E ', '')
                edit_file(str(options))
            else:
                print("ERROR")
        elif response == 'P':
            if len(command_parts) >= 1:
                print_profile(command_parts[1:])
            else:
                print("ERROR")
        elif response.upper() == 'Y':
            if command_parts[1] == '1':
                temp = LastFM.LastFM()
                user_artist = command_parts[2]
                user_key = command_parts[3]
                temp.set_api(user_key, user_artist)
                global last_fm
                last_fm = temp
                last_fm.load_data()
            elif command_parts[1] == '2':
                temp = OpenWeather.OpenWeather()
                user_zip = command_parts[2]
                user_ccode = command_parts[3]
                user_key = command_parts[4]
                temp.set_apikey(user_key)
                temp.set_ccode(user_ccode)
                temp.set_zipcode(user_zip)
                global open_weather
                open_weather = temp
                open_weather.load_data()
        elif response.lower() == 'directmessage':
            # Sending a direct message
            token = input("Enter your token: ")
            entry = input("Enter your message: ")
            recipient = input("Enter recipient username: ")
            timestamp = input("Enter timestamp: ")
            send_direct_message(token, entry, recipient, timestamp)
        elif response.upper() == 'NEW':
            # Requesting new messages
            token = input("Enter your token: ")
            request_messages(token, "new")
        elif response.upper() == 'ALL':
            # Requesting all messages
            token = input("Enter your token: ")
            request_messages(token, "all")
        else:
            print("Invalid; Enter 'L', 'C', 'D', 'R', 'O', 'E', 'P' or 'Q'")


if __name__ == "__main__":
    run()
