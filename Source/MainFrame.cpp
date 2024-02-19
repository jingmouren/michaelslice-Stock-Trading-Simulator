
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/regex.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <wx/spinctrl.h>
#include <sstream>
#include <iomanip>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    // Add stock button
    wxPanel* panel = new wxPanel(this);
    wxButton* add_stock_button = new wxButton(panel, wxID_ANY, "Add Ticker", wxPoint(520, 400), wxSize(120, 25));
    add_stock_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Text for Watchlist
    wxStaticText* watchlist_text = new wxStaticText(panel, wxID_ANY, "Watchlist", wxPoint(420, 50));
    wxFont watchlist_text_font(wxFontInfo(18).Bold());
    watchlist_text->SetFont(watchlist_text_font);

    // Text for Trading Simulator

    wxStaticText* trading_simulator_text = new wxStaticText(panel, wxID_ANY, "Trading Simulator", wxPoint(10, 10));
    wxFont trading_simulator_text_font(wxFontInfo(18).Bold());
    trading_simulator_text->SetFont(trading_simulator_text_font);

    // Text for Portfolio Balance

    wxStaticText* portfolio_balance_text = new wxStaticText(panel, wxID_ANY, "Portfolio Balance:", wxPoint(10, 100));
    wxFont portfolio_balance_text_font(wxFontInfo(10));
    portfolio_balance_text->SetFont(portfolio_balance_text_font);

    // Text for Portfolio Book Value

    wxStaticText* portfolio_value_text = new wxStaticText(panel, wxID_ANY, "Portfolio Book Value:", wxPoint(10, 140));
    wxFont portfolio_value_text_font(wxFontInfo(10));
    portfolio_balance_text->SetFont(portfolio_value_text_font);

    // Text for Profit / Loss

    wxStaticText* profit_loss_text = new wxStaticText(panel, wxID_ANY, "Profit/(Loss)", wxPoint(10, 180));
    wxFont profit_loss_text_font(wxFontInfo(10));
    profit_loss_text->SetFont(profit_loss_text_font);

    // Text for Funds Available

    wxStaticText* funds_available_text = new wxStaticText(panel, wxID_ANY, "Funds Available:", wxPoint(10, 280));
    wxFont funds_available_text_font(wxFontInfo(10));
    funds_available_text->SetFont(funds_available_text_font);

    // Text for Add/Withdraw Funds

    wxStaticText* add_withdraw_funds_text = new wxStaticText(panel, wxID_ANY, "Add/(Withdraw) Funds", wxPoint(10, 320));
    wxFont add_withdraw_funds_text_font(wxFontInfo(10));
    add_withdraw_funds_text->SetFont(add_withdraw_funds_text_font);

    // Request Funds Button

    wxButton* request_funds_button = new wxButton(panel, wxID_ANY, "Request Funds", wxPoint(10, 358), wxSize(120, 25));
    request_funds_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Input Frame for Adding Funds

    adding_withdrawing_funds_frame = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(160, 320), wxSize(70, 20), wxTE_PROCESS_ENTER);

    // Bind the Adding Withdrawing Funds Frame to the Enter Key 

    adding_withdrawing_funds_frame->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnEnterPressed, this);

    // Input Frame for Adding a Ticker Symbol

    adding_ticker_frame = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(380, 400), wxSize(100, 20), wxTE_PROCESS_ENTER);

    // Bind the Input Frame for Adding a Ticker Symbol 

    adding_ticker_frame->Bind(wxEVT_TEXT_ENTER, &MainFrame::AddingSellingTickers, this);

    // Button for Updating Data Table

    wxButton* update_button = new wxButton(panel, wxID_ANY, "Update", wxPoint(720, 400), wxSize(100, 25));
    update_button->SetBackgroundColour(*wxLIGHT_GREY);

    update_button->Bind(wxEVT_BUTTON, &MainFrame::OnUpdateButton, this);

    // Scroll Bar for Data Table

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxPoint(250, 80), wxSize(450, 300));
    scrolledWindow->SetScrollRate(10, 10); // Set the scrolling increment

    // Data Table for Ticker Data
    basicListView = new wxListView(scrolledWindow, wxID_ANY, wxPoint(0, 0), wxSize(450, 300));

    // Enable vertical scrolling
    scrolledWindow->SetScrollbars(0, 10, 0, 100);

    // Append columns and set column labels
    basicListView->AppendColumn("", wxLIST_FORMAT_LEFT, 80);
    basicListView->AppendColumn("Ticker", wxLIST_FORMAT_LEFT, 120);
    basicListView->AppendColumn("Market Value", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Avg. Price", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Shares Held", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Avg. P/L", wxLIST_FORMAT_LEFT, 600);


    // Set the width of the first column
    basicListView->SetColumnWidth(0, 40);
    // Set the width of the second column
    basicListView->SetColumnWidth(1, 80);
    // Set the width of the third column
    basicListView->SetColumnWidth(2, 90);
    // Set the width of the third column
    basicListView->SetColumnWidth(3, 80);
    // Set the width of the third column
    basicListView->SetColumnWidth(4, 80);
    // Set the width of the third column
    basicListView->SetColumnWidth(5, 80);

    // Text for buying more shares

    wxStaticText* stock_quantity_text = new wxStaticText(panel, wxID_ANY, "Ticker", wxPoint(750, 150));
    wxFont stock_quantity_text_font(wxFontInfo(10));
    stock_quantity_text->SetFont(stock_quantity_text_font);

    // Input Frame For Buying / Selling Shares

    wxTextCtrl* stock_frame = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(730, 170), wxSize(80, 20));

    // Text for Quantity

    wxStaticText* quantity_text = new wxStaticText(panel, wxID_ANY, "Quantity", wxPoint(750, 200));
    wxFont quantity_text_font(wxFontInfo(10));
    quantity_text->SetFont(stock_quantity_text_font);

    // Input Frame for Buying / Selling Shares

    stock_quantity = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(730, 220), wxSize(80, 20));

    // Button for Buying Shares

    buy_button = new wxButton(panel, wxID_ANY, "Sell", wxPoint(730, 270), wxSize(80, 25));
    buy_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Sell button

    sell_button = new wxButton(panel, wxID_ANY, "Buy", wxPoint(730, 320), wxSize(80, 25));
    sell_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Text for Funds Available

    funds_available = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 280), wxSize(70, 20));


    // Text For Profit Loss

    profit_loss = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 180), wxSize(70, 20));

    // Text For Portfolio Book Value

    portfolio_book_value = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 140), wxSize(70, 20));

    // Text For Portfolio Balance

    portfolio_balance = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 100), wxSize(70, 20));

    // Load Previus Inputed Ticker Data from data.txt

    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string ticker;
        while (std::getline(file, ticker)) {
            wxString tickerWx(ticker);
            long index = basicListView->InsertItem(basicListView->GetItemCount(), "");
            basicListView->SetItem(index, 1, tickerWx);
            basicListView->SetItem(index, 4, "1"); // Set "Shares Held" column to 1 for each stock
        }
        file.close();
    }
    else
    {
        wxMessageBox("Unable to open data file.", "Error", wxOK | wxICON_ERROR);
    }

    // Retrieve Saved Funds and Display 

    LoadDataFromFile();
    LoadStockPricesFromFile();

}


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
{

}

// Function to Add and Withdraw Funds

void MainFrame::OnEnterPressed(wxCommandEvent& event)
{
    wxString input = adding_withdrawing_funds_frame->GetValue();
    adding_withdrawing_funds_frame->Clear();

    // Check if User Input is a Number
    double value;
    if (!input.ToDouble(&value) && input != "-")
    {
        wxMessageBox("Invalid input. Please enter a number.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Retrieve Previous Data From Labels and Convert to Long Integers
    double bookval = wxAtoi(portfolio_balance->GetLabel());
    double fundsAva = wxAtoi(portfolio_book_value->GetLabel());
    double mktVal = wxAtoi(funds_available->GetLabel());

    if (input == "-")
    {
        // Subtract the Value From all Three Variables
        bookval -= value;
        fundsAva -= value;
        mktVal -= value;
    }
    else
    {
        // Add the Value to All Three Variables
        bookval += value;
        fundsAva += value;
        mktVal += value;
    }

    // Update the Labels With the New Values
    portfolio_balance->SetLabel(wxString::Format("%.2f", bookval));
    portfolio_book_value->SetLabel(wxString::Format("%.2f", fundsAva));
    funds_available->SetLabel(wxString::Format("%.2f", mktVal));

    // Save the Variables to the Data File
    std::ofstream file("savedata.txt");
    if (file.is_open())
    {
        file << std::fixed << std::setprecision(2) << bookval << '\n';
        file << std::fixed << std::setprecision(2) << fundsAva << '\n';
        file << std::fixed << std::setprecision(2) << mktVal << '\n';
        file.close();
    }
    else
    {
        wxMessageBox("Unable to save data to file.", "Error", wxOK | wxICON_ERROR);
    }

    event.Skip();
}

// Code and Logic for Adding and Selling Tickers

void MainFrame::AddingSellingTickers(wxCommandEvent& event)
{
    wxString ticker = adding_ticker_frame->GetValue();
    adding_ticker_frame->Clear();

    wxString tickerLettersOnly;
    for (size_t i = 0; i < ticker.length(); ++i)
    {
        wxChar ch = ticker[i];
        if (wxIsalpha(ch))
        {
            tickerLettersOnly += ch;
        }
    }

    tickerLettersOnly.Truncate(4);

    if (tickerLettersOnly.empty())
    {
        wxMessageBox("Invalid input! Please enter a valid ticker consisting of letters only.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString tickerUppercase = tickerLettersOnly.MakeUpper();

    int itemcount = basicListView->GetItemCount();
    for (int i = 0; i < itemcount; ++i)
    {
        wxString existingTicker = basicListView->GetItemText(i, 1);
        if (existingTicker == tickerUppercase)
        {
            wxMessageBox("Duplicate ticker! Ticker already exists.", "Error", wxOK | wxICON_ERROR);
            return;
        }
    }

    long index = basicListView->InsertItem(basicListView->GetItemCount(), "");
    basicListView->SetItem(index, 1, tickerLettersOnly);
    basicListView->SetItem(index, 4, "1"); // Set "1" in the "Shares Held" column

    // Check if the Stock Price is Already Saved
    double price = 0.0;
    bool priceFound = false;

    std::ifstream file("data.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string tickerSaved;
            std::string priceSavedStr;
            if (iss >> tickerSaved >> priceSavedStr)
            {
                // Convert priceSavedStr to double
                double priceSaved = std::stod(priceSavedStr);

                if (tickerSaved == tickerUppercase)
                {
                    price = priceSaved;
                    priceFound = true;
                    break;
                }
            }
        }
        file.close();

    }
    else
    {
        wxMessageBox("Unable to read stock prices from file.", "Error", wxOK | wxICON_ERROR);
    }

    // If the Price is not Found, Retrieve it Using the Python script
    if (!priceFound)
    {
        // Call the Python script to retrieve stock price
        wxString pythonCommand = "python -c \"import yfinance; ticker = '" + tickerUppercase + "'; data = yfinance.Ticker(ticker).history(period='1d'); price = data['Close'].values[-1]; print(price)\"";

        wxArrayString output;
        wxExecute(pythonCommand, output);

        // Check if the Python Command was Successful and Capture the Result
        wxString result;
        if (!output.IsEmpty())
        {
            result = output[0]; // Assuming the output is stored in the first element of the array
            price = wxAtof(result);
            double mktVal = wxAtof(funds_available->GetLabel());
            mktVal -= price;

            funds_available->SetLabel(wxString::Format("%.2f", mktVal)); // Update the label

            std::ifstream inputFile("savedata.txt");
            std::ofstream outputFile("temp.txt");

            if (inputFile.is_open() && outputFile.is_open())
            {
                std::string line;
                int lineNumber = 0;

                while (std::getline(inputFile, line))
                {
                    if (lineNumber == 2)
                    {
                        // Replace the old funds available value with the new one
                        outputFile << std::fixed << std::setprecision(2) << mktVal << '\n';
                    }
                    else
                    {
                        outputFile << line << '\n';
                    }

                    lineNumber++;
                }

                inputFile.close();
                outputFile.close();

                // Replace the original file with the updated file
                std::remove("savedata.txt");
                std::rename("temp.txt", "savedata.txt");
            }
            else
            {
                wxMessageBox("Unable to update funds available in the file.", "Error", wxOK | wxICON_ERROR);
            }

            // Save the stock price to the file
            std::ofstream saveFile("data.txt", std::ios::app);
            if (saveFile.is_open())
            {
                saveFile << tickerUppercase << '\n';
                saveFile.close();
            }
            else
            {
                wxMessageBox("Unable to save stock price to file.", "Error", wxOK | wxICON_ERROR);
            }
        }

        // Round the result to two decimal places
        wxString formattedPrice = wxString::Format("%.2f", price);

        // Update the stock price in the ListView
        basicListView->SetItem(index, 3, formattedPrice);
        basicListView->SetItem(index, 2, wxString::Format("%.2f", price));

        // Save The User Input When Tickers Are Added
        std::ofstream file("stockprices.txt", std::ios::app);
        if (file.is_open())
        {
            file << formattedPrice << '\n';
            file.close();
        }
        else
        {
            wxMessageBox("Unable to save ticker to file.", "Error", wxOK | wxICON_ERROR);
        }
    }
}

// Retrieve Input for Funds from savedata.txt this is the money code

void MainFrame::LoadDataFromFile()
{
    std::ifstream file("savedata.txt");
    if (file.is_open())
    {
        std::string line;
        int lineNumber = 0;

        while (std::getline(file, line))
        {
            if (lineNumber == 0)
            {
                double bookval = std::stol(line);
                portfolio_balance->SetLabel(wxString::Format("%.2f", bookval));
            }
            else if (lineNumber == 1)
            {
                double fundsAva = std::stol(line);
                portfolio_book_value->SetLabel(wxString::Format("%.2f", fundsAva));
            }
            else if (lineNumber == 2)
            {
                double  mktVal = std::stol(line);
                funds_available->SetLabel(wxString::Format("%.2f", mktVal));
            }

            lineNumber++;
        }

        file.close();
    }
    else
    {
        wxMessageBox("Unable to load data from file.", "Error", wxOK | wxICON_ERROR);
    }
}

// Code for loading the Stock Prices From the Portfolio in stockprices.txt

void MainFrame::LoadStockPricesFromFile()
{
    std::ifstream file("stockprices.txt");
    if (file.is_open())
    {
        std::string line;
        int index = 0;
        while (std::getline(file, line))
        {
            wxString price = wxString::FromUTF8(line.c_str());
            basicListView->SetItem(index, 3, price);
            index++;
        }
        file.close();
    }
    else
    {
        wxMessageBox("Unable to open stockprices.txt file.", "Error", wxOK | wxICON_ERROR);
    }
}

// Code for Updating the Market Value Column in the Data table

void MainFrame::OnUpdateButton(wxCommandEvent& event)
{
    // Update the market value column with the most recent stock prices
    int itemCount = basicListView->GetItemCount();
    for (int i = 0; i < itemCount; ++i)
    {
        wxString ticker = basicListView->GetItemText(i, 1);
        wxString priceStr;

        // Check if the stock price is already saved
        bool priceFound = false;
        std::ifstream priceFile("data.txt");
        if (priceFile.is_open())
        {
            std::string line;
            while (std::getline(priceFile, line))
            {
                std::istringstream iss(line);
                std::string tickerSaved;
                std::string priceSavedStr;
                if (iss >> tickerSaved >> priceSavedStr)
                {
                    if (tickerSaved == ticker)
                    {
                        priceStr = priceSavedStr;
                        priceFound = true;
                        break;
                    }
                }
            }
            priceFile.close();
        }
        else
        {
            wxMessageBox("Unable to read stock prices from file.", "Error", wxOK | wxICON_ERROR);
        }

        // If the price is not found, retrieve it using the Python script
        if (!priceFound)
        {
            // Call the Python script to retrieve stock price
            wxString pythonCommand = "python -c \"import yfinance; ticker = '" + ticker
                + "'; data = yfinance.Ticker(ticker).history(period='1d');"
                " price = data['Close'].values[-1]; print(price)\"";

            wxArrayString output;
            wxExecute(pythonCommand, output);

            // Check if the Python command was successful and capture the result
            wxString result;
            if (!output.IsEmpty())
            {
                result = output[0]; // Assuming the output is stored in the first element of the array
                double price = wxAtof(result);

                // Update the stock price in the ListView

                basicListView->SetItem(i, 2, wxString::Format("%.2f", price));


                // Update the market value column with the most recent stock prices
                int itemCount = basicListView->GetItemCount();
                double totalProfitLoss = 0.0;

                for (int i = 0; i < itemCount; ++i)
                {
                    wxString ticker = basicListView->GetItemText(i, 1);
                    wxString avgPriceStr = basicListView->GetItemText(i, 3);
                    wxString currentPriceStr = basicListView->GetItemText(i, 2);
                    wxString quantityStr = basicListView->GetItemText(i, 4);

                    double avgPrice = wxAtof(avgPriceStr);
                    double currentPrice = wxAtof(currentPriceStr);
                    int quantity = wxAtoi(quantityStr);

                   
                    double marketValue = currentPrice * quantity;

                    // Calculate the profit/loss
                    double profitLoss = marketValue - avgPrice;

                   
                    basicListView->SetItem(i, 5, wxString::Format("%.2f", profitLoss));

                    // Add the profit/loss value to the total
                    totalProfitLoss += profitLoss;

                   
                    profit_loss->SetLabel(wxString::Format("%.2f", totalProfitLoss));

                }
                // Get the current portfolio balance
                double currentPortfolioBalance = wxAtof(portfolio_balance->GetLabel());

                // Update the portfolio balance by adding the sum of the profit/loss column
                double updatedPortfolioBalance = currentPortfolioBalance + totalProfitLoss;

                // Update the portfolio_balance text with the updated portfolio balance
                portfolio_balance->SetLabel(wxString::Format("%.2f", updatedPortfolioBalance));
            }
        }
    }



    event.Skip();
}