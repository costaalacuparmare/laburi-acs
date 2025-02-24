#!/usr/bin/python3

import imaplib
import smtplib
import email
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import decode_header
import time

# Conf
SERVER = "milano"
IMAP_PORT = 993
SMTP_PORT = 25
USER = "support"
PASSWORD = "Pierdut$Cont1337"

# Counter for IDs
TICKER_NUMBER = 1


def open_imap():
    mail = imaplib.IMAP4_SSL(SERVER, IMAP_PORT)
    mail.login(USER, PASSWORD)
    return mail


def get_support_emails(mail):
    mail.select("inbox")
    status, messages = mail.search(None, '(SUBJECT "Support Ticket")')
    if status != "OK":
        print("No messages found")
        return []
    messages = messages[0].split()
    emails = []
    for mail_id in messages:
        status, data = mail.fetch(mail_id, "(RFC822)")
        if status != "OK":
            print("Error fetching mail")
            continue
        msg = email.message_from_bytes(data[0][1])
        emails.append(msg)
    return emails


def send_reply(sender, subject, ticket_id):
    msg = MIMEMultipart()
    msg["From"] = USER
    msg["To"] = sender
    msg["Subject"] = f"Re: {subject}"
    body = (f"Hi,\n\nYour ticket named '{subject}' was registered as "
            f"#{ticket_id}.\n\nThank you for your patience!")
    msg.attach(MIMEText(body, "plain"))
    with smtplib.SMTP(SERVER, SMTP_PORT) as server:
        server.sendmail(USER, sender, msg.as_string())


def main():
    global TICKER_NUMBER
    mail_imap = open_imap()
    email = get_support_emails(mail_imap)
    for msg in email:
        subject = msg['Subject']
        sender = msg['From']
        send_reply(sender, subject, TICKER_NUMBER)
        TICKER_NUMBER += 1
    mail_imap.logout()


if __name__ == "__main__":
    main()
