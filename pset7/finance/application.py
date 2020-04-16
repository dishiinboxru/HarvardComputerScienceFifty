import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, lookupPrice, lookupFullName

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
app.jinja_env.filters["lookupPrice"] = lookupPrice
app.jinja_env.filters["lookupFullName"] = lookupFullName

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

    user_id = session['user_id']

    rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

    # get total cash
    cashAvailable = rows[0]["cash"]

    # get username by user id
    username = rows[0]["username"]

    # getting grandTotal
    grandTotal = 0

    # requesting user protfolio
    rows = db.execute("SELECT * from portfolio WHERE username = :username ", username=username)
    entries = len(rows)
    for i in range(0, entries):
        increment = rows[i]["number_of_stocks"] * lookupPrice(rows[i]["company_name"])
        grandTotal += increment

    grandTotal += cashAvailable

    return render_template("/index.html", rows=rows , cashAvailable=cashAvailable , grandTotal = grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide company symbol", 400)

        if lookup(request.form.get("symbol")) is None:
            return apology("company symbol is incorrect", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares of stocks", 400)

        # Ensure it's not negative
        elif int(request.form.get("shares")) <= 0:
            return apology("shares of stocks must be positive int ", 400)

        # Ensure it's not float or string
        elif not int(request.form.get("shares")):
            return apology("shares of stocks must be integer, not float or string ", 400)


        looked_up = lookup(request.form.get("symbol"))
        user_id = session['user_id']

        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

        cashAvailable = rows[0]["cash"]
        totalPrice = looked_up.get("price") * int(request.form.get("shares"))

        # ensure there's enough money
        if cashAvailable < totalPrice:
            return apology("insufficient funds ", 400)

        # get username by user id
        username = rows[0]["username"]


        # insert into transactions
        rows = db.execute("INSERT INTO transactions (username,transaction_type, company_name, price, number_of_stocks ) VALUES (:username, 'buy' ,:symbol ,:price , :shares )", username = username, symbol = request.form.get("symbol"), price =looked_up.get("price"),  shares = request.form.get("shares") )

        # insert into portfolio - should be some verification first in order to route increments in a specific place

        rows= db.execute ("SELECT * from portfolio WHERE (username = :username AND company_name = :symbol)" , symbol = request.form.get("symbol"), username = username)
        if len(rows) == 1:
            rows = db.execute("UPDATE portfolio SET number_of_stocks = number_of_stocks + :shares WHERE (username = :username AND company_name = :symbol)" , symbol = request.form.get("symbol"), username = username , shares =request.form.get("shares") )
        else:
            rows = db.execute("INSERT INTO portfolio (username, company_name, number_of_stocks ) VALUES (:username, :symbol ,:shares )", symbol = request.form.get("symbol"), username = username, shares =request.form.get("shares") )

        # manipulations with cash in main table
        rows = db.execute("UPDATE users SET cash = cash - :price WHERE id = :user_id" , user_id =user_id, price = totalPrice )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/buy.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """SELL shares of stock"""

    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide company symbol", 400)

        if lookup(request.form.get("symbol")) is None:
            return apology("company symbol is incorrect", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares of stocks", 400)

        elif int(request.form.get("shares")) <= 0:
            return apology("shares of stocks must be positive int ", 400)

        looked_up = lookup(request.form.get("symbol"))
        user_id = session['user_id']

        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

        cashAvailable = rows[0]["cash"]
        totalPrice = looked_up.get("price") * int(request.form.get("shares"))

        # get username by user id
        username = rows[0]["username"]

        # verifications should go prior to inserts !
        rows= db.execute("SELECT * from portfolio WHERE (username = :username AND company_name = :symbol)" , symbol = request.form.get("symbol"), username = username)
        # verify stocks are present
        if len(rows) != 1:
            return apology("Sorry, you don't have that company's stocks ", 400)
        # verify their shares is not below selling shares
        if rows[0]["number_of_stocks"] < int(request.form.get("shares")):
             return apology("Sorry, you don't have that many stocks ", 400)
        # update portfolio if everything is fine
        else :
            # removing entry if person sells all stocks he owns , example - DELETE FROM Customers WHERE CustomerName='Alfreds Futterkiste';
            if rows[0]["number_of_stocks"] == int(request.form.get("shares")):
                rows = db.execute("DELETE FROM portfolio WHERE (username = :username AND company_name = :symbol)" , symbol = request.form.get("symbol"), username = username)
            else:
                rows = db.execute("UPDATE portfolio SET number_of_stocks = number_of_stocks - :shares WHERE (username = :username AND company_name = :symbol)" , symbol = request.form.get("symbol"), username = username , shares =request.form.get("shares") )

        # manipulations with cash in main table
        rows = db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id" , user_id =user_id, price = totalPrice )

        # insert into transactions
        rows = db.execute("INSERT INTO transactions (username,transaction_type, company_name, price, number_of_stocks ) VALUES (:username, 'sell' ,:symbol ,:price , :shares )", username = username, symbol = request.form.get("symbol"), price =looked_up.get("price"),  shares = request.form.get("shares") )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/sell.html")


@app.route("/history", methods=["GET"])
@login_required
def history():
    if request.method == "GET":

        #getting the user name
        user_id = session['user_id']
        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)
        username = rows[0]["username"]

        # select into transactions
        rows = db.execute("SELECT * FROM transactions WHERE (username = :username)", username = username)


        return render_template("/history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


def isPasswordStrong(p):
    # checking if password is strong enough
    x = True
    while x:
        if (len(p) < 6 or len(p) > 12):
            break
        elif not re.search("[a-z]", p):
            break
        elif not re.search("[0-9]", p):
            break
        elif not re.search("[A-Z]", p):
            break
        elif not re.search("[$#@]", p):
            break
        elif re.search("\s", p):
            break
        else:
            return True
    if x:
        return False


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
    if request.method == "POST":
        looked_up = lookup(request.form.get("symbol"))

        if lookup(request.form.get("symbol")) is None:
            return apology("company symbol is incorrect", 400)

        price = looked_up.get("price")
        name = looked_up.get("name")
        symbol = looked_up.get("symbol")
        return render_template("quoted.html", name=name, price=usd(price), symbol=symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was verified
        elif not request.form.get("confirmation"):
            return apology("must verify password", 400)

        # Ensure password was verified correctly
        elif not request.form.get("confirmation")== request.form.get("password"):
            return apology("must re-enter the password", 400)
        # # looks like password verification is too strong for autochecks, disable it temporarily
        # elif not isPasswordStrong(request.form.get("password")):
        #     # return apology("password should have at least 1 letter between [a-z] and 1 letter between [A-Z], 1 number between [0-9], 1 character from [$#@] and between 6 and 16 characters.", 400)
        #     return apology("password should be strong ", 400)


        # Query Db to Ensure username is unique
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists, sorry. Try another one", 400)

        # insert into  database for username  TODO - hashing the [password] + veryfying no duplicated users
        rows = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash = generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


# @app.route("/sell", methods=["GET", "POST"])
# @login_required
# def sell():
#     """Sell shares of stock"""
#     return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
