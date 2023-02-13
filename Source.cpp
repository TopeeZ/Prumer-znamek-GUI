#include <wx/wx.h>


class Appka : public wxApp {
public:
	virtual bool OnInit();
};

class Frame : public wxFrame {
public:
	Frame(const wxString& title);
	void OnButtonClick(wxCommandEvent& evt);
	void OnQuit(wxCommandEvent& evt);

private:
	wxTextCtrl *textbox;
	wxButton *button;
	float prumer = 0;
	float nasobekPrumeru = 0;
	float sum = 0;
	int cislo;

	struct znamka {
		float hodnota;
		float vaha;
	};
	znamka pole[5];

	DECLARE_EVENT_TABLE()
};

DECLARE_APP(Appka)

IMPLEMENT_APP(Appka)

bool Appka::OnInit() {
	wxSize windowSize(300, 250);
	Frame *frame = new Frame(wxT("Appka"));
	frame->SetMaxClientSize(windowSize);
	frame->SetMinClientSize(windowSize);
	frame->Center(true);
	frame->Show(true);
	return true;
}

void Frame::OnButtonClick(wxCommandEvent& evt) {
	cislo = wxAtoi(textbox->GetValue());

	for (int i = 0; i < cislo; i++) {
		wxString znamka_str = wxGetTextFromUser("Zadej známku: ", "Zadávání");
		pole[i].hodnota = wxAtof(znamka_str);
		wxString vaha_str = wxGetTextFromUser("Zadej váhu: ", "Zadávání");
		pole[i].vaha = wxAtof(vaha_str);

		nasobekPrumeru += pole[i].hodnota * pole[i].vaha;
		sum += pole[i].vaha;
	}
	
	prumer = nasobekPrumeru / sum;
	wxMessageBox(wxString::Format("Tvùj prùmìr známek je: %.2f",prumer), "Info", wxOK | wxICON_INFORMATION);
}

void Frame::OnQuit(wxCommandEvent& evt) {
	Close();
}
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_BUTTON(wxID_ANY, Frame::OnButtonClick)
	EVT_MENU(wxID_EXIT, Frame::OnQuit)
END_EVENT_TABLE();

Frame::Frame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
	wxPanel *panel = new wxPanel(this, wxID_ANY);
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxFont font2(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxMenu *quitMenu = new wxMenu;
	wxMenuBar *menuBar = new wxMenuBar;
	wxIcon icon("E:/dev/game.ico", wxBITMAP_TYPE_ICO);
	textbox = new wxTextCtrl(panel, wxID_ANY, "Sem zadej poèet známek.", wxPoint(20, 20), wxSize(260, 120), wxTE_MULTILINE | wxHSCROLL);
	button = new wxButton(panel, wxID_ANY, "Vypoèítej", wxPoint(20, 160), wxSize(260, 50));
	
	quitMenu->Append(wxID_EXIT, wxT("U&konèit\tAlt-X"), wxT("Ukonèit"));
	menuBar->Append(quitMenu, wxT("&Soubor"));
	textbox->SetScrollbar(wxVERTICAL, 0,0,0);
	textbox->SetFont(font);
	button->SetFont(font2);

	SetIcon(icon);
	SetMenuBar(menuBar);
}