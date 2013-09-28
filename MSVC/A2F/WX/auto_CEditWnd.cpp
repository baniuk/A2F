///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "auto_CEditWnd.h"

///////////////////////////////////////////////////////////////////////////

info_Dialog::info_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* main_Sizer;
	main_Sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* label_Sizer;
	label_Sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Info") ), wxVERTICAL );
	
	
	main_Sizer->Add( label_Sizer, 8, wxEXPAND, 5 );
	
	wxBoxSizer* button_Sizer;
	button_Sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_OK_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	button_Sizer->Add( m_OK_button, 0, wxALL, 5 );
	
	
	main_Sizer->Add( button_Sizer, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( main_Sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

info_Dialog::~info_Dialog()
{
}
