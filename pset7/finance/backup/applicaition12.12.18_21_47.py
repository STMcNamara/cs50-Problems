import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, posint

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Collate stock info
    stocklist = db.execute("SELECT symbol, sum(trans) FROM transactions WHERE id = :id GROUP BY symbol", id=session["user_id"])

    for i in stocklist:
        current_quote = lookup(i["symbol"])
        i["company_name"] = current_quote["name"]
        i["current_price"] = current_quote["price"]
        i["value"] = i["sum(trans)"] * i["current_price"]
        i["usd"] = usd(i["value"])

    # Collate simple information
    user = db.execute("SELECT username FROM users WHERE id = :id", id=session["user_id"])[0]["username"]
    cash_balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
    share_total = 0.0
    for i in stocklist:
        share_total += i["value"]
    grand_total = cash_balance + share_total

    # Return index.html:
    return render_template("index.html", user=user, cash_balance=usd(cash_balance), grand_total=usd(grand_total), stocklist=stocklist)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check for a postive integer of shares
        trans_shares = request.form.get("shares")
        if not posint(trans_shares):
            return apology("Positive whole shares only")

        # Lookup the submitted code
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Invalid company code")

        # Check the user can afford the purchase
        balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
        trans_price = quote["price"] * int(trans_shares)
        if trans_price > balance:
            return apology("Insuffient funds")

        # Log the transaction in the database
        db.execute("INSERT INTO transactions (id, symbol, trans, price) VALUES(:id, :symbol, :trans, :price)",
                   id=session["user_id"], symbol=quote["symbol"], trans=trans_shares, price=quote["price"])

        # Update the users cash
        db.execute("UPDATE users SET cash = cash - :trans_price WHERE id = :id", trans_price=trans_price, id=session["user_id"])

        # Redirect the user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Collate stock info
    transactions = db.execute("SELECT symbol, trans, price, trans_date FROM transactions WHERE id = :id ", id=session["user_id"])

    for i in transactions:
        current_quote = lookup(i["symbol"])
        i["company_name"] = current_quote["name"]
        if i["trans"] > 0:
            i["type"] = "Bought"
        else:
            i["type"] = "Sold"
        i["value"] = i["trans"] * i["price"]
        i["price"] = usd(i["price"])

    # Collate simple information
    user = db.execute("SELECT username FROM users WHERE id = :id", id=session["user_id"])[0]["username"]

    # Return history.html:
    return render_template("history.html", user=user, transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST) - quoted template
    if request.method == "POST":

        # Lookup the submitted code
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Invalid company code")

        # Return quoted template and pass in values
        return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=usd(quote["price"]))

    # User reached route via GET (as by clicking a link or via redirect) - quote template
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        # Hash the password and create temporary variables
        hash = generate_password_hash(request.form.get("password"))

        # Add user name and password hash to the database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username=request.form.get("username"), hash=hash)
        if not result:
            return apology("User already exists")

        # Keep the user logged in
        session["user_id"] = result

        # Redirect the user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check for a postive integer of shares
        trans_shares = request.form.get("shares")
        if not posint(trans_shares):
            return apology("Positive whole shares only")

        # Lookup the submitted code
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Invalid company code")

        # Check that the user owns sufficient shares
        stock_no = db.execute("SELECT sum(trans) FROM transactions WHERE id = :id AND symbol = :symbol",
                              id=session["user_id"], symbol=quote["symbol"])[0]["sum(trans)"]

        if not stock_no:
            return apology("No shares owned")

        if stock_no < int(trans_shares):
            return apology("Insuffient shares owned")

        # Log the transaction in the database
        db.execute("INSERT INTO transactions (id, symbol, trans, price) VALUES(:id, :symbol, :trans, :price)",
                   id=session["user_id"], symbol=quote["symbol"], trans=-int(trans_shares), price=quote["price"])

        # Update the users cash
        trans_price = quote["price"] * int(trans_shares)
        db.execute("UPDATE users SET cash = cash + :trans_price WHERE id = :id", trans_price=trans_price, id=session["user_id"])

        # Redirect the user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Generate list of owned shares
        stock_list = db.execute("SELECT DISTINCT symbol FROM transactions WHERE id = :id", id=session["user_id"])

        return render_template("sell.html", stock_list=stock_list)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
