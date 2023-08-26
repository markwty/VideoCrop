/***************************************************************
 * Name:      VideoCropMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mark ()
 * Created:   2020-02-04
 * Copyright: Mark ()
 * License:
 **************************************************************/

#include "VideoCropMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(VideoCropFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
/*
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }
    return wxbuild;
}
*/

//(*IdInit(VideoCropFrame)
const long VideoCropFrame::ID_CHOOSEBTN = wxNewId();
const long VideoCropFrame::ID_MEDIAPANEL = wxNewId();
const long VideoCropFrame::ID_ASPECTRATIORADIOBOX = wxNewId();
const long VideoCropFrame::idMenuQuit = wxNewId();
const long VideoCropFrame::idMenuAbout = wxNewId();
const long VideoCropFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(VideoCropFrame,wxFrame)
    //(*EventTable(VideoCropFrame)
    //*)
END_EVENT_TABLE()

VideoCropFrame::VideoCropFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(VideoCropFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(715,400));
    ChooseBtn = new wxButton(this, ID_CHOOSEBTN, _("Choose video"), wxPoint(624,0), wxSize(90,30), 0, wxDefaultValidator, _T("ID_CHOOSEBTN"));
    MediaPanel = new wxPanel(this, ID_MEDIAPANEL, wxPoint(0,0), wxSize(624,352), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_MEDIAPANEL"));
    wxString __wxRadioBoxChoices_1[2] =
    {
    	_("4:3"),
    	_("16:9")
    };
    AspectRatioRadioBox = new wxRadioBox(this, ID_ASPECTRATIORADIOBOX, _("Aspect ratio"), wxPoint(632,40), wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_ASPECTRATIORADIOBOX"));
    AspectRatioRadioBox->SetSelection(1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ChooseFileDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_CHOOSEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VideoCropFrame::OnChooseBtnClick);
    Connect(ID_ASPECTRATIORADIOBOX,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&VideoCropFrame::OnAspectRatioRadioBoxSelect);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&VideoCropFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&VideoCropFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&VideoCropFrame::OnClose);
    //*)
    ID_VIDEOMEDIACTRL = NewControlId();
    VideoMediaCtrl = new wxMediaCtrl(MediaPanel, ID_VIDEOMEDIACTRL, _(""), wxPoint(0, 0), wxSize((int)(16.0/9*height), height), wxNO_BORDER, wxMEDIABACKEND_WMP10);
	VideoMediaCtrl->ShowPlayerControls();
	Connect(ID_VIDEOMEDIACTRL, wxEVT_MEDIA_LOADED, wxMediaEventHandler(VideoCropFrame::VideoMediaCtrlMediaLoaded), NULL, this);
	Connect(ID_VIDEOMEDIACTRL, wxEVT_MEDIA_FINISHED, wxMediaEventHandler(VideoCropFrame::VideoMediaCtrlMediaFinished));
	//drawPane = new BasicDrawPane(drawPanel);
}

VideoCropFrame::~VideoCropFrame()
{
    //(*Destroy(VideoCropFrame)
    //*)
}

void VideoCropFrame::VideoMediaCtrlMediaLoaded(wxMediaEvent& event)
{
	VideoMediaCtrl->Play();
    VideoMediaCtrl->SetVolume(0);
}

void VideoCropFrame::VideoMediaCtrlMediaFinished(wxMediaEvent& event)
{
	VideoMediaCtrl->Play();
}

void VideoCropFrame::LoadVideo(wxString selectedFile)
{
    VideoMediaCtrl->Load(selectedFile);
}

void VideoCropFrame::OnChooseBtnClick(wxCommandEvent& event)
{
    ChooseFileDialog = new wxFileDialog(this);
    if (ChooseFileDialog->ShowModal() == wxID_OK)
    {
        wxString selectedFile = ChooseFileDialog->GetPath();
        VideoMediaCtrl->Load(selectedFile);
        VideoMediaCtrl->Play();
    }
}

void VideoCropFrame::OnAspectRatioRadioBoxSelect(wxCommandEvent& event)
{
    if (aspect == 0 && AspectRatioRadioBox->GetString(AspectRatioRadioBox->GetSelection()).compare("16:9") != 0)
    {
        VideoMediaCtrl->SetSize(0, 0, (int)(4.0/3*height), height);
        aspect = 1;
    }
    else if (aspect == 1 && AspectRatioRadioBox->GetString(AspectRatioRadioBox->GetSelection()).compare("4:3") != 0)
    {
        VideoMediaCtrl->SetSize(0, 0, (int)(16.0/9*height), height);
        aspect = 0;
    }
}

void VideoCropFrame::OnClose(wxCloseEvent& event)
{
    if (VideoMediaCtrl->Stop() || VideoMediaCtrl->GetState() == wxMEDIASTATE_STOPPED)
    {
        Destroy();
    }
}

void VideoCropFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void VideoCropFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxMessageBox("", _("Welcome to..."));
}
/*
void VideoCropFrame::OndrawPanelLeftDown(wxMouseEvent& event)
{
    left_down = true;
    prev_pt.x = event.GetX();
    prev_pt.y = event.GetY();
}

void VideoCropFrame::OndrawPanelMouseMove(wxMouseEvent& event)
{
    if (left_down)
    {
        wxClientDC dc(drawPanel);
        dc.Clear();
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetPen(wxPen(wxColor(255,175,175), 1, wxPENSTYLE_SHORT_DASH));
        int mouseX = event.GetX();
        int mouseY = event.GetY();
        dc.DrawRectangle(std::min(prev_pt.x, mouseX), std::min(prev_pt.y, mouseY), abs(prev_pt.x - mouseX), abs(prev_pt.y - mouseY));
    }
}

void VideoCropFrame::OndrawPanelLeftUp(wxMouseEvent& event)
{
    left_down = false;
    wxClientDC dc(drawPanel);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(wxPen(wxColor(255,175,175), 1, wxPENSTYLE_SHORT_DASH));
    int mouseX = event.GetX();
    int mouseY = event.GetY();
    dc.DrawRectangle(std::min(prev_pt.x, mouseX), std::min(prev_pt.y, mouseY), abs(prev_pt.x - mouseX), abs(prev_pt.y - mouseY));
}
*/
