from flask import Flask, jsonify, request
import subprocess
from flask_cors import CORS
from flask import stream_with_context
import time
#app instance
app = Flask(__name__)
CORS(app)

#recieve the board in the '000abc000' format from the website and users input

#create a file with the users board

#call ./words

#parse output so that react can use it
def parseIn(string):
    f = open("boards/curr_board.txt", "w")
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
    #print(letters)
    fout = open("out.txt","w",buffering=1)
    fin = open("out.txt", "r")
    p1 = subprocess.Popen(['./words','devin.txt', 'abcasefasef'], stdout=fout.fileno(),text=True)

    def generate():
        index = 0
        while(True):
            output = fin.readline()
            if output:
                index+=1
                yield(output.strip() + "-")
                if(index == 225):
                    print(fin.tell())
                    break
    return app.response_class(stream_with_context(generate()))


@app.route("/api/words", methods=['POST', 'GET'])
def handle_words():
        fin = open("out.txt", "r")
        fin.seek(792) #magic number, always where updates end
        time.sleep(.5)
        words_raw = fin.read()
        print(words_raw)
        words = parseOut(words_raw)
        return jsonify(words)
if __name__ == "__main__":
    app.run(debug=True, port=5006)



    