#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>


class MainFrame : public wxFrame
{
 public:
     MainFrame(const wxString& Title);
     MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);        

 void OnEnterPressed(wxCommandEvent& event);

 void AddingSellingTickers(wxCommandEvent& event);

 void LoadDataFromFile();

private:
    std::vector<std::string> tickers;
     
 private:    
     wxTextCtrl* adding_withdrawing_funds_frame;
     wxTextCtrl* adding_ticker_frame;

 private:
      wxListView* basicListView;
      wxString userInput;
 
 private:
      wxStaticText* userInputText;

 private:
      wxStaticText* funds_available;
      wxStaticText* profit_loss;
      wxStaticText* portfolio_book_value;
      wxStaticText* portfolio_balance;


};