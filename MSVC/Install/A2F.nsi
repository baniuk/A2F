# define the name of the installer
SetCompressor /FINAL /SOLID lzma 
outfile "A2F.exe"
 
# define the directory to install to, the desktop in this case as specified  
# by the predefined $DESKTOP variable
installDir "c:\A2F"
Page components
Page directory
Page instfiles
# default section
Section "VC Redistributable 2012"
	ClearErrors
	ExecWait "$EXEDIR\vcredist_x86.exe" $0
	DetailPrint "some program returned $0"
	IfErrors 0 +2
		messageBox MB_OK "Installation of VC Redist failed. Check if the file vcredist_x86.exe is present in installator directory or install it manually."
	
SectionEnd

Section "A2F"

	# g³ówny katalog
	setOutPath $INSTDIR
	file A2F\*.*
		
	setOutPath $INSTDIR
	
	RegDLL a2f.dll
	
	writeUninstaller $INSTDIR\uninstall.exe
	
	WriteRegStr HKCU "Software\A2F" "InstallDir" "$INSTDIR"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "Name" "A2F"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "Description" "Cape-Open 2 Fluent port"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "CapeVersion" "1.0"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "ComponentVersion" "1.0"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "VendorURL" "baniuk@zut.edu.pl"
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription" "About" "(c) Piotr Baniukiewicz"
	
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\Implemented Categories\{678C09A1-7D66-11D2-A67D-00105A42887F}" "" ""
	WriteRegStr HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\Implemented Categories\{678C09A1-7D66-11D2-A67D-00105A42887F}" "" ""

	# create a shortcut named "new shortcut" in the start menu programs directory
    # presently, the new shortcut doesn't call anything (the second field is blank)
	CreateDirectory "$SMPROGRAMS\A2F"
    createShortCut "$SMPROGRAMS\A2F\Params.lnk" "$INSTDIR\A2F.cfg"
	createShortCut "$SMPROGRAMS\A2F\uninstall.lnk" "$INSTDIR\uninstall.exe"
 SectionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"
 
# Always delete uninstaller first
	delete "$INSTDIR\uninstall.exe"

    delete "$SMPROGRAMS\A2F\A2F.cfg"
	delete "$SMPROGRAMS\A2F\uninstall.lnk"
	RMDir "$SMPROGRAMS\A2F"
	UnRegDLL a2f.dll
	DeleteRegKey HKCU "Software\Cape2Fluent"
	DeleteRegKey HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\CapeDescription"
	DeleteRegKey HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}\Implemented Categories"
	DeleteRegKey HKCR "CLSID\{A9129436-FB2C-4D26-B88D-A61E4D594BCB}"

# now delete installed file
	messageBox MB_OK "Please, delete A2F installation directory manually"
SectionEnd