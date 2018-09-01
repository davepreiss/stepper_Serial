from device import *
from flask import Flask, request, make_response
from math import *

# this is what grabs python from device.py
device = Device() # perhaps this should be device = device(_____)? as linkage is gone

app = Flask(__name__)
# http://flask.pocoo.org/docs/1.0/quickstart/

@app.route('/goto', methods=['POST'])
def goto():
    pos = float(request.args['pos'])
    # device.line_to(a1, a2, 50)
    device.move(pos)
    r = make_response('OK')
    r.headers['Access-Control-Allow-Origin'] = '*'
    return r

if __name__ == '__main__':
    app.run(debug=False)
