
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/listctrl.h>



MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

    // Add stock button
    wxPanel* panel = new wxPanel(this);
    wxButton* add_stock_button = new wxButton(panel, wxID_ANY, "Add Ticker", wxPoint(520, 400), wxSize(120, 25));
    add_stock_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Text for Watchlist
    wxStaticText* watchlist_text = new wxStaticText(panel, wxID_ANY, "Watchlist", wxPoint(500, 50));
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

    //request_funds_button->Bind(wxEVT_BUTTON, &MainFrame::OnRequestFundsButtonClicked, this);










    // Input Frame for Adding Funds

    wxTextCtrl* adding_withdrawing_funds_frame = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(160, 320), wxSize(70, 20));













    // Input Frame for Adding a Ticker Symbol

    wxTextCtrl* adding_ticker_frame = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(380, 400), wxSize(100, 20));

    // Button for Updating Data Table

    wxButton* update_button = new wxButton(panel, wxID_ANY, "Update", wxPoint(780, 400), wxSize(100, 25));
    update_button->SetBackgroundColour(*wxLIGHT_GREY);

    // Scroll Bar for Data Table

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxPoint(250, 80), wxSize(630, 300));
    scrolledWindow->SetScrollRate(10, 10); // Set the scrolling increment

    // Data Table for Ticker Data
    basicListView = new wxListView(scrolledWindow, wxID_ANY, wxPoint(0, 0), wxSize(630, 300));

    // Enable vertical scrolling
    scrolledWindow->SetScrollbars(0, 10, 0, 100);

    // Append columns and set column labels
    basicListView->AppendColumn("", wxLIST_FORMAT_LEFT, 80);
    basicListView->AppendColumn("Ticker", wxLIST_FORMAT_LEFT, 120);
    basicListView->AppendColumn("Market Value", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Avg. Price", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Shares Held", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Avg. P/L", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Quantity", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Buy", wxLIST_FORMAT_LEFT, 600);
    basicListView->AppendColumn("Sell", wxLIST_FORMAT_LEFT, 600);

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
    // Set the width of the third column
    basicListView->SetColumnWidth(6, 80);
    // Set the width of the third column
    basicListView->SetColumnWidth(7, 50);
    // Set the width of the third column
    basicListView->SetColumnWidth(8, 50);




    wxStaticText* funds_available = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 280), wxSize(70, 20));


    wxStaticText* profit_loss = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 180), wxSize(70, 20));

    wxStaticText* portfolio_book_value = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 140), wxSize(70, 20));

    wxStaticText* portfolio_balance = new wxStaticText(panel, wxID_ANY, "0", wxPoint(160, 100), wxSize(70, 20));

    
    
    

}

    
