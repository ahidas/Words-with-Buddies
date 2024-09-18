from flask import Flask, jsonify, request, session, stream_with_context
from flask_session import Session
import subprocess
from flask_cors import CORS
import time
import uuid
from uuid import uuid4
import os
import sqlite3
import json


def get_db_connection():
    conn = sqlite3.connect('database.db')
    #conn.row_factory = sqlite3.Row
    return conn


#app instance
app = Flask(__name__)
app.secret_key = os.urandom(32)

#confif sessions
app.config["SESSION_COOKIE_SAMESITE"] = "None"
app.config["SESSION_COOKIE_SECURE"] = True
app.config["SESSION_TYPE"] = 'filesystem'
sess = Session()
sess.init_app(app)
CORS(app, supports_credentials=True)


##### High Level Overview
#recieve the board and letters in the '000abc000' format from the website 
#create a file with the users board and a file for the output of words
#both of these are unique to the user and is stored in a session variable
#call ./words
#parse output so that react can use it



def parse_user_info(data):
    user_data = json.loads(data)
    return user_data['username'], user_data['password']


#Parses the data sent from user and creates the users board in a file
def parseIn(string):
    curr_board_name = str(uuid.uuid4())
    session['curr_board'] = curr_board_name
    f = open('boards/' + curr_board_name, "w")
    spaces = string.decode().split(',')
    letters = spaces[0]
    spaces.pop(0)
    i = 0
    for space in spaces:
        if(not space or space == 'TW' or space =='DW' or space == 'TL' or space == 'DL' or space == '☆'):
            f.write('0')
        else:
            f.write(space.lower())
        i += 1

        if(i == 15):
            f.write('\n')
            i = 0
    f.close()
    return letters

#Formats the words to be sent back to user 
def parseOut(string):
    word = {
        "word": "",
        "points": "",
        "position": (),
        "direction": "",
        "new_letters": ""
    }
    data = {}
    words = []

    newline_sep = string.split('\n')
    data["total"] = int(newline_sep[0].split()[1])
    newline_sep = newline_sep[1:]
    i = 1
    for line in newline_sep:
        line_sep = line.split()
        if (len(line_sep) > 0):
            words.append({"word": line_sep[0],
        "points": line_sep[1],
        "position": (line_sep[2],line_sep[3]),
        "direction": line_sep[4],
        "new_letters": line_sep[5]})
            i += 1
    data["words"] = words
    return data



@app.route("/api/home", methods=['GET'])
def return_home():
    return jsonify({
        'message': "Hello world!"
    })

@app.route("/api/save_board", methods=['POST'])
def handle_save_board():
    data = json.loads(request.data)
    board_name = data['name']
    vals = data['vals']
    print (request.data) #data should be the vals array from the react app and fnam
    f_name = str(uuid.uuid4())
    f = open('saved_boards/' + f_name, 'w')
    f.write(request.data)
    with get_db_connection() as conn:
        cursor = conn.cursor()
        cursor.execute("""SELECT EXISTS (SELECT 1 FROM boards WHERE id=(?) and board_name=(?)) AS row_exists""",(5,board_name))
        res = res.fetchone()
        if(res[0] == 0):
            res = cursor.execute("INSERT INTO boards (id, board_name, vals) VALUES (?, ?, ?)", (5,board_name,vals))
            conn.commit()
            return jsonify(True)
        else:
            return jsonify(False)


@app.route("/api/users", methods=['GET'])
def handle_users():
    with get_db_connection() as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users")
        results = cursor.fetchall()

    print(results)
    return results

@app.route("/api/sign_up", methods=['POST','GET'])
def handle_sign_up():
    print(request.data)
    with get_db_connection() as conn:
        cursor = conn.cursor()
        user,password = parse_user_info(request.data)
        res = cursor.execute("""SELECT EXISTS (SELECT 1 FROM users WHERE user=(?)) AS row_exists""",(user,))
        res = res.fetchone()
        if(res[0] == 0):
            res = cursor.execute("INSERT INTO users (user, pass) VALUES (?, ?)", (user,password))
            conn.commit()
            return jsonify(True)
        else:
            return jsonify(False)

@app.route("/api/login", methods=['POST'])
def handle_login():
    with get_db_connection() as conn:
        cursor = conn.cursor()
        user,password = parse_user_info(request.data)
        res = cursor.execute("""SELECT id FROM users WHERE user= (?) and pass=(?)""",(user,password))
        row = res.fetchone()
        if(row is None):
            return jsonify(False)
        id = row[0]
        session['curr_id'] = id
        return jsonify(True)

#Sends a stream of progress updates
@app.route("/api/updates", methods=['POST', 'GET'])
def handle_post():
    print(request.data)
    words =  {
        "word": "",
        "points": "",
        "position": (),
        "direction": "",
        "new_letters": ""
    }
    letters = parseIn(request.data)

    f_name = str(uuid.uuid4())
    print(f_name)
    session['f_name'] = f_name
    print("session: " + session.get('f_name', None))
    fout = open(f_name,"w",buffering=1)
    fin = open(f_name, "r")

   # p1 = subprocess.Popen(['./words',session.get('curr_board', None), letters], stdout=fout.fileno(),text=True)
    p1 = subprocess.Popen(['./words',session['curr_board'],letters], stdout=fout.fileno(),text=True)
    def generate():
        index = 0
        while(True):
            output = fin.readline()
            if output:
                index+=1
                if(index == 225): #255 is the number of squares on a board
                    print(fin.tell())
                    fout.close()
                    fin.close()
                    while(p1.poll() is None): #make sure program finishes
                        time.sleep(.1)
                    yield(output.strip() + "-")
                    break
                yield(output.strip() + "-")

    return app.response_class(stream_with_context(generate()))

#reads the top words from the users file and returns it to user, this must be called after a call to updates completes
@app.route("/api/words", methods=['POST', 'GET'])
def handle_words():
        f_name = session['f_name']
        fin = open(f_name, "r")
        fin.seek(792) #magic number, always where updates end
        words_raw = fin.read()
        print(words_raw)
        words = parseOut(words_raw)
        fin.close()
        os.remove(f_name)
        os.remove('boards/' + session.get('curr_board',None))
        return jsonify(words)

        
if __name__ == "__main__":
    app.run(debug=True, port=5006)



    