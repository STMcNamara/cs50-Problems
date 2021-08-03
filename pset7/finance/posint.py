import os
from cs50 import get_string

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Define function
def posint(value):
    """Return True if value is a positive integer, False otherwise"""

    # Test if value is an int
    try:
        val = int(value)

        # Check if positve
        if val > 0:
            return True
        else:
            return False

    except ValueError:
        return False


# Request code from user
code = get_string("Enter an int: ")

# Call and print the function
print(posint(code))