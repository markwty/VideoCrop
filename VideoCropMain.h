/***************************************************************
 * Name:      VideoCropMain.h
 * Purpose:   Defines Application Frame
 * Author:    Mark ()
 * Created:   2020-02-04
 * Copyright: Mark ()
 * License:
 **************************************************************/

#ifndef VIDEOCROPMAIN_H
#define VIDEOCROPMAIN_H

//(*Headers(VideoCropFrame)
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/statusbr.h>
//*)
#include <wx/mediactrl.h>
#include <wx/dcclient.h>
#include <wx/overlay.h>

class VideoCropFrame: public wxFrame
{
    public:

        VideoCropFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~VideoCropFrame();
        void VideoMediaCtrlMediaLoaded(wxMediaEvent& event);
        void VideoMediaCtrlMediaFinished(wxMediaEvent& event);
        void LoadVideo(wxString selectedFile);

    private:

        //(*Handlers(VideoCropFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnChooseBtnClick(wxCommandEvent& event);
        void OnAspectRatioRadioBoxSelect(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        //*)

        //(*Identifiers(VideoCropFrame)
        static const long ID_CHOOSEBTN;
        static const long ID_MEDIAPANEL;
        static const long ID_ASPECTRATIORADIOBOX;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(VideoCropFrame)
        wxButton* ChooseBtn;
        wxFileDialog* ChooseFileDialog;
        wxPanel* MediaPanel;
        wxRadioBox* AspectRatioRadioBox;
        wxStatusBar* StatusBar1;
        //*)
        long ID_VIDEOMEDIACTRL;
        wxMediaCtrl* VideoMediaCtrl;
        int aspect = 0, height = 350;
        //wxPoint prev_pt;
        //bool left_down = false;
        DECLARE_EVENT_TABLE()
};
#endif // VIDEOCROPMAIN_H
