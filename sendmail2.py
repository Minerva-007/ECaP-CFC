from __future__ import print_function

import os.path
from google.oauth2.credentials import Credentials
import base64
from email.message import EmailMessage
from email.mime.text import MIMEText

import google.auth
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

SCOPES = ['https://www.googleapis.com/auth/gmail.send']

def gmail_send_message():
    """Create and send an email message
    Print the returned  message id
    Returns: Message object, including message id

    Load pre-authorized user credentials from the environment.
    TODO(developer) - See https://developers.google.com/identity
    for guides on implementing OAuth2 for the application.
    """
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)

    try:
        service = build('gmail', 'v1', credentials=creds)
        message = EmailMessage();
        f = open("output.txt","r")
        email = f.readline()
        f = open("content.txt","r")
        texto = f.read()
        message.set_content(texto, cte='7bit')

        message['To'] = email.strip()
        message['From'] = 'ecapuet23@gmail.com'
        message['Subject'] = 'Carbon Footprint Results - ECAP 2023'
        f = open('image.png','rb')
        picdata = f.read()
        message.add_attachment(picdata,maintype='application',subtype='image/png',filename='image.png')

        # encoded message
        encoded_message = base64.urlsafe_b64encode(message.as_bytes()) \
            .decode()

        create_message = {
            'raw': encoded_message
        }
        # pylint: disable=E1101
        send_message = (service.users().messages().send
                        (userId="me", body=create_message).execute())
        print(F'Message Id: {send_message["id"]}')
    except HttpError as error:
        print(F'An error occurred: {error}')
        send_message = None
    return send_message


if __name__ == '__main__':
    gmail_send_message()

