from flask import Flask, request, jsonify

app = Flask(__name__)

sensor_data_list = []

@app.route('/sensor/data', methods=['POST'])
def add_sensor_data():
    data = request.json
    temperature = data.get('temperature')
    kelembapan = data.get('kelembapan')
    timestamp = data.get('timestamp')

    sensor_data = {
        'temperature': temperature,
        'kelembapan': kelembapan,
        'timestamp': timestamp
    }

    sensor_data_list.append(sensor_data)

    return jsonify({'message': 'Data successfully added'}), 201

@app.route('/sensor/data', methods=['GET'])
def get_sensor_data():
    return jsonify(sensor_data_list), 200

if __name__ == '__main__':
    app.run(debug=True)
