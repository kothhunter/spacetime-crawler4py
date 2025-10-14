'''
User interface allows easier readability
for users to interact with this program.
'''

# Henry Lee
# hwlee4@uci.edu
# 89041994

import gui


def process(admin):
    '''
    Starts the user interface system for easier
    maneuvering of program.
    '''
    if admin:
        command = input()
        return command
    command = input("Welcome! Do you want to create a LastFM "
                    "or OpenWeather class (y/n)? Or send a "
                    "directmessage (d)? ")
    if command == 'd':
        string = "d "
        command = input("Type 'DIRECTMESSAGE', 'NEW', or 'ALL'")
        if command.upper() == 'DIRECTMESSAGE':
            # Handling direct message command
            token = input("Enter your token: ")
            entry = input("Enter your message: ")
            recipient = input("Enter recipient username: ")
            timestamp = input("Enter timestamp: ")
            string += f"{command} {token} {entry} {recipient} {timestamp}"
        elif command.upper() == 'NEW':
            # Handling request for new messages
            token = input("Enter your token: ")
            string += f"{command} {token}"
        elif command.upper() == 'ALL':
            # Handling request for all messages
            token = input("Enter your token: ")
            string += f"{command} {token}"
        else:
            command = input("Invalid. Type 'DIRECTMESSAGE', 'NEW', or 'ALL'")
    if command == 'y':
        string = "y "
        command = input("Type '1' for LastFM and '2' "
                        "for OpenWeather: ")
        if command == '1':
            string += '1 '
            user_artist = input("Name of artist? ")
            user_key = input("What's your APIkey? ")
            string += f"{user_artist} {user_key}"

        elif command == '2':
            string += '2 '
            user_zip = input("What's your zip code? ")
            user_ccode = input("What's your country code? ")
            user_key = input("What's your APIkey? ")
            string += f"{user_zip} {user_ccode} {user_key}"
        else:
            command = input("Invalid; Type 1 or 2")
        return string

    command = input("Do you want to create or load a DSU file "
                    "(type 'c' to create or 'l' to load or 'no' "
                    "to move on): ")
    if command.lower() == 'admin':
        return "admin"
    if command.lower() == 'no':
        string = ""
        contin = True
        while contin:
            temp = input("Would you like to read (R), "
                         "delete (D), edit (E), open(O), "
                         "or print (P) the file: ").upper()
            poss = ["R", "D", "E", "P", "O"]
            if (x in temp for x in poss):
                string += f"{temp} "
                if 'R' == temp:
                    file_input = input("Write your file path: ")
                    string += f"{file_input} "
                    return string
                if 'D' == temp:
                    file_input = input("Write your file path: ")
                    string += f"{file_input} "
                    return string
                if 'E' == temp:
                    edit_list = ["-usr", "-pwd", "-bio",
                                 "-addpost", "-delpost"]
                    cont = True
                    while cont:
                        file_input = input("What option do you "
                                           "want to edit?\n "
                                           "'-usr', '-pwd', '-bio', "
                                           "'-addpost', '-delpost': ")
                        if file_input in edit_list:
                            cont = False
                            string += f"{file_input} "
                            next_input = input("Include new name "
                                               "or value: ")
                            tempstring = "\"" + next_input + "\""
                            string += tempstring
                    return string
                if 'P' == temp:
                    print_list = ["-usr", "-pwd", "-bio",
                                  "-posts", "-post", "-all"]
                    cont = True
                    while cont:
                        file_input = input("What option do you "
                                           "want to print?\n "
                                           "'-usr', '-pwd', "
                                           "'-bio', '-posts', "
                                           "'-post', '-all': ")
                        if file_input in print_list:
                            cont = False
                            string += f"{file_input} "
                            if file_input == '-post':
                                next_input = input("Write post number: ")
                                string += next_input
                    return string
                if 'O' == temp:
                    file_input = input("Write your file "
                                       "you want to open: ")
                    string += f"{file_input} "
                    return string
        print("ERROR")
    else:
        string = ""
        if command.upper() == 'Q':
            exit()
        elif command.lower() == 'c':
            string += "C "
            user_file = input("Sounds good! Which pathway would you like "
                              "to put the file in: ")
            string += f"{user_file} "
            user_file = input("Got it! What name do you want "
                              "the file to have: ")
            string += f"-n {user_file} "
            return string
        elif command.lower() == 'l':
            string += "L "
            user_file = input("Great! What is the name of the file you "
                              "would like to load? ")
            string += f"{user_file} "
            new_input = input("Would you like to add "
                              "more commands (yes or no): ")
            if new_input.lower() == 'no':
                return string
            if new_input.lower() == 'yes':
                cont = True
                while cont:
                    directory_content = input("Type '-r' to output "
                                              "directory "
                                              "content recursively\n"
                                              "Type '-f' to output "
                                              "only files, "
                                              "excluding directories "
                                              "in the results\n"
                                              "Type '-s' to output only "
                                              "files that match a "
                                              "given file name\n"
                                              "Type '-e' to output only "
                                              "files that "
                                              "match a given file "
                                              "extension\n")
                    print(directory_content)
                    poss = ["-r", "-f", "-s", "-e"]
                    if directory_content in string:
                        directory_content = input("You already have that "
                                                  "command; add a new "
                                                  "one: ")
                    elif (x in directory_content for x in poss):
                        string += f"{directory_content} "
                        cont = False
                        return string
            else:
                new_input = input("Type 'yes' or 'no'.")
        else:
            print("ERROR")
