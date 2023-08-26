/***************************************************************
 * Name:      VideoCropApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Mark ()
 * Created:   2020-02-04
 * Copyright: Mark ()
 * License:
 **************************************************************/

#include "VideoCropApp.h"

//(*AppHeaders
#include "VideoCropMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(VideoCropApp);

bool VideoCropApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	VideoCropFrame* Frame = new VideoCropFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
