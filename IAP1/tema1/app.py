from flask import Flask, render_template, request, send_file
from werkzeug.utils import secure_filename
from PIL import Image

app = Flask(__name__)

# Variable to store the last encoded image and decoded message
last_encoded_image = None
last_decoded_message = None

def encode_message(image, message):
    width, height = image.size
    pixel_values = list(image.getdata())

    binary_message = ''.join(format(ord(char), '08b') for char in message)
    message_length = len(binary_message)

    if message_length > width * height:
        raise ValueError('Image size is too small to encode the message.')

    encoded_pixels = []
    encoded_pixels.extend(pixel_values)

    for i in range(message_length):
        pixel = pixel_values[i]
        red = pixel[0]
        green = pixel[1]
        blue = pixel[2]
        encoded_red = red & 0xFC | int(binary_message[i], 2)
        encoded_pixel = (encoded_red, green, blue)
        encoded_pixels[i] = encoded_pixel

    encoded_image = Image.new('RGB', (width, height))
    encoded_image.putdata(encoded_pixels)

    return encoded_image

def decode_message(image):
    pixel_values = list(image.getdata())

    binary_message = ''

    for pixel in pixel_values:
        red = pixel[0]
        binary_message += str(red & 0x03)

    decoded_message = ''
    for i in range(0, len(binary_message), 8):
        byte = binary_message[i:i + 8]
        decoded_message += chr(int(byte, 2))

    return decoded_message

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/image/encode', methods=['POST'])
def encode_image():
    global last_encoded_image, last_decoded_message

    # Get the uploaded file and message from the request
    file = request.files['file']
    message = request.form['message']

    # Open the image file
    image = Image.open(file)

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
    global last_encoded_image
    if last_encoded_image is not None:
        return send_file('images/' + last_encoded_image, as_attachment=True)
    else:
        return 'No last encoded image found.'

@app.route('/image/decode', methods=['POST'])
def decode_image():
    global last_decoded_message

    # Get the uploaded encoded image from the request
    file = request.files['file']

    # Open the image file
    image = Image.open(file)

    try:
        # Perform steganography decoding
        decoded_message = decode_message(image)

        # Update the last decoded message variable
        last_decoded_message = decoded_message

        # Return the decoded message (can be HTML or plain text)
        return render_template('decode.html', last_decoded_message=last_decoded_message)
    except:
        return 'Failed to decode the image.'

@app.route('/image/last/decoded')
def get_last_decoded_message():
    global last_decoded_message
    if last_decoded_message is not None:
        return last_decoded_message
    else:
        return 'No last decoded message found.'

if __name__ == '__main__':
    app.run()