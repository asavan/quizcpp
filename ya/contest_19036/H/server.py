# https://yandex.ru/cup/backend/analysis/

import json
import logging
import re
import sys
import urllib.parse
from http.server import HTTPServer, BaseHTTPRequestHandler
from typing import NamedTuple, List, Tuple

log = logging.getLogger(__name__)
log.setLevel(logging.INFO)
log.addHandler(logging.FileHandler('solution.log'))


class PhoneParser:
    PHONE_CODES = [982, 986, 912, 934]
    REGEXP = [
        re.compile(r'^\+7 (\d{3}) (\d{3}) (\d{2})(\d{2})$'),
        re.compile(r'^\+7 (\d{3}) (\d{3}) (\d{2}) (\d{2})$'),
        re.compile(r'^\+7 \((\d{3})\) (\d{3})-(\d{2})(\d{2})$'),
        re.compile(r'^\+7(\d{3})(\d{3})(\d{2})(\d{2})$'),
        re.compile(r'^8 (\d{3}) (\d{3}) (\d{2})(\d{2})$'),
        re.compile(r'^8 (\d{3}) (\d{3}) (\d{2}) (\d{2})$'),
        re.compile(r'^8 \((\d{3})\) (\d{3})-(\d{2})(\d{2})$'),
        re.compile(r'^8(\d{3})(\d{3})(\d{2})(\d{2})$'),
    ]

    def __init__(self, raw):
        self.raw = raw

    def parse(self):
        m = self.match()
        if not m:
            log.info('could not match')
            return ''

        code, *parts = m.groups()
        if int(code) not in self.PHONE_CODES:
            log.info('did not match code')
            return ''

        return f'+7-{code}-{parts[0]}-{parts[1]}{parts[2]}'

    def match(self):
        for pattern in self.REGEXP:
            m = pattern.match(self.raw)
            log.info(f'result matching: raw={self.raw} pattern={pattern}, m={m}')
            if m:
                return m


class Response(NamedTuple):
    code: int
    headers: List[Tuple[str, str]]
    message: str


class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        query = urllib.parse.urlparse(self.path)
        log.info('query: %s', query)
        if query.path == '/ping':
            response = ping()
        elif query.path == '/shutdown':
            sys.exit()
        else:
            response = validate(query)

        self.send_response(response.code)
        for name, value in response.headers:
            self.send_header(name, value)
        self.end_headers()

        self.wfile.write(response.message.encode())


def ping():
    return Response(200, [], '')


def validate(query: urllib.parse.ParseResult) -> Response:
    if query.path != '/validatePhoneNumber':
        return Response(404, [], '')

    phone_number = urllib.parse.parse_qs(query.query).get('phone_number')
    if phone_number is None or len(phone_number) != 1:
        return Response(400, [], '')

    log.info('phone_number: %s', phone_number)
    headers = [('Content-Type', 'application/json')]

    normalized = PhoneParser(phone_number[0]).parse()
    if normalized:
        result = {'status': True, 'normalized': normalized}
    else:
        result = {'status': False}

    return Response(200, headers, json.dumps(result))


server = HTTPServer(('127.0.0.1', 7777), Handler)
server.serve_forever()
