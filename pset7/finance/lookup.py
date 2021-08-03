import os
from cs50 import get_string

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Request code from user
code = get_string("Enter company code: ")

# Get info from the api
info = lookup(code)

# If not valid, return error message
print(info["name"])
print(info["price"])

# If valid, return values
