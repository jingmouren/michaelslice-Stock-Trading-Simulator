
import numpy as np
import yfinance as yf
import datetime as dt
from pandas_datareader import data as pdr

# Read stock names from text file
with open('data.txt', 'r') as file:
    stocks = file.read().splitlines()

# Retrieve stock prices and update file
with open('stockprices.txt', 'r+') as file:
    lines = file.readlines()
    file.seek(0)  # Move the file pointer to the beginning of the file

    for line in lines:
        stock = line.strip()
        ticker = yf.Ticker(stock)
        latest_price = ticker.history().tail(1)['Close'].values[0]

        updated_line = line.strip() + ',' + str(latest_price) + '\n'
        file.write(updated_line)

    file.truncate()  # Remove any remaining lines from the previous version of the file
    