from flask import Flask, request, jsonify
import datetime

app = Flask(__name__)

sensor_data_list = []

@app.route('/sensor/data', methods=['POST'])
def add_sensor_data():
    try:
        data = request.json
        temperature = data.get('temperature')
        kelembapan = data.get('kelembapan')
        timestamp = data.get('timestamp')

        sensor_data = {
            'temperature': temperature,
            'kelembapan': kelembapan,
            'timestamp': timestamp,
            'received_at': datetime.datetime.now().isoformat()
        }

        sensor_data_list.append(sensor_data)

        return jsonify({'message': 'Data successfully added'}), 201
    except Exception as e:
        return jsonify({'error': str(e)}), 400

@app.route('/sensor/data', methods=['GET'])
def get_sensor_data():
    return jsonify(sensor_data_list), 200

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
