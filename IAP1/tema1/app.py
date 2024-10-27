from flask import Flask, render_template, request, send_file
from werkzeug.utils import secure_filename
from PIL import Image
import numpy as np

app = Flask(__name__)

# Variable to store the last encoded image and decoded message
last_encoded_image = ""
last_decoded_message = None


def encode_message(original_image, text):
    # Open the original image
    width, height = original_image.size

    # Check if the image is big enough to hide the message
    if (len(text) * 8) > (width * height * 3):
        raise ValueError("Text too long for chosen image....")

    # Normalize the original image (make pixel values even)
    pixel_data = np.array(original_image)
    for i in range(pixel_data.shape[0]):
        for j in range(pixel_data.shape[1]):
            for k in range(3):  # RGB channels
                if pixel_data[i][j][k] % 2 != 0:
                    pixel_data[i][j][k] -= 1

    # Convert the message to a binary string
    binary_message = ''.join(format(ord(char), '08b') for char in text)

    # Apply the binary string to the image
    counter = 0
    for i in range(pixel_data.shape[0]):
        for j in range(pixel_data.shape[1]):
            for k in range(3):  # RGB channels
                if counter < len(binary_message):
                    pixel_data[i][j][k] += int(binary_message[counter])
                    counter += 1
                else:
                    break
            if counter >= len(binary_message):
                break
        if counter >= len(binary_message):
            break

    # Save the new image with the message embedded
    encoded_image = Image.fromarray(pixel_data)
    return encoded_image


def decode_message(encoded_image):
    # Open the encoded image
    pixel_data = np.array(encoded_image)

    binary_message = ""

    for i in range(pixel_data.shape[0]):
        for j in range(pixel_data.shape[1]):
            for k in range(3):  # RGB channels
                binary_message += str(pixel_data[i][j][k] % 2)

    # Convert the binary string to characters
    output = ""
    for i in range(0, len(binary_message), 8):
        byte = binary_message[i:i + 8]
        if len(byte) < 8:
            break
        output += chr(int(byte, 2))

    return output.rstrip('\x00')  # Remove any padding zeros


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/encode')
def encode():
    return render_template('encode.html')


@app.route('/decode')
def decode():
    return render_template('decode.html')


@app.route('/image/encode', methods=['POST'])
def encode_image():
    global last_encoded_image, last_decoded_message

    # Get the uploaded file and message from the request
    file = request.files['file']
    message = request.form['message']

    # Open the image file
    image = Image.open(file.stream)

    try:
        # Perform steganography encoding
        encoded_image = encode_message(image, message)

        # Save the encoded image on the server's disk
        encoded_image_filename = secure_filename(file.filename)
        encoded_image.save('images/' + encoded_image_filename)

        # Update the last encoded image and decoded message variables
        last_encoded_image = encoded_image_filename
        last_decoded_message = None

        # Return the encoded image as a binary download
        return send_file('images/' + encoded_image_filename, as_attachment=True)
    except ValueError as e:
        return str(e)


@app.route('/image/last/encoded')
def get_last_encoded_image():
    if last_encoded_image is not None:
        return send_file('images/' + last_encoded_image, as_attachment=True)
    else:
        return 'No last encoded image found.', 404


# TO BE IMPLEMENTED
@app.route('/image/decode', methods=['POST'])
def decode_image():
    global last_decoded_message, last_encoded_image

    # Get the uploaded encoded image from the request
    file = request.files['file']

    # Open the image file
    image = Image.open(file.stream)

    # Perform steganography decoding
    decoded_message = decode_message(image)

    # Update the last decoded message variable
    last_decoded_message = decoded_message

    # Save the uploaded image to display it later
    encoded_image_filename = secure_filename(file.filename)
    image.save('images/' + encoded_image_filename)
    last_encoded_image = encoded_image_filename

    # Render the decode.html template with the decoded message and image
    return render_template('decode.html', last_decoded_message=decoded_message,
                           encoded_image_url='images/' + encoded_image_filename)


@app.route('/image/last/decoded')
def get_last_decoded_message():
    global last_decoded_message
    if last_decoded_message is not None:
        return last_decoded_message
    else:
        return 'No last decoded message found.'


if __name__ == '__main__':
    app.run(debug=True)
